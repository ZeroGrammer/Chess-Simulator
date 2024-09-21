
#include "game.hpp"

using namespace Graphics;
using namespace Chess;


struct GameState {

    Board board;

    bool game_over;
    Player winner;

    Piece::Type promotion_piece_type;
};

struct Settings {

    bool is_board_flipped;
    bool pause_board_controls;

    bool focus_on_board;
    bool focus_on_menu;

    Colors::Theme theme;
};


static Window    G_window;
static GameState G_game_state;
static Settings  G_settings;
static MoveStack G_move_stack;


static int initialize() {
    
    std::string STARTING_FEN = "RNBKQBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbkqbnr w QKqk";
    // std::string STARTING_FEN = "8/pppppppp/8/8/8/8/PPPPPPPP/8 w QKqk";

    if (G_window.initialize() == -1) {
        log(ERR, "An Error occured while initializing the Window Class...");
        return -1;
    }

    if (G_move_stack.initialize(STARTING_FEN) == -1) {
        log(ERR, "An Error occured while initializing the Move Stack...");
        return -1;
    }


    G_game_state.game_over = false;
    G_game_state.winner = Player::NONE;
    G_game_state.promotion_piece_type = Piece::Type::QUEEN;
    G_game_state.board.fenReader(STARTING_FEN);


    G_settings.is_board_flipped = false;
    G_settings.pause_board_controls = false;
    G_settings.focus_on_board = true;
    G_settings.focus_on_menu = false;
    G_settings.theme = Colors::REGULAR_TWO;


    G_window.rend->setIsFlipped(!G_settings.is_board_flipped);

    return 0;
}

static void toggleMenu() {

    G_settings.focus_on_menu = (G_settings.focus_on_menu) ? false : true;
    G_settings.focus_on_board = !G_settings.focus_on_menu;
}

static void handleKeyboardOnBoard() {
    
    if (G_window.kbd.type == Keyboard::Type::FLIP_BOARD) {
        G_settings.is_board_flipped = (G_settings.is_board_flipped) ? false : true;
    }

    if (G_window.kbd.type == Keyboard::Type::RESET_BOARD) {
        G_game_state.board.resetBoard();
        G_game_state.game_over = false;
        G_settings.pause_board_controls = false;
        G_move_stack.clear();
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

    if (G_window.kbd.type == Keyboard::Type::PREVIOUS_MOVE) {
        Move prev_move = G_move_stack.getPriviousMove();
        G_game_state.board.fenReader(prev_move.fen);
    }

    if (G_window.kbd.type == Keyboard::Type::NEXT_MOVE) {
        Move next_move = G_move_stack.getNextMove();
        G_game_state.board.fenReader(next_move.fen);
    }

    if (G_window.kbd.type == Keyboard::Type::LATEST_MOVE) {
        Move latest_move = G_move_stack.getLatestMove();
        G_game_state.board.fenReader(latest_move.fen);
    }
}

static void handleKeyboardOnMenu() {

    if (G_window.kbd.type == Keyboard::Type::NEXT_ITEM) {

        
    }

    if (G_window.kbd.type == Keyboard::Type::PREVIOUS_ITEM) {

        
    }
}

static bool makeMove(Square from, Square to, Player player) {

    bool result = false;

    Move move = {};
    move.player = player;
    move.squares.from = from;
    move.squares.to = to;

    bool is_valid = MoveEngine::isValidMove(G_game_state.board, from, to);

    Square king_side_castle = MoveEngine::canCastleKingSide(G_game_state.board, player);
    Square queen_side_castle = MoveEngine::canCastleQueenSide(G_game_state.board, player);

    Move prev_move = G_move_stack.getLatestMove();
    Square en_passent = MoveEngine::canEnPassant(G_game_state.board, from, prev_move);

    if (is_valid) {
        
        G_game_state.board.movePiece(from, to);
        result = true;

        // checking for pawn promotion
        Square promotion_square = MoveEngine::canPromote(G_game_state.board, player);
        if (promotion_square != OFF_SQUARE) {
            Piece promote_to = { G_game_state.promotion_piece_type, player };
            G_game_state.board.promotePawn(promotion_square, promote_to);
            G_game_state.promotion_piece_type = Piece::Type::QUEEN;
        }
    }

    else if (king_side_castle == to) {

        G_game_state.board.castle(player, Side::KING_SIDE);
        result = true;

        move.is_castle = true;
        move.castle.is_king_side = true;
    }
            
    else if (queen_side_castle == to) {

        G_game_state.board.castle(player, Side::QUEEN_SIDE);
        result = true;

        move.is_castle = true;
        move.castle.is_queen_side = true;
    }

    else if (en_passent == to) {

        if (en_passent.file < from.file)
            G_game_state.board.enPassent(from, Side::KING_SIDE);

        if (en_passent.file > from.file)
            G_game_state.board.enPassent(from, Side::QUEEN_SIDE);
        
        result = true;

        move.piece = G_game_state.board.getPieceAt(to);
        move.is_enpassent = true;
    }


    if (result) {
        G_game_state.board.changeTurn();

        move.piece = G_game_state.board.getPieceAt(to);
        move.fen = G_game_state.board.getFen();

        G_move_stack.addMove(move);
    }

    return result; 
}

static bool handleMouseOnBoard() {

    if (G_window.mouse.type == Mouse::Type::RCLICK) {
        G_game_state.board.resetSelection();
        return 0;
    }

    if (G_window.mouse.type == Mouse::Type::LCLICK) {

        Square clicked_square =
            G_window.rend->pixelToBoardConverter(G_window.mouse.x, G_window.mouse.y);

        if (!G_game_state.board.isAnySquareSelected()) {

            Piece piece = G_game_state.board.getPieceAt(clicked_square);

            if (piece.color == G_game_state.board.getTurn()) {
                G_game_state.board.setSelection(clicked_square);
            } else {
                G_game_state.board.resetSelection();
            }

            return 0;
        }

        if (G_game_state.board.isAnySquareSelected()) {

            Square selected_square = G_game_state.board.getSelectedSquare();

            bool result = makeMove(selected_square, clicked_square, G_game_state.board.getTurn());

            G_game_state.board.updatePlayerInfo();
            G_game_state.board.resetSelection();   // reset selection if clicked on a non vaild square.

            return result;
        }
    }

    return 0;
}

static void update() {

    if (G_window.kbd.type == Keyboard::Type::TOGGLE_MENU)
        toggleMenu();

    if (G_settings.focus_on_board) {

        handleKeyboardOnBoard();

        if (!G_settings.pause_board_controls) {
            bool result = handleMouseOnBoard();
            // TODO(Tejas): // later we'll use this result for the bot to decide wheather it should make a move or wait
            result;  
        }

        if (!G_move_stack.isOnLatest()) G_settings.pause_board_controls = true;
        else G_settings.pause_board_controls = false;

        if (MoveEngine::isInCheckMate(G_game_state.board, Piece::Color::WHITE)) {
            G_game_state.winner = Player::BLACK;
            G_game_state.game_over = true;
        }

        if (MoveEngine::isInCheckMate(G_game_state.board, Piece::Color::BLACK)) {
            G_game_state.winner = Player::WHITE;
            G_game_state.game_over = true;
        }

    }

    if (G_settings.focus_on_menu) {

        handleKeyboardOnMenu();
    }

    G_window.rend->setIsFlipped(!G_settings.is_board_flipped);
}

static void drawGameOverFog() {
    
    // draw fog on game over
    if (G_game_state.winner == Player::WHITE) G_window.rend->displayFog(Colors::WHITE_FOG);
    if (G_game_state.winner == Player::BLACK) G_window.rend->displayFog(Colors::BLACK_FOG);
}

static void drawBoard() {

    Square selected_square = G_game_state.board.getSelectedSquare();

    for (int rank = 0; rank < BOARD_SIZE; rank++) {

        for (int file = 0; file < BOARD_SIZE; file++) {

            Square current_square = { rank, file };

            Color base_color = ((rank + file) % 2) ? G_settings.theme.dark_sq : G_settings.theme.light_sq;
            G_window.rend->fillSquare(current_square, base_color);

            // NOTE(Tejas): Selected Square is being rendered inside the loop because we need it to be
            //              rendered after the base color and before the piece.
            if (selected_square == current_square)
                G_window.rend->fillSquare(selected_square, G_settings.theme.highlight_sq);

            G_window.rend->renderPieceTexture(current_square, G_game_state.board.getPieceAt(current_square));

            if (selected_square != OFF_SQUARE) {
                bool is_valid = MoveEngine::isValidMove(G_game_state.board, selected_square, current_square);
                if (is_valid) G_window.rend->fillSquare(current_square, G_settings.theme.legal_sq);
            }
        }
    }

    // highlights castle square(s) if available
    if (G_game_state.board.getPieceAt(selected_square).type == Piece::Type::KING) {

        Square king_side_castle_square =
            MoveEngine::canCastleKingSide(G_game_state.board,
                                          G_game_state.board.getPieceAt(selected_square).color);
        Square queen_side_castle_square =
            MoveEngine::canCastleQueenSide(G_game_state.board,
                                           G_game_state.board.getPieceAt(selected_square).color);

        if (king_side_castle_square != OFF_SQUARE)
            G_window.rend->fillSquare(king_side_castle_square, G_settings.theme.legal_sq);

        if (queen_side_castle_square != OFF_SQUARE)
            G_window.rend->fillSquare(queen_side_castle_square, G_settings.theme.legal_sq);
    }

    // highlights enpassent square if available
    if (G_game_state.board.getPieceAt(selected_square).type == Piece::Type::PAWN) {

        Move prev_move = G_move_stack.getLatestMove();
        Square en_passent_square = MoveEngine::canEnPassant(G_game_state.board, selected_square, prev_move);

        if (en_passent_square != OFF_SQUARE)
            G_window.rend->fillSquare(en_passent_square, G_settings.theme.legal_sq);
    }
}

static void drawMenu() {

    Square s = { 3, 3 };
    G_window.rend->fillSquare(s, 0xFF0000FF);
    s = { 3, 4 };
    G_window.rend->fillSquare(s, 0xFF0000FF);
    s = { 4, 3 };
    G_window.rend->fillSquare(s, 0xFF0000FF);
    s = { 4, 4 };
    G_window.rend->fillSquare(s, 0xFF0000FF);
}

int Game::run() {

    int result = initialize();
    if (result != 0) return result;

    while (!G_window.shouldClose()) {

        // Updatings
        G_window.pollEvents();

        update();

        // Drawings
        G_window.rend->clear();

        if (G_settings.focus_on_board) {
            drawBoard();   
            if (G_game_state.game_over) drawGameOverFog();
        }

        if (G_settings.focus_on_menu) {
            drawMenu();
        }
        

        G_window.rend->present();
    }

    return 0;
}
