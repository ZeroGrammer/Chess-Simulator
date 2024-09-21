
/*
 * TODO(Tejas):
 * - [ ] Fix the bug in pawn promotion with the default promotion type
 * - [ ] Fix so that the FEN string follows the regular convention
 * - [ ] Add Stalemate detection
 * - [ ] Add a menu system
*/

#include "game.hpp"

int main(int argc, char **argv) {

    (void) argc; (void) argv;

    int result = Game::run();
    return result;
}
