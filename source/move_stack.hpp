
#ifndef _MOVE_STACK_HPP_
#define _MOVE_STACK_HPP_

#include "Chess/chess.hpp"
#include "Graphics/graphics.hpp"

#define MOVE_STACK_LIMIT 1024

using namespace Chess;

class MoveStack {

public:

    MoveStack();
    ~MoveStack();

    int initialize(const std::string starting_fen);

    void clear();

    void addMove(Move move);

    bool isOnLatest();
    Move MoveStack::getLatestMove();

    Move getPriviousMove();
    Move getNextMove();

    void resetMoveIndex();

private:

    std::string _starting_fen;

    int _top;         // this is for internal use of the stack
    int _move_index;  // this is used to index into the history of the game

    Move *_moves;
};

#endif // _MOVE_STACK_HPP_
