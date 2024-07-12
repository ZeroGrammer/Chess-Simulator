
#include "board.hpp"

using namespace Chess;

Board::Board() {

    _turn = Player::WHITE;
    _selected_square = OFF_SQUARE;

    // by default assuming that both the rooks have been moved,
    // unless specified otherwise in the fen string
    white.has_king_moved = true;
    white.has_king_rook_moved = true;
    white.has_queen_rook_moved = true;
    black.has_king_moved = true;
    black.has_king_rook_moved = true;
    black.has_queen_rook_moved = true;

    fenReader("RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w QKqk");
}

Board::~Board() {}

void Board::fenReader(const std::string &fen_string)  {

    // fen reading starts form the top right square
    int file = BOARD_SIZE - 1;
    int rank = 0;

    // true when the position on the board is loaded and now additional
    // information about the position is being provided like castling info,
    // whose turn is it and so on...
    bool check_for_addition_data = false;

    for (auto ch : fen_string) {

        if (file < 0) file = BOARD_SIZE - 1;

        if (ch == ' ') {
            check_for_addition_data = true;
            continue;
        }

        if (check_for_addition_data) {

            if (ch == 'Q') {
                white.has_queen_rook_moved = false;
                white.has_king_moved = false;
                continue;
            }

            if (ch == 'q') {
                black.has_queen_rook_moved = false;
                black.has_king_moved = false;
                continue;
            }

            if (ch == 'K') {
                white.has_king_rook_moved = false;
                white.has_king_moved = false;
                continue;
            }

            if (ch == 'k') {
                black.has_king_rook_moved = false;
                black.has_king_moved = false;
                continue;
            }

            if (ch == 'w') {
                _turn = Player::WHITE;
                continue;
            }

            if (ch == 'b') {
                _turn = Player::BLACK;
                continue;
            }
        }

        // new file
        if (ch == '/') {
            rank++;
            file = BOARD_SIZE - 1;
            continue;
        }

        // Empty Squares are indicated by numbers (the number indicates how
        // many of the following squares are going to be blank)
        else if (isdigit(ch)) {
            int empty_squares = static_cast<int>(ch - '0');
            for (int j = 0; j < empty_squares; j++) {
                _board[rank][file] = EMPTY_SQUARE;
                file--;
            }
        }

        // TODO (Tejas): add better invalid char handling here
        else {

            Piece::Color color = std::isupper(ch) ? Piece::Color::WHITE : Piece::Color::BLACK;

            ch = (char)std::tolower(ch);

            Piece::Type type = Piece::Type::NONE;
            switch (ch) {
            case 'p':
                type = Piece::Type::PAWN;
                break;
            case 'n':
                type = Piece::Type::KNIGHT;
                break;
            case 'b':
                type = Piece::Type::BISHOP;
                break;
            case 'r':
                type = Piece::Type::ROOK;
                break;
            case 'q':
                type = Piece::Type::QUEEN;
                break;
            case 'k':
                type = Piece::Type::KING;
                break;
            default:
                break;
            }

            _board[rank][file] = { type, color };
            file--;
        }
    }
}

bool Board::isAnySquareSelected() const {

    return (_selected_square != OFF_SQUARE );
}

Square Board::getSelectedSqaure() const {

    return _selected_square;
}

void Board::setSelection(Square square) {

    _selected_square = square;
}

void Board::resetSelection() {

    _selected_square = OFF_SQUARE;
}

Player Board::getTurn() const {

    return _turn;
}

void Board::changeTurn() {

    _turn = (_turn == Player::WHITE) ? Player::WHITE : Player::BLACK;
}

Piece Board::getPieceAt(Square square) const {

    return _board[square.rank][square.file];
}

void Board::movePiece(Square from, Square to) {

    Piece piece_to_move = getPieceAt(from);
    _board[from.rank][from.file] = EMPTY_SQUARE;
    _board[to.rank][to.file] = piece_to_move;
}

void Board::updatePlayerInfo() {

    if (_turn == Player::WHITE) {

        int rank = 0;

        Piece queen_side_rook = getPieceAt(Square{ rank, 0 });
        Piece king_side_rook = getPieceAt(Square{ rank, 7 });
        Piece king = getPieceAt(Square{ rank, 4 });

        if (queen_side_rook != WHITE_ROOK)
            white.has_queen_rook_moved = true;

        if (king != WHITE_KING)
            white.has_king_moved = true;

        if (king_side_rook != WHITE_ROOK)
            white.has_king_rook_moved = true;
    }

    else {

        int rank = 7;

        Piece queen_side_rook = getPieceAt(Square{ rank, 0 });
        Piece king_side_rook = getPieceAt(Square{ rank, 7 });
        Piece king = getPieceAt(Square{ rank, 4 });

        if (queen_side_rook != BLACK_ROOK)
            white.has_queen_rook_moved = true;

        if (king != BLACK_KING)
            white.has_king_moved = true;

        if (king_side_rook != BLACK_ROOK)
            white.has_king_rook_moved = true;
    }
}

void Board::castleKingSide(Player player) {
    
    int rank = 0;

    if (player == Player::BLACK) rank = 7;

    Square king_pos = { rank, 4 };
    Square rook_pos = { rank, 0 };

    Piece king = getPieceAt(king_pos);
    Piece rook = getPieceAt(rook_pos);

    _board[king_pos.rank][king_pos.file] = EMPTY_SQUARE;
    _board[rook_pos.rank][rook_pos.file] = EMPTY_SQUARE;

    king_pos.file += 2;
    rook_pos.file -= 2;

    _board[king_pos.rank][king_pos.file] = king;
    _board[rook_pos.rank][rook_pos.file] = rook;
}

void Board::castleQueenSide(Player player) {
    
    int rank = 0;

    if (player == Player::BLACK) rank = 7;

    Square king_pos = { rank, 4 };
    Square rook_pos = { rank, 0 };

    Piece king = getPieceAt(king_pos);
    Piece rook = getPieceAt(rook_pos);

    _board[king_pos.rank][king_pos.file] = EMPTY_SQUARE;
    _board[rook_pos.rank][rook_pos.file] = EMPTY_SQUARE;

    king_pos.file -= 2;
    rook_pos.file += 3;

    _board[king_pos.rank][king_pos.file] = king;
    _board[rook_pos.rank][rook_pos.file] = rook;
}

void Board::promotePawn(Square promotion_square, Piece promote_to) {
    
    // assumes that the pawn has already been moved to the promotion square and is
    // waiting to be transformed into a minor piece (promote_to)
    _board[promotion_square.rank][promotion_square.file] = promote_to;
}
