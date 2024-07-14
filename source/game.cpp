
#include "game.hpp"

static Graphics::Window window;
static Chess::Board board;

static Colors::Theme theme = Colors::REGULAR_THEME;
static bool is_board_flipped;

static void handleKeyboard() {
    
    if (window.kbd.type == Graphics::Keyboard::Type::FLIP_BOARD) {
        is_board_flipped = (is_board_flipped) ? false : true;
        window.rend->setFlippedBoard(!is_board_flipped);
    }

    if (window.kbd.type == Graphics::Keyboard::Type::RESET_BOARD) {
        // TODO (Tejas): add a method on the board class
        //               that does this reset board
    }
}

static void handleMouse() {
    
    if (window.mouse.type == Graphics::Mouse::Type::RBOARD) {
    }
    
    if (window.mouse.type == Graphics::Mouse::Type::RLOGS) {
    }
    
    if (window.mouse.type == Graphics::Mouse::Type::RMENU) {
    }
    
    if (window.mouse.type == Graphics::Mouse::Type::LBOARD) {
    }
    
    if (window.mouse.type == Graphics::Mouse::Type::LLOGS) {
    }
    
    if (window.mouse.type == Graphics::Mouse::Type::LMENU) {
    }
}

static void drawBoard() {

    for (int rank = 0; rank < BOARD_SIZE; rank++) {
        for (int file = 0; file < BOARD_SIZE; file++) {

            Chess::Square square = { rank, file };

            Graphics::Color color = ((rank + file) % 2) ? theme.dark_sq : theme.light_sq;
            window.rend->fillSquare(square, color);

            window.rend->renderPieceTexture(square, board.getPieceAt(square));
        }
    }
}

int Game::run () {

    if (window.initialize() == -1) {
        std::cerr << "An error occured while initializing the Window Class...\n";
        return -1;
    }

    is_board_flipped = false;
    window.rend->setFlippedBoard(!is_board_flipped);

    while (!window.shouldClose()) {

        handleKeyboard();
        handleMouse();

        window.rend->clear();
        drawBoard();

        window.rend->present();
        window.pollEvents();
    }

    return 0;
}
