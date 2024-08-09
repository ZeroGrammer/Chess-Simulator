
#include "move_stack.hpp"

MoveStack::MoveStack()
    : _moves(nullptr), _move_index(-1)
{}

MoveStack::~MoveStack() {

    if (_moves) delete _moves;
}

int MoveStack::initialize(const char *starting_fen) {

    _starting_fen = starting_fen;

    _moves = new Move[MOVE_STACK_LIMIT];
    if (_moves == nullptr) return -1;

    std::memset(_moves, 0, sizeof(Move) * MOVE_STACK_LIMIT);

    return 0;
}

void MoveStack::addMove(Move move) {

    if (!(_move_index < MOVE_STACK_LIMIT)) {
        std::cerr << "Move Stack is full!\n";
        return;
    }

    _moves[++_move_index] = move;
}

Move MoveStack::getPriviousMove() {

    // TODO(Tejas): make it so that it remembers the forward moves

    if (_move_index < 0) {
        Move move = {};
        move.fen = _starting_fen;
        return move;
    }

    return _moves[_move_index--];
}
