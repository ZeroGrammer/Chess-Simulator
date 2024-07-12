
#include "renderer.hpp"

using namespace Graphics;

Renderer::Renderer(SDL_Window *window, Dim wnd, Dim board, Dim menu, Dim logs)
    : _renderer(nullptr),
      _wnd(wnd), _board(board), _menu(menu), _logs(logs),
      _is_board_flipped(false)
{
    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer() {

    SDL_DestroyRenderer(_renderer);
}

int Renderer::initialize() {
    
    if (_renderer == nullptr) {
        std::cerr << "Failed to create the SDL Renderer: ";
        std::cerr << SDL_GetError() << std::endl;
        return -1;
    }

    // Set the blend mode for the renderer to enable transparency
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    return 0;
}

void Renderer::setFlippedBoard(bool value) {

    _is_board_flipped = value;
}
void Renderer::present() {
    
    SDL_RenderPresent(_renderer);
}

void Renderer::clear() {
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &_wnd);

    SDL_SetRenderDrawColor(_renderer, 123, 123, 123, 255);
    SDL_RenderDrawRect(_renderer, &_menu);

    SDL_SetRenderDrawColor(_renderer, 53, 53, 53, 255);
    SDL_RenderFillRect(_renderer, &_board);

    SDL_SetRenderDrawColor(_renderer, 121, 32, 189, 32);
    SDL_RenderDrawRect(_renderer, &_logs);
}

void Renderer::fillSquare(Chess::Square square, Color color) {

    SDL_Rect rect;
    // NOTE(Tejas): This filp board check needs to happen only after all the no
    //              board related manipulations are done.
    if (_is_board_flipped) {
        square.file = (BOARD_SIZE - 1) - square.file;
        square.rank = (BOARD_SIZE - 1) - square.rank;
    }
    rect.x = square.file * SQUARE_SIZE;
    rect.y = square.rank * SQUARE_SIZE;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderFillRect(_renderer, &rect);
}

std::string Renderer::getPieceFilePath(Chess::Piece piece) {

    std::string file_path = "./assets/textures/";
    std::string color = (piece.color == Chess::Piece::Color::WHITE) ? "w" : "b";
    std::string extention = ".png";
    std::string type;

    switch (piece.type) {

    case Chess::Piece::Type::PAWN:
        type = "Pawn";
        break;
    case Chess::Piece::Type::KNIGHT:
        type = "Knight";
        break;
    case Chess::Piece::Type::BISHOP:
        type = "Bishop";
        break;
    case Chess::Piece::Type::ROOK:
        type = "Rook";
        break;
    case Chess::Piece::Type::QUEEN:
        type = "Queen";
        break;
    case Chess::Piece::Type::KING:
        type = "King";
        break;
    default:
        std::cerr << "Invalid Piece!\n";
        break;
    }

    file_path = file_path + color + type + extention;

    return file_path;
}

void Renderer::renderPieceTexture(Chess::Square square, Chess::Piece piece) {

    if (piece == Chess::EMPTY_SQUARE) return;

    std::string piece_file_path = getPieceFilePath(piece);

    SDL_Surface *piece_image = IMG_Load(piece_file_path.c_str());
    if (piece_image == nullptr) {
        std::cerr << "Could not open file: " << piece_file_path << "\n";
    }

    SDL_Texture* piece_texture = SDL_CreateTextureFromSurface(_renderer, piece_image);

    SDL_Rect rect;

    // NOTE(Tejas): This filp board check needs to happen only after all the no
    //              board related manipulations are done.
                  
    if (_is_board_flipped) {
        square.file = (BOARD_SIZE - 1) - square.file;
        square.rank = (BOARD_SIZE - 1) - square.rank;
    }
    rect.x = square.file * SQUARE_SIZE;
    rect.y = square.rank * SQUARE_SIZE;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    SDL_RenderCopy(_renderer, piece_texture, NULL, &rect);
    SDL_DestroyTexture(piece_texture);
    SDL_FreeSurface(piece_image);
}
