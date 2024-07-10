
#include "game.hpp"
#include <iostream>

#include <SDL.h>

int main(int argc, char **argv) {

    (void) argc;
    (void) argv;

    SDL_Init(SDL_INIT_EVERYTHING);

    std::cout << "Hello World!";

    return 0;
}
