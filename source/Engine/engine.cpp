
#include "engine.hpp"

Move Engine::getBestMove(const Board &board, Player player) {

    Move move = { };
    move.player = player;

    for (int rank = 0; rank < BOARD_SIZE; rank++) {
        
        for (int file = 0; file < BOARD_SIZE; file++) {

            Square from = { rank, file };

            if (board.getPieceAt(from).color == player) {

                for (int rank2 = 0; rank2 < BOARD_SIZE; rank2++) {

                    for (int file2 = 0; file2 < BOARD_SIZE; file2++) {

                        Square to = { rank2, file2 };
                        bool is_valid = MoveEngine::isValidMove(board, from, to);

                        if (is_valid) {
                            move.squares.from = from;
                            move.squares.to = to;
                            move.piece = board.getPieceAt(move.squares.to);
                            goto loop_break;
                        }
                    }
                }
            }
        }
    }

loop_break:
    return move;
}
