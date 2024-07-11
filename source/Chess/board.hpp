
#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include "defines.hpp"

/*
  NOTE(Tejas): The Chess board is stuctured so that 0, 0 (i.e, rank 0 file a) is
               at the top right, which is the promotion square for black.

                  (7) (6) (5) (4) (3) (2) (1) (0)

                   h   g   f   e   d   c   b   a
                 +---+---+---+---+---+---+---+---+
          (0)  1 | R | B | N | K | Q | B | N | R |
                 +---+---+---+---+---+---+---+---+
          (1)  2 | P | P | P | P | P | P | P | P |
                 +---+---+---+---+---+---+---+---+
          (2)  3 |   |   |   |   |   |   |   |   |
                 +---+---+---+---+---+---+---+---+
          (3)  4 |   |   |   |   |   |   |   |   |
                 +---+---+---+---+---+---+---+---+
          (4)  5 |   |   |   |   |   |   |   |   |
                 +---+---+---+---+---+---+---+---+
          (5)  6 |   |   |   |   |   |   |   |   |
                 +---+---+---+---+---+---+---+---+
          (6)  7 | p | p | p | p | p | p | p | p |
                 +---+---+---+---+---+---+---+---+
          (7)  8 | r | b | n | k | q | b | n | r |
                 +---+---+---+---+---+---+---+---+
 */

    
namespace Chess {

struct PlayerInfo {
    bool has_king_moved;
    bool has_king_rook_moved;
    bool has_queen_rook_moved;
};

class Board {

public:

    Board();
    ~Board();

    void fenReader(const std::string &fenstring);

    bool isAnySquareSelected() const;
    Square getSelectedSqaure() const;
    void setSelection(Square square);
    void resetSelection();

    Player getTurn() const;
    void changeTurn();

    Piece getPieceAt(Square square) const;
    void movePiece(Square from, Square to);

    void updatePlayerInfo();
    void castleKingSide(Player player);
    void castleQueenSide(Player player);

    void promotePawn(Square promotion_square, Piece promote_to);

public:

    PlayerInfo white;
    PlayerInfo black;

private:

    Piece _board[BOARD_SIZE][BOARD_SIZE];
    Square _selected_square;
    Player _turn;
};
    
}

#endif // _BOARD_HPP_
