
#ifndef _MOVE_STACK_HPP_
#define _MOVE_STACK_HPP_

#include "Chess/chess.hpp"

#define MOVE_STACK_LIMIT 1024

struct Move {

    Chess::Player player;    // the player who made the move
    const char* fen;  // The Fen of the board after this move was made

    // NOTE(Tejas): for castling move the 'from' and 'to'
    //              will be refering to the kigs position
    struct Squares {
        Chess::Square from;
        Chess::Square to;
    } squares;

    // NOTE(Tejas): this struct is only relevent if the
    //              is_castling flag is set to true
    bool is_castle;
    struct Castling {
        bool is_queen_side;
        bool is_king_side;
    } castle;

    bool is_promotion;
    bool is_enpassent;
};

class MoveStack {

public:

    MoveStack();
    ~MoveStack();

    int initialize(const char *starting_fen);

    void addMove(Move move);
    Move getPriviousMove();

private:

    const char *_starting_fen;

    int _move_index;
    Move *_moves;
};

#endif // _MOVE_STACK_HPP_
