
#include "bot.hpp"

int Bot::getEval(Board &board, Player player) {

    (board); (player);
    return 0;
}

Move Bot::getBestMove(Board &board, Player player) {

    Move move = { };

    for (int rank = 0; rank < BOARD_SIZE; rank++) {

        for (int file = 0; file < BOARD_SIZE; file++) {

            Square from = { rank, file };

            if (board.getPieceAt(from).color == player) {

                for (int rank2 = 0; rank2 < BOARD_SIZE; rank2++) {

                    for (int file2 = 0; file2 < BOARD_SIZE; file2++) {

                        Square to = { rank2, file2 };
                        if (board.getPieceAt(to).color != player) {

                            bool is_valid = MoveEngine::isValidMove(board, from, to);
                            if (is_valid) {
                                move.player = player;
                                move.squares.from = from;
                                move.squares.to = to;

                                return move;
                            }
                        }
                    }
                }
            }
        }
    }

    return move;
}
