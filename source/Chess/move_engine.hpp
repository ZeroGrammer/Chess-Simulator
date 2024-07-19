
#ifndef _MOVE_ENGINE_HPP_
#define _MOVE_ENGINE_HPP_

#include "defines.hpp"
#include "board.hpp"

namespace Chess {

namespace MoveEngine {

bool isSquareOnTheBoard(Square square);
Square getKingPos(const Board &board, Player player);

// NOTE(Tejas): These functions just check if theres something in between the
//              two give square where the two square are connected either
//              digonally (Bishop path) or straight (Rook path).
bool isBishopPathClear(const Board &board, Square from, Square to);
bool isRookPathClear(const Board &board, Square from, Square to);

bool isUnderAttack(const Board &board, Player player, Square square);
bool isInCheckMate(const Board &board, Player player);

bool isKingSideCastleAllowed(const Board &board, Player player);
bool isQueenSideCastleAllowed(const Board &board, Player player);
Square canCastleKingSide(const Board &board, Player player);
Square canCastleQueenSide(const Board &board, Player player);

// NOTE(Tejas):checks if any pawns are on the promotion square and returns the
//             square of the pawn that needs to be promoted
//             The function returns a Square since we can be sure that every
//             turn the max number of pawn to be promoted is 1 (and min 0)
Square canPromote(const Board &board, Player player);

// to check if a given move (move_from - move_to) is legal by the chess rule
bool isValidMove(const Board &board, Square move_from, Square move_to);

// is the given move (move_from - move_to) puts the self king in check
bool isLegalSquare(const Board &board, Square move_from, Square move_to);

// is a given square (move_to) a valid square for the piece on move_from square
bool isValidSquare(const Board &board, Square move_from, Square move_to);

bool isValidPawnSquare(const Board &board, Square move_from, Square move_to);
bool isValidKnightSquare(const Board &board, Square move_from, Square move_to);
bool isValidBishopSquare(const Board& board, Square move_from, Square move_to);
bool isValidRookSquare(const Board &board, Square move_from, Square move_to);
bool isValidQueenSquare(const Board &board, Square move_from, Square move_to);
bool isValidKingSquare(const Board &board, Square move_from, Square move_to);

} // namespace MoveEngine

} // namespace Chess

#endif _MOVE_ENGINE_HPP_
