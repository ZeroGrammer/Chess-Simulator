
#include "game.hpp"

static Graphics::Window window;
static Colors::Theme theme = Colors::REGULAR_THEME;

static void drawBoard() {

    for (int rank = 0; rank < 8; rank++) {

        for (int file = 0; file < 8; file++) {

            Chess::Square square = { rank, file };

            // Color color = ((rank + file) % 2) ? 0x44AAEEFF : 0xCCCCCCFF;
            Color color = ((rank + file) % 2) ? theme.dark_sq : theme.light_sq;
            window.rend->fillSquare(square, color);
        }
    }
}

int Game::run () {

    if (window.initialize() == -1) {
        std::cerr << "An error occured while initializing the Window Class...\n";
        return -1;
    }

    while (!window.shouldClose()) {

        window.rend->clear();

        drawBoard();

        window.rend->present();
        window.pollEvents();
    }

    return 0;
}
