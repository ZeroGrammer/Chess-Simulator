
#include "game.hpp"

int Game::mainLoop() {

    Graphics::Window window;
    if (window.initialize() == -1) {
        std::cerr << "An error occured while initializing the Window...\n";
        return -1; 
    }

    while (!window.shouldClose()) {

        window.clear();
        window.present();
        window.pollEvents();
    }

    return 0;
}
