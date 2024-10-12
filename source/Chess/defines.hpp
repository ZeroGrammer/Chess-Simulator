
#ifndef _CHESS_DEFINES_HPP
#define _CHESS_DEFINES_HPP

#include <iostream>
#include <string>
#include <vector>

namespace Chess {

#define BOARD_SIZE 8
    
// Location of a square on the board
struct Square {

    int rank;
    int file;

    inline bool operator==(const Square &square) const {
        return (rank == square.rank && file == square.file);
    }
    inline bool operator!=(const Square &square) const {
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

constexpr Piece EMPTY_SQUARE = { Piece::Type::NONE  , Piece::Color::NONE  };
constexpr Piece WHITE_PAWN   = { Piece::Type::PAWN  , Piece::Color::WHITE };
constexpr Piece BLACK_PAWN   = { Piece::Type::PAWN  , Piece::Color::BLACK };
constexpr Piece WHITE_KNIGHT = { Piece::Type::KNIGHT, Piece::Color::WHITE };
constexpr Piece BLACK_KNIGHT = { Piece::Type::KNIGHT, Piece::Color::BLACK };
constexpr Piece WHITE_BISHOP = { Piece::Type::BISHOP, Piece::Color::WHITE };
constexpr Piece BLACK_BISHOP = { Piece::Type::BISHOP, Piece::Color::BLACK };
constexpr Piece WHITE_ROOK   = { Piece::Type::ROOK  , Piece::Color::WHITE };
constexpr Piece BLACK_ROOK   = { Piece::Type::ROOK  , Piece::Color::BLACK };
constexpr Piece WHITE_QUEEN  = { Piece::Type::QUEEN , Piece::Color::WHITE };
constexpr Piece BLACK_QUEEN  = { Piece::Type::QUEEN , Piece::Color::BLACK };
constexpr Piece WHITE_KING   = { Piece::Type::KING  , Piece::Color::WHITE };
constexpr Piece BLACK_KING   = { Piece::Type::KING  , Piece::Color::BLACK };

typedef Piece::Color Player;

} // namespace Chess

#endif // _CHESS_DEFINES_HPP
