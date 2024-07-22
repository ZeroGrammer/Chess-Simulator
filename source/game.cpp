
#include "game.hpp"

using namespace Graphics;
using namespace Chess;

static Window G_window;
static Board G_board;
static bool G_game_over;

static Colors::Theme theme = Colors::REGULAR_ONE;

// NOTE(Tejas): The flipped board is true when the White pieces appear at the 
//              bottom, and false when the Black pieces are at the bottom
static bool G_is_board_flipped;

static void selectSquare(Square clicked_square) {
    
    Piece clicked_piece = G_board.getPieceAt(clicked_square);

    if (clicked_piece.color == G_board.getTurn()) {
        G_board.setSelection(clicked_square);
    }
    else {
        G_board.resetSelection();
        return;
    }
}

static void movePiece(Square clicked_square) {
    
    // NOTE(Tejas): move the piece from the selected square to the clicked square
    //              only if the clicked square is a legal square that the selected
    //              piece can move to

    Square selected_square = G_board.getSelectedSquare();
    Player player_turn = G_board.getTurn();

    bool is_valid = MoveEngine::isValidMove(G_board, selected_square, clicked_square);

    if (is_valid) {

        G_board.movePiece(selected_square, clicked_square);

        // checking for pawn promotion
        Square promotion_square = MoveEngine::canPromote(G_board, player_turn);
        if (promotion_square != OFF_SQUARE) {

            // for now promotes to just Queen.
            Piece promote_to = { Piece::Type::QUEEN, player_turn};
            G_board.promotePawn(promotion_square, promote_to);
        }

        G_board.changeTurn();
    }

    Square king_side_castle = MoveEngine::canCastleKingSide(G_board, player_turn);
    Square queen_side_castle = MoveEngine::canCastleQueenSide(G_board, player_turn);
    if (king_side_castle == clicked_square) {
        G_board.castleKingSide(player_turn);
        G_board.changeTurn();
    }
            
    if (queen_side_castle == clicked_square) {
        G_board.castleQueenSide(player_turn);
        G_board.changeTurn();
    }
}

static void handleMouse() {
    
    if (G_window.mouse.type == Mouse::Type::RCLICK) {
        G_board.resetSelection();
        return;
    }
    
    else if (G_window.mouse.type == Mouse::Type::LCLICK) {

        Square clicked_square = G_window.rend->pixelToBoardConverter(G_window.mouse.x, G_window.mouse.y);

        if (!G_board.isAnySquareSelected()) {
            selectSquare(clicked_square);
            return;
        }

        else {
            movePiece(clicked_square);
            G_board.updatePlayerInfo();
            G_board.resetSelection();
        }
    }
}

static void handleKeyboard() {
    
    if (G_window.kbd.type == Keyboard::Type::FLIP_BOARD) {
        G_is_board_flipped = (G_is_board_flipped) ? false : true;
        G_window.rend->setFlippedBoard(!G_is_board_flipped);
    }

    else if (G_window.kbd.type == Keyboard::Type::RESET_BOARD) {
        G_board.resetBoard();
        G_game_over = false;
    }
}

static Player checkGameOver() {

    Player winner = Player::NONE;

    if (MoveEngine::isInCheckMate(G_board, Piece::Color::WHITE)) {
        G_game_over = true;
        winner = Player::BLACK;
    }

    if (MoveEngine::isInCheckMate(G_board, Piece::Color::BLACK)) {
        G_game_over = true;
        winner = Player::WHITE;
    }

    return winner;
}

static void drawBoard() {

    Square selected_square = G_board.getSelectedSquare();

    for (int rank = 0; rank < BOARD_SIZE; rank++) {

        for (int file = 0; file < BOARD_SIZE; file++) {

            Square square = { rank, file };

            Color color = ((rank + file) % 2) ? theme.dark_sq : theme.light_sq;
            G_window.rend->fillSquare(square, color);

            if (selected_square == square)
                G_window.rend->fillSquare(selected_square, theme.highlight_sq);

            G_window.rend->renderPieceTexture(square, G_board.getPieceAt(square));

            if (selected_square != OFF_SQUARE) {
                bool is_valid = MoveEngine::isValidMove(G_board, selected_square, square);
                if (is_valid)
                    G_window.rend->fillSquare(square, theme.legal_sq);
            }
        }
    }

    // highlights castle square(s) if available
    if (G_board.getPieceAt(selected_square).type == Piece::Type::KING) {

        Square king_side_castle_square = MoveEngine::canCastleKingSide(G_board, G_board.getPieceAt(selected_square).color);
        if (king_side_castle_square != OFF_SQUARE)
            G_window.rend->fillSquare(king_side_castle_square, theme.legal_sq);

        Square queen_side_castle_square = MoveEngine::canCastleQueenSide(G_board, G_board.getPieceAt(selected_square).color);
        if (queen_side_castle_square != OFF_SQUARE)
            G_window.rend->fillSquare(queen_side_castle_square, theme.legal_sq);
    }
}

int Game::run() {

    if (G_window.initialize() == -1) {
        std::cerr << "An error occured while initializing the Window Class...\n";
        return -1;
    }

    G_is_board_flipped = false;
    G_window.rend->setFlippedBoard(!G_is_board_flipped);

    G_game_over = false;

    Player winner = Player::NONE;

    while (!G_window.shouldClose()) {

        if (!G_game_over) handleMouse();
        handleKeyboard();

        if (!G_game_over) winner = checkGameOver();

        G_window.rend->clear();

        drawBoard();

        if (winner != Player::NONE) {

            if (winner == Player::WHITE)
                G_window.rend->displayFog(Colors::WHITE_FOG);

            if (winner == Player::BLACK)
                G_window.rend->displayFog(Colors::BLACK_FOG);
        }

        G_window.rend->present();
        G_window.pollEvents();
    }

    return 0;
}
