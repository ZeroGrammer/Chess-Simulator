
#include "move_engine.hpp"

using namespace Chess;

bool MoveEngine::isSquareOnTheBoard(Square square) {

    return ((square.rank >= 0 && square.rank < BOARD_SIZE) &&
            (square.file >= 0 && square.file < BOARD_SIZE));
}

Square MoveEngine::getKingPos(const Board &board, Player player) {
    
    Piece king = (player == Player::WHITE) ? WHITE_KING : BLACK_KING;
    Square king_pos = OFF_SQUARE;

    for (int rank = 0; rank < BOARD_SIZE; rank++) {
        for (int file = 0; file < BOARD_SIZE; file++) {

            if (board.getPieceAt({ rank, file }) == king) {
                king_pos = Square{ rank, file };
                break;
            }
        }
    }

    return king_pos;
}

bool MoveEngine::isBishopPathClear(const Board &board, Square from, Square to) {

    // TODO(Tejas): check if the from to to square is acutally a bishops path

    int d_rank = (to.rank < from.rank) ? -1 : 1;
    int d_file = (to.file < from.file) ? -1 : 1;

    from.rank += d_rank;
    from.file += d_file;

    while (from != to) {

        // if a piece detected in the path
        if (board.getPieceAt(from) != EMPTY_SQUARE) return true;

        // increment towards the to Square
        from.rank += d_rank;
        from.file += d_file;
    }

    return false;
    
}

bool MoveEngine::isRookPathClear(const Board &board, Square from, Square to) {
    
    // TODO: check if the from to to square is acutally a rooks path

    // checking horizontally
    if (from.rank == to.rank) {

        int d_file = (to.file < from.file) ? -1 : 1;

        from.file += d_file;

        while (from != to) {

            // if there is a piece detected in the path
            if (board.getPieceAt(from) != EMPTY_SQUARE) return true;

            // increment towards the to square
            from.file += d_file;
        }
    }

    // checking vertically
    else if (from.file == to.file) {

        int d_rank = (to.rank < from.rank) ? -1 : 1;

        from.rank += d_rank;

        while (from != to) {

            // if there is a piece detected in the path
            if (board.getPieceAt(from) != EMPTY_SQUARE) return true;

            // increment towards the to square
            from.rank += d_rank;
        }
    }

    return false;
}

bool MoveEngine::isUnderAttack(const Board &board, Player player, Square square) {
    
    for (int rank = 0; rank < BOARD_SIZE; rank++) {

        for (int file = 0; file < BOARD_SIZE; file++) {

            Square current_square = { rank ,file };
            Piece current_piece = board.getPieceAt(current_square);

            if (current_piece != EMPTY_SQUARE &&
                current_piece.color != player) {

                if (isValidSquare(board, current_square, square)) return true;
            }
        }
    }

    return false;
}

bool MoveEngine::isInCheckMate(const Board &board, Player player) {

    Square king_pos = getKingPos(board, player);
    if (!isUnderAttack(board, player, king_pos)) return false;

    for (int rank = 0; rank < BOARD_SIZE; rank++) {

        for (int file = 0; file < BOARD_SIZE; file++) {

            Piece current_piece = board.getPieceAt(Square{ rank, file });
            Square current_square = { rank, file };

            if (current_piece == EMPTY_SQUARE) continue;

            if (current_piece.color != player) continue;

            for (int rank2 = 0; rank2 < BOARD_SIZE; rank2++) {
    
                for (int file2 = 0; file2 < BOARD_SIZE; file2++) {

                    if (MoveEngine::isValidSquare(board, current_square, { rank2, file2 }) &&
                        MoveEngine::isLegalSquare(board, current_square, { rank2, file2 }))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool MoveEngine::isKingSideCastleAllowed(const Board &board, Player player) {
    
    int rank = 0;
    int file = 3;

    if (player == Player::BLACK) rank = 7;

    // check first if any of the king or the rook have moved previously
    if (player == Player::WHITE) {

        if (board.white.has_king_rook_moved || board.white.has_king_moved)
            return false;

    } else {

        if (board.black.has_king_rook_moved || board.black.has_king_moved)
            return false;
    }

    // cannot castle if the king is in check 
    Square king_pos = MoveEngine::getKingPos(board, player);
    if (MoveEngine::isUnderAttack(board, player, king_pos)) return false;

    file -= 1;

    while (file > 0) {

        // NOTE(Tejas): squares between the rook and the king should be empty
        //              and no square that king needs to move should be under threat

        Square current_square = { rank, file };

        // checks if there are pieces in between the king and the rook
        if (board.getPieceAt(current_square) != EMPTY_SQUARE) return false;

        // checks if the current square is under attack
        if (MoveEngine::isUnderAttack(board, player, current_square)) return false;

        file -= 1;
    }

    return true;
}

bool MoveEngine::isQueenSideCastleAllowed(const Board &board, Player player) {
    
    int rank = 0;
    int file = 3; 

    if (player == Player::BLACK) rank = 7;

    // check first if any of the king or the rook have moved previously
    if (player == Player::WHITE) {

        if (board.white.has_queen_rook_moved || board.white.has_king_moved)
            return false;

    } else {

        if (board.black.has_queen_rook_moved || board.black.has_king_moved)
            return false;
    }

    Square king_pos = MoveEngine::getKingPos(board, player);
    if (MoveEngine::isUnderAttack(board, player, king_pos)) return false;

    file += 1;

    while (file < 6) {

        // NOTE(Tejas): squares between the rook and the king should be empty
        //              and no square that king needs to move should be under threat

        Square current_square = { rank, file };

        if (board.getPieceAt(current_square) != EMPTY_SQUARE) return false;
        if (MoveEngine::isUnderAttack(board, player, current_square)) return false;

        file += 1;
    }

    return true;
}

Square MoveEngine::canCastleKingSide(const Board &board, Player player) {
    
    bool is_king_side_castle_allowed = MoveEngine::isKingSideCastleAllowed(board, player);

    Square square = OFF_SQUARE;

    if (is_king_side_castle_allowed) {

        if (player == Player::WHITE) square = { 0, 1 };

        if (player == Player::BLACK) square = { 7, 1 };
    }

    return square;
}

Square MoveEngine::canCastleQueenSide(const Board &board, Player player) {
    
    bool is_queen_side_castle_allowed = MoveEngine::isQueenSideCastleAllowed(board, player);

    Square square = OFF_SQUARE;

    if (is_queen_side_castle_allowed) {

        if (player == Player::WHITE) square = { 0, 5 };

        if (player == Player::BLACK) square = { 7, 5 };
    }

    return square;
}

Square MoveEngine::canEnPassant(const Board &board, Square pawn_square, Move prev_move) {

    Player player = board.getPieceAt(pawn_square).color;

    Square last_move_from = prev_move.squares.from;
    Square last_move_to = prev_move.squares.to;
    Piece last_move_piece = prev_move.piece;

    if (last_move_piece.type != Piece::Type::PAWN) return OFF_SQUARE;

    if (player == Player::WHITE) {

        // if (last_move_to.rank - last_move_from.rank < 2) return OFF_SQUARE;

        if (last_move_to.rank == pawn_square.rank &&
            (last_move_to.file == pawn_square.file + 1 || last_move_to.file == pawn_square.file - 1))
        {
            return Square { last_move_to.rank + 1, last_move_to.file };
        }
    }

    if (player == Player::BLACK) {

        // if (last_move_from.rank - last_move_to.rank < 2) return OFF_SQUARE;

        if (last_move_to.rank == pawn_square.rank &&
            (last_move_to.file == pawn_square.file + 1 || last_move_to.file == pawn_square.file - 1))
        {
            return Square { last_move_to.rank - 1, last_move_to.file };
        }
    }

    return OFF_SQUARE;
}


Square MoveEngine::canPromote(const Board &board, Player player) {
    
    Square promotion_square = OFF_SQUARE;
    int rank = 7;

    if (player == Player::BLACK) rank = 0;

    for (int file = 0; file < BOARD_SIZE; file++) {

        Square current_square = { rank, file };
        Piece::Type piece_type = board.getPieceAt(current_square).type;

        if (piece_type == Piece::Type::PAWN) {
            promotion_square = current_square;
            break;
        }
    }

    return promotion_square;
}

bool MoveEngine::isValidMove(const Board &board, Square move_from, Square move_to) {
    
    // NOTE(Tejas): A function to check if a given move is a valid move of the piece
    //              and it does not put the self king in danger (in check)

    bool isValid = MoveEngine::isValidSquare(board, move_from, move_to);
    bool isLegal = MoveEngine::isLegalSquare(board, move_from, move_to);

    return (isValid && isLegal);
}

bool MoveEngine::isLegalSquare(const Board &board, Square move_from, Square move_to) {

    // NOTE(Tejas): This function checks if the given move (move_from - move_to)
    //              puts the self king in check

    // TODO(Tejas): This does not seem necessary but at the moment cant think of
    //              anything else so leaving this todo here to comeback to here...
    Board copy_board = board;

    Player player = board.getPieceAt(move_from).color;
    copy_board.movePiece(move_from, move_to);

    Square king_pos = MoveEngine::getKingPos(copy_board, player);
    if (MoveEngine::isUnderAttack(copy_board, player, king_pos)) return false;

    return true;
}

bool MoveEngine::isValidSquare(const Board &board, Square move_from, Square move_to) {

    // NOTE(Tejas): This function check if the give move is a move that the
    //              piece on move_from square make.

    Piece piece_to_move = board.getPieceAt(move_from);

    if (!MoveEngine::isSquareOnTheBoard(move_from) ||
        !MoveEngine::isSquareOnTheBoard(move_to))
        return false;

    // cant capture your own piece
    if ((board.getPieceAt(move_to).color == piece_to_move.color))
        return false;

    bool result = false;

    switch (piece_to_move.type) {

    case Piece::Type::PAWN:
        result = MoveEngine::isValidPawnSquare(board, move_from, move_to);
        break;
    case Piece::Type::KNIGHT:
        result = MoveEngine::isValidKnightSquare(board, move_from, move_to);
        break;
    case Piece::Type::BISHOP:
        result = MoveEngine::isValidBishopSquare(board, move_from, move_to);
        break;
    case Piece::Type::ROOK:
        result = MoveEngine::isValidRookSquare(board, move_from, move_to);
        break;
    case Piece::Type::QUEEN:
        result = MoveEngine::isValidQueenSquare(board, move_from, move_to);
        break;
    case Piece::Type::KING:
        result = MoveEngine::isValidKingSquare(board, move_from, move_to);
        break;
    default:
        break;
    }

    return result;
}

bool MoveEngine::isValidPawnSquare(const Board &board, Square move_from, Square move_to) {
    
    Piece piece_to_move = board.getPieceAt(move_from);

    // NOTE(Tejas): White is forwarding in +1 and Black is forwarding in -1
    int direction = (piece_to_move.color == Player::WHITE) ? 1 : -1;

    // Checking validation one square in front of the pawn
    if (move_to.rank == (move_from.rank + direction) &&
        move_to.file == move_from.file) {

        if (board.getPieceAt(move_to) == EMPTY_SQUARE)
            return true;
    }

    // Checking validation two square in front of the pawn if the pawn is on the 2nd or the 6th rank
    if (move_from.rank == 1 || move_from.rank == 6) {

        if ((move_to.rank == (move_from.rank + (2 * direction))) &&
            (move_to.file == move_from.file)) {

            if ((board.getPieceAt(move_to) == EMPTY_SQUARE) &&
                (board.getPieceAt({ move_to.rank - direction, move_to.file }) == EMPTY_SQUARE)) {

                return true;
            }
        }
    }

    // Diagonal captures of the Pawn
    // left diagonal
    if ((move_to.rank == move_from.rank + direction) &&
        (move_to.file == move_from.file - 1)) {

        if ((board.getPieceAt(move_to) != EMPTY_SQUARE) &&
            (board.getPieceAt(move_to).color != piece_to_move.color)) {

            return true;
        }
    }

    // right capture
    if ((move_to.rank == move_from.rank + direction) &&
        (move_to.file == move_from.file + 1)) {

        if ((board.getPieceAt(move_to) != EMPTY_SQUARE) &&
            (board.getPieceAt(move_to).color != piece_to_move.color)) {

            return true;
        }
    }

    return false;
}

bool MoveEngine::isValidKnightSquare(const Board &board, Square move_from, Square move_to) {
    
    (void) board;

    // all possible square for a knight to move from its position
    int d_rank[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
    int d_file[] = { -1, 1, 2, -2, -2, 2, -1, 1 };

    // 8 possible squares that a knight can move to
    for (int i = 0; i < 8; i++) {

        if ((move_to.rank == move_from.rank + d_rank[i]) &&
            (move_to.file == move_from.file + d_file[i])) {

            return true;
        }
    }

    return false;
}

bool MoveEngine::isValidBishopSquare(const Board &board, Square move_from, Square move_to) {
    
    if (std::abs(move_from.file - move_to.file) ==
        std::abs(move_from.rank - move_to.rank)) {

        if (!MoveEngine::isBishopPathClear(board, move_from, move_to))
            return true;
    }

    return false;
}

bool MoveEngine::isValidRookSquare(const Board &board, Square move_from, Square move_to) {
    
    if (move_from.rank == move_to.rank || move_from.file == move_to.file) {

        if (!MoveEngine::isRookPathClear(board, move_from, move_to))
            return true;
    }

    return false;
}

bool MoveEngine::isValidQueenSquare(const Board &board, Square move_from, Square move_to) {
    
    bool isValidBisop = MoveEngine::isValidBishopSquare(board, move_from, move_to);
    bool isValidRook = MoveEngine::isValidRookSquare(board, move_from, move_to);

    if (isValidBisop || isValidRook) return true;

    return false;
}

bool MoveEngine::isValidKingSquare(const Board &board, Square move_from, Square move_to) {
    
    (void) board;

    // all possible squares for a king to move from its position
    int d_rank[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int d_file[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    // 8 possible squares that a king can move to (not considering castling)
    for (int i = 0; i < 8; i++) {

        if ((move_to.rank == move_from.rank + d_rank[i]) &&
            (move_to.file == move_from.file + d_file[i])) {

            return true;
        }
    }

    return false;
}
