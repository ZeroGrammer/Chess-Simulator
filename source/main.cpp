
/*
  TODO(Tejas):
  - [ ] fix the bug that in pawn promotion default promotion type
  - [ ] Add a Logging system
  - [ ] Remove SDL dependency
*/

// I thought the adding the new feature would take me about 2 hours
// It took me 20 mins... So.. Ya..

#include "game.hpp"

int main(int argc, char **argv) {

    (void) argc; (void) argv;

    int result = Game::run();
    return result;
}
