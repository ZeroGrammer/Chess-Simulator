
#include "game.hpp"

int Game::mainLoop() {

    Graphics::Window window;
    if (window.initialize() == -1) {
        std::cerr << "An error occured while initializing the Window Class...\n";
        return -1; 
    }

    while (!window.shouldClose()) {

        window.renderer->clear();

        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {

                Square square = { rank, file };

                Color color = ((rank + file) % 2) ? 0x444444FF : 0xCCCCCCFF;
                window.renderer->fillSquare(square, color);
            }
        }

        window.renderer->present();
        window.pollEvents();
    }

    return 0;
}
