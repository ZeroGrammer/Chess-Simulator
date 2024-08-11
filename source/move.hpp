
#ifndef _MOVE_HPP_
#define _MOVE_HPP_

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

#endif // _MOVE_HPP_
