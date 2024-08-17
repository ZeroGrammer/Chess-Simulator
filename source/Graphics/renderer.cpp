
#include "renderer.hpp"

using namespace Graphics;

Renderer::Renderer(SDL_Window *window)
    : _renderer(nullptr), _is_board_flipped(false)
{

    _screen = { 0, 0, WND_WIDTH, WND_HEIGHT };
    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer() {

    SDL_DestroyRenderer(_renderer);
}

int Renderer::initialize() {
    
    if (_renderer == nullptr) {
        log(ERR, "Failed to create the SDL Renderer: %s", SDL_GetError());
        return -1;
    }

    // Set the blend mode for the renderer to enable transparency
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    return 0;
}

void Renderer::setFlippedBoard(bool value) {

    _is_board_flipped = value;
}

Chess::Square Renderer::pixelToBoardConverter(int pixel_x, int pixel_y) {

    Chess::Square square = {};
    square.file = pixel_x / SQUARE_SIZE;
    square.rank = pixel_y / SQUARE_SIZE;
    if (_is_board_flipped) {
        square.file = (BOARD_SIZE - 1) - square.file;
        square.rank = (BOARD_SIZE - 1) - square.rank;
    }

    return square;
}

void Renderer::present() {
    
    SDL_RenderPresent(_renderer);
}

void Renderer::clear() {
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &_screen);
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
        log(ERR, "Invalid Piece!");
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
        log(ERR, "Could not open file: %s", piece_file_path.c_str());
    }

    SDL_Texture* piece_texture = SDL_CreateTextureFromSurface(_renderer, piece_image);

    SDL_Rect rect;

    // NOTE(Tejas): This filp board check needs to happen only after all the
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

void Renderer::displayFog(Color color) {
    
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderFillRect(_renderer, &_screen);
}
