
#include "move_stack.hpp"

MoveStack::MoveStack()
    : _moves(nullptr), _top(-1), _move_index(-1)
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

void MoveStack::clear() {
    
    std::memset(_moves, 0, sizeof(Move) * MOVE_STACK_LIMIT);
    _top = -1;
    _move_index = -1;
}

void MoveStack::addMove(Move move) {

    if (!(_top < MOVE_STACK_LIMIT)) {
        Graphics::log(Graphics::ERR, "Move Stack is full!");
        return;
    }

    _moves[++_top] = move;
    _move_index = _top;
}

bool MoveStack::isOnLatest() {

    if (_move_index == _top) return true;
    else return false;
}

Move MoveStack::getLatestMove() {

    if (_top == -1) {
        Move move = {};
        move.fen = _starting_fen;
        return move;
    }

    _move_index = _top;
    return _moves[_move_index];
}

Move MoveStack::getPriviousMove() {

    if (_move_index <= 0) {
        Move move = {};
        move.fen = _starting_fen;
        return move;
    }

    return _moves[--_move_index];
}

void MoveStack::resetMoveIndex() {

    _move_index = _top;
}
