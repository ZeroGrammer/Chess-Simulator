
#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include "defines.hpp"

/*
  NOTE(Tejas): the board starts (i.e. when rank = 0 and file = 0) at top left
               square, where there is a White King Side Rook.

  NOTE(Tejas): The conventional Chess considers top right corner to be 0, 0
              (i.e, rank = 1 and file = a), but it ease to visualize rendering
              when using the following way (atleast for me!)... 

                (0) (1) (2) (3) (4) (5) (6) (7)

                 h   g   f   e   d   c   b   a
               +---+---+---+---+---+---+---+---+
        (0)  1 | R | N | B | K | Q | B | N | R |
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
        (7)  8 | r | n | b | k | q | b | n | r |
               +---+---+---+---+---+---+---+---+

  NOTE(Tejas): Flip Board is a pure Visual effect, the white pawns always need
               to promote at the 7th rank and the black pawns always need
               to promote at the 0th rank.

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
    Square getSelectedSquare() const;
    void setSelection(Square square);
    void resetSelection();

    Player getTurn() const;
    void changeTurn();

    Piece getPieceAt(Square square) const;
    void movePiece(Square from, Square to);

    void resetBoard();

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
    
} // namespace Chess

#endif // _BOARD_HPP_
