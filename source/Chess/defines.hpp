
#ifndef _CHESS_DEFINES_HPP
#define _CHESS_DEFINES_HPP

#define BOARD_SIZE 8

// Location of a square on the board
struct Square {

    int rank;
    int file;

    inline bool operator==(const Square& square) {
        return (rank == square.rank && file == square.file);
    }
    inline bool operator!=(const Square& square) {
        return (rank != square.rank || file != square.file);
    }
};

constexpr Square OFF_SQUARE = { -1, -1 };

struct Piece {

    enum class Type {
        NONE,
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    } type;

    enum class Color {
        NONE,
        WHITE,
        BLACK
    } color;

    inline bool operator==(const Piece& piece) const {
        return (type == piece.type && color == piece.color);
    }

    inline bool operator!=(const Piece& piece) const {
        return (type != piece.type || color != piece.color);
    }
};

#endif // _CHESS_DEFINES_HPP
