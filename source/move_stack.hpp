
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

    int initialize(const char *starting_fen);

    void clear();

    void addMove(Move move);

    bool isOnLatest();
    Move MoveStack::getLatestMove();

    Move getPriviousMove();

    void resetMoveIndex();

private:

    const char *_starting_fen;

    int _top;         // this is for internal use of the stack
    int _move_index;  // this is used to index into the history of the game

    Move *_moves;
};

#endif // _MOVE_STACK_HPP_