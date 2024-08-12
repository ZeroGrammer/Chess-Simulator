
/*
  TODO(Tejas):
  - [ ] fix the bug that in pawn promotion default promotion type
  - [ ] Add a Logging system
  - [ ] Remove SDL dependency
*/

#include "game.hpp"

int main(int argc, char **argv) {

    (void) argc; (void) argv;

    int result = Game::run();
    return result;
}
