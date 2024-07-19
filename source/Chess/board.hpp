
#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include "defines.hpp"

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
