
#include "game.hpp"

using namespace Graphics;
using namespace Chess;

struct GameState {

    bool game_over;
    bool pause_controls;

    bool is_board_flipped;

    Board board;
    Player winner;

    Piece::Type promotion_piece_type;

    MoveStack move_stack;
};

static GameState G_game_state;
static Window G_window;
static Colors::Theme theme = Colors::REGULAR_TWO;

static void selectSquare(Square square) {

    Piece piece = G_game_state.board.getPieceAt(square);

    if (piece.color == G_game_state.board.getTurn())
        G_game_state.board.setSelection(square);

    else
        G_game_state.board.resetSelection();
}

static void movePiece(Square from, Square to, Player player_turn) {

    // NOTE(Tejas): move the piece from the selected square to the clicked square
    //              only if the clicked square is a legal square that the selected
    //              piece can move to

    // NOTE(Tejas): because this function and also return without making any move
    //              the return value is used to check if a move was made or not

    Move move = {};
    move.player = player_turn;
    move.squares.from = from;
    move.squares.to = to;

    bool is_valid = MoveEngine::isValidMove(G_game_state.board, from, to);

    if (is_valid) {

        G_game_state.board.movePiece(from, to);

        // checking for pawn promotion
        Square promotion_square = MoveEngine::canPromote(G_game_state.board, player_turn);

        if (promotion_square != OFF_SQUARE) {
            Piece promote_to = { G_game_state.promotion_piece_type, player_turn };
            G_game_state.board.promotePawn(promotion_square, promote_to);
            G_game_state.promotion_piece_type = Piece::Type::QUEEN;
        }

        move.piece = G_game_state.board.getPieceAt(to);
        move.fen = _strdup(G_game_state.board.getFen());
        G_game_state.move_stack.addMove(move);

        G_game_state.board.changeTurn();

        return;
    }

    Square king_side_castle = MoveEngine::canCastleKingSide(G_game_state.board, player_turn);
    Square queen_side_castle = MoveEngine::canCastleQueenSide(G_game_state.board, player_turn);

    if (king_side_castle == to) {

        G_game_state.board.castleKingSide(player_turn);

        move.piece = G_game_state.board.getPieceAt(to);
        move.is_castle = true;
        move.castle.is_king_side = true;
        move.fen = _strdup(G_game_state.board.getFen());

        G_game_state.move_stack.addMove(move);
        G_game_state.board.changeTurn();

        return;
    }
            
    if (queen_side_castle == to) {

        G_game_state.board.castleQueenSide(player_turn);

        move.piece = G_game_state.board.getPieceAt(to);
        move.is_castle = true;
        move.castle.is_king_side = true;
        move.fen = _strdup(G_game_state.board.getFen());

        G_game_state.move_stack.addMove(move);
        G_game_state.board.changeTurn();

        return;
    }

    // That was way eaiser than I thought.

    Move prev_move = G_game_state.move_stack.getLatestMove();
    Square en_passent = MoveEngine::canEnPassant(G_game_state.board, from, prev_move);

    if (en_passent == to) {

        if (en_passent.file < from.file)
            G_game_state.board.enPassent(from, Side::KING_SIDE);

        if (en_passent.file > from.file)
            G_game_state.board.enPassent(from, Side::QUEEN_SIDE);
        
        move.piece = G_game_state.board.getPieceAt(to);
        move.is_enpassent = true;
        move.fen = _strdup(G_game_state.board.getFen());

        G_game_state.move_stack.addMove(move);
        G_game_state.board.changeTurn();

        return;
    }
}

static void handleMouse() {
    
    if (G_window.mouse.type == Mouse::Type::RCLICK) {

        G_game_state.board.resetSelection();
    }
    
    else if (G_window.mouse.type == Mouse::Type::LCLICK) {

        Square clicked_square = G_window.rend->pixelToBoardConverter(G_window.mouse.x, G_window.mouse.y);

        if (!G_game_state.board.isAnySquareSelected()) {
            selectSquare(clicked_square);
        }

        else {
            Square selected_square = G_game_state.board.getSelectedSquare();
            movePiece(selected_square, clicked_square, G_game_state.board.getTurn());
            G_game_state.board.updatePlayerInfo();
            G_game_state.board.resetSelection();
        }
    }
}

static void handleKeyboard() {

    if (G_window.kbd.type == Keyboard::Type::FLIP_BOARD) {
        G_game_state.is_board_flipped = (G_game_state.is_board_flipped) ? false : true;
        G_window.rend->setFlippedBoard(!G_game_state.is_board_flipped);
    }

    if (G_window.kbd.type == Keyboard::Type::RESET_BOARD) {
        G_game_state.board.resetBoard();
        G_game_state.game_over = false;
        G_game_state.pause_controls = false;
        G_game_state.move_stack.clear();
    }

    if (G_window.kbd.type == Keyboard::Type::PROMOTE_TO) {

        switch (G_window.kbd.piece_type) {

        case Keyboard::PieceType::QUEEN:
            G_game_state.promotion_piece_type = Piece::Type::QUEEN;
            break;
        case Keyboard::PieceType::ROOK:
            G_game_state.promotion_piece_type = Piece::Type::ROOK;
            break;
        case Keyboard::PieceType::BISHOP:
            G_game_state.promotion_piece_type = Piece::Type::BISHOP;
            break;
        case Keyboard::PieceType::KNIGHT:
            G_game_state.promotion_piece_type = Piece::Type::KNIGHT;
            break;
        }
    }

    if (G_window.kbd.type == Keyboard::Type::PRIVIOUS_MOVE) {

        Move prev_move = G_game_state.move_stack.getPriviousMove();
        G_game_state.board.fenReader(prev_move.fen);
    }

    if (G_window.kbd.type == Keyboard::Type::LATEST_MOVE) {

        Move latest_move = G_game_state.move_stack.getLatestMove();
        G_game_state.board.fenReader(latest_move.fen);
    }
}

static Player checkGameOver() {

    Player winner = Player::NONE;

    if (MoveEngine::isInCheckMate(G_game_state.board, Piece::Color::WHITE))
        winner = Player::BLACK;

    if (MoveEngine::isInCheckMate(G_game_state.board, Piece::Color::BLACK))
        winner = Player::WHITE;

    return winner;
}

static void updateState() {
    
    G_game_state.winner = checkGameOver();

    if (G_game_state.winner != Player::NONE) {
        G_game_state.game_over = true;
        G_game_state.pause_controls = true;
    }

    if (!G_game_state.move_stack.isOnLatest()) G_game_state.pause_controls = true;
    else G_game_state.pause_controls = false;

    if (G_game_state.board.getTurn() == Player::BLACK) {

        Move engine_move = Engine::getBestMove(G_game_state.board, G_game_state.board.getTurn());
        movePiece(engine_move.squares.from, engine_move.squares.to, G_game_state.board.getTurn());
        G_game_state.board.updatePlayerInfo();
        G_game_state.board.resetSelection();
    }
}

static void drawBoard() {

    Square selected_square = G_game_state.board.getSelectedSquare();

    for (int rank = 0; rank < BOARD_SIZE; rank++) {

        for (int file = 0; file < BOARD_SIZE; file++) {

            Square square = { rank, file };

            Color color = ((rank + file) % 2) ? theme.dark_sq : theme.light_sq;
            G_window.rend->fillSquare(square, color);

            if (selected_square == square)
                G_window.rend->fillSquare(selected_square, theme.highlight_sq);

            G_window.rend->renderPieceTexture(square, G_game_state.board.getPieceAt(square));

            if (selected_square != OFF_SQUARE) {
                bool is_valid = MoveEngine::isValidMove(G_game_state.board, selected_square, square);
                if (is_valid)
                    G_window.rend->fillSquare(square, theme.legal_sq);
            }
        }
    }

    // highlights castle square(s) if available
    if (G_game_state.board.getPieceAt(selected_square).type == Piece::Type::KING) {

        Square king_side_castle_square =
            MoveEngine::canCastleKingSide(G_game_state.board,
                                          G_game_state.board.getPieceAt(selected_square).color);
        if (king_side_castle_square != OFF_SQUARE)
            G_window.rend->fillSquare(king_side_castle_square, theme.legal_sq);

        Square queen_side_castle_square =
            MoveEngine::canCastleQueenSide(G_game_state.board,
                                           G_game_state.board.getPieceAt(selected_square).color);

        if (queen_side_castle_square != OFF_SQUARE)
            G_window.rend->fillSquare(queen_side_castle_square, theme.legal_sq);
    }

    if (G_game_state.board.getPieceAt(selected_square).type == Piece::Type::PAWN) {

        Move prev_move = G_game_state.move_stack.getLatestMove();
        Square en_passent_square = MoveEngine::canEnPassant(G_game_state.board, selected_square, prev_move);

        if (en_passent_square != OFF_SQUARE)
            G_window.rend->fillSquare(en_passent_square, theme.legal_sq);
    }
}

int Game::run() {

    const char* STARTING_FEN = "RNBKQBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbkqbnr w QKqk";

    if (G_window.initialize() == -1) {
        log(ERR, "An Error occured while initializing the Window Class...");
        return -1;
    }

    G_game_state.is_board_flipped = false;
    G_game_state.promotion_piece_type = Piece::Type::QUEEN;
    G_game_state.game_over = false;
    G_game_state.pause_controls = false;
    G_game_state.winner = Player::NONE;

    G_window.rend->setFlippedBoard(!G_game_state.is_board_flipped);

    G_game_state.board.fenReader(STARTING_FEN);
    G_game_state.move_stack.initialize(STARTING_FEN);

    while (!G_window.shouldClose()) {

        // update
        G_window.pollEvents();

        handleKeyboard();
        if (!G_game_state.pause_controls) handleMouse();   

        updateState();

        // draw
        G_window.rend->clear();
        drawBoard();

        if (G_game_state.winner != Player::NONE) {
            if (G_game_state.winner == Player::WHITE) G_window.rend->displayFog(Colors::WHITE_FOG);
            if (G_game_state.winner == Player::BLACK) G_window.rend->displayFog(Colors::BLACK_FOG);
        }

        G_window.rend->present();
    }

    return 0;
}

