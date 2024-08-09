
#include "game.hpp"

using namespace Graphics;
using namespace Chess;

struct GameState {

    bool game_over;
    bool is_board_flipped;

    Board board;
    Piece::Type promotion_piece_type;

    MoveStack move_stack;
};

static GameState G_game_state;
static Window G_window;
static Colors::Theme theme = Colors::REGULAR_TWO;

static void selectSquare(Square clicked_square) {
    
    Piece clicked_piece = G_game_state.board.getPieceAt(clicked_square);

    if (clicked_piece.color == G_game_state.board.getTurn())
        G_game_state.board.setSelection(clicked_square);

    else
        G_game_state.board.resetSelection();
}

static void movePiece(Square clicked_square) {
    
    // NOTE(Tejas): move the piece from the selected square to the clicked square
    //              only if the clicked square is a legal square that the selected
    //              piece can move to

    Square selected_square = G_game_state.board.getSelectedSquare();
    Player player_turn = G_game_state.board.getTurn();

    Move move = {};
    move.fen = _strdup(G_game_state.board.getFen());
    move.player = player_turn;
    move.squares.from = selected_square;
    move.squares.to = clicked_square;

    bool is_valid = MoveEngine::isValidMove(G_game_state.board, selected_square, clicked_square);

    if (is_valid) {

        G_game_state.board.movePiece(selected_square, clicked_square);

        // checking for pawn promotion
        Square promotion_square = MoveEngine::canPromote(G_game_state.board, player_turn);

        if (promotion_square != OFF_SQUARE) {
            Piece promote_to = { G_game_state.promotion_piece_type, player_turn };
            G_game_state.board.promotePawn(promotion_square, promote_to);
            G_game_state.promotion_piece_type = Piece::Type::QUEEN;
        }

        G_game_state.move_stack.addMove(move);
        G_game_state.board.changeTurn();
    }

    Square king_side_castle = MoveEngine::canCastleKingSide(G_game_state.board, player_turn);
    Square queen_side_castle = MoveEngine::canCastleQueenSide(G_game_state.board, player_turn);

    if (king_side_castle == clicked_square) {

        move.is_castle = true;
        move.castle.is_king_side = true;
        G_game_state.move_stack.addMove(move);

        G_game_state.board.castleKingSide(player_turn);
        G_game_state.board.changeTurn();
    }
            
    if (queen_side_castle == clicked_square) {

        move.is_castle = true;
        move.castle.is_queen_side = true;
        G_game_state.move_stack.addMove(move);

        G_game_state.board.castleQueenSide(player_turn);
        G_game_state.board.changeTurn();
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
            movePiece(clicked_square);
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
}

static Player checkGameOver() {

    Player winner = Player::NONE;

    if (MoveEngine::isInCheckMate(G_game_state.board, Piece::Color::WHITE)) {
        G_game_state.game_over = true;
        winner = Player::BLACK;
    }

    if (MoveEngine::isInCheckMate(G_game_state.board, Piece::Color::BLACK)) {
        G_game_state.game_over = true;
        winner = Player::WHITE;
    }

    return winner;
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
}

int Game::run() {

    const char* STARTING_FEN = "RNBKQBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbkqbnr w QKqk";
    // const char* STARTING_FEN = "RNBKQBNR/PPPP1PPP/11111111/1111P111/11111111/11111111/pppppppp/rnbkqbnr b QKqk";
    // const char* STARTING_FEN = "RNBKQBNR/PPP1PPPP/8/3P4/5p2/8/ppppp1pp/rnbkqbnr w QKqk";

    if (G_window.initialize() == -1) {
        std::cerr << "An error occured while initializing the Window Class...\n";
        return -1;
    }

    G_window.rend->setFlippedBoard(!G_game_state.is_board_flipped);

    G_game_state.is_board_flipped = false;
    G_game_state.promotion_piece_type = Piece::Type::QUEEN;
    G_game_state.game_over = false;

    G_game_state.board.fenReader(STARTING_FEN);
    G_game_state.move_stack.initialize(STARTING_FEN);

    Player winner = Player::NONE;

    while (!G_window.shouldClose()) {

        // update
        G_window.pollEvents();

        handleKeyboard();

        if (!G_game_state.game_over) {
            handleMouse();   
            winner = checkGameOver();
        }

        // draw
        G_window.rend->clear();
        drawBoard();

        if (winner != Player::NONE) {
            if (winner == Player::WHITE) G_window.rend->displayFog(Colors::WHITE_FOG);
            if (winner == Player::BLACK) G_window.rend->displayFog(Colors::BLACK_FOG);
        }

        G_window.rend->present();
    }

    return 0;
}
