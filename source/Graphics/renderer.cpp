
#include "renderer.hpp"

using namespace Graphics;

Renderer::Renderer(SDL_Window *window)
    : _renderer(nullptr), _is_flipped(false)
{
    _screen = { 0, 0, WND_WIDTH, WND_HEIGHT };
    _renderer = SDL_CreateRenderer(window, -1, 0);
}

Renderer::~Renderer() {

    SDL_DestroyTexture(_piece_textures.wPawn);
    SDL_DestroyTexture(_piece_textures.wKnight);
    SDL_DestroyTexture(_piece_textures.wBishop);
    SDL_DestroyTexture(_piece_textures.wRook);
    SDL_DestroyTexture(_piece_textures.wQueen);
    SDL_DestroyTexture(_piece_textures.wKing);
    
    SDL_DestroyTexture(_piece_textures.bPawn);
    SDL_DestroyTexture(_piece_textures.bKnight);
    SDL_DestroyTexture(_piece_textures.bBishop);
    SDL_DestroyTexture(_piece_textures.bRook);
    SDL_DestroyTexture(_piece_textures.bQueen);
    SDL_DestroyTexture(_piece_textures.bKing);

    TTF_CloseFont(_menu_font.bold);
    TTF_CloseFont(_menu_font.regular);
    TTF_CloseFont(_menu_font.small);

    SDL_DestroyRenderer(_renderer);
}

int Renderer::initialize() {
    
    if (_renderer == nullptr) {
        log(ERR, "Failed to create the SDL Renderer: %s", SDL_GetError());
        return -1;
    }

    // Set the blend mode for the renderer to enable transparency
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    _piece_textures.wPawn   = loadTexture(getPieceFilePath(Chess::WHITE_PAWN).c_str());
    _piece_textures.wKnight = loadTexture(getPieceFilePath(Chess::WHITE_KNIGHT).c_str());
    _piece_textures.wBishop = loadTexture(getPieceFilePath(Chess::WHITE_BISHOP).c_str());
    _piece_textures.wRook   = loadTexture(getPieceFilePath(Chess::WHITE_ROOK).c_str());
    _piece_textures.wQueen  = loadTexture(getPieceFilePath(Chess::WHITE_QUEEN).c_str());
    _piece_textures.wKing   = loadTexture(getPieceFilePath(Chess::WHITE_KING).c_str());

    _piece_textures.bPawn   = loadTexture(getPieceFilePath(Chess::BLACK_PAWN).c_str());
    _piece_textures.bKnight = loadTexture(getPieceFilePath(Chess::BLACK_KNIGHT).c_str());
    _piece_textures.bBishop = loadTexture(getPieceFilePath(Chess::BLACK_BISHOP).c_str());
    _piece_textures.bRook   = loadTexture(getPieceFilePath(Chess::BLACK_ROOK).c_str());
    _piece_textures.bQueen  = loadTexture(getPieceFilePath(Chess::BLACK_QUEEN).c_str());
    _piece_textures.bKing   = loadTexture(getPieceFilePath(Chess::BLACK_KING).c_str());


    _menu_font.bold    = TTF_OpenFont("./assets/fonts/Hermit-Bold.otf", 34);
    _menu_font.regular = TTF_OpenFont("./assets/fonts/Hermit-Regular.otf", 30);
    _menu_font.small   = TTF_OpenFont("./assets/fonts/Hermit-Regular.otf", 22);

    // _menu_font.bold    = TTF_OpenFont("./assets/fonts/CONSOLAB.ttf", 30);
    // _menu_font.regular = TTF_OpenFont("./assets/fonts/CONSOLA.ttf", 30);
    // _menu_font.small   = TTF_OpenFont("./assets/fonts/CONSOLA.ttf", 24);

    if (_menu_font.bold == nullptr || _menu_font.regular == nullptr) {
        log(ERR, "Failed while loading on or more fonts");
        return -1;
    }


    return 0;
}

void Renderer::setIsFlipped(bool value) {

    _is_flipped = value;
}

Chess::Square Renderer::pixelToBoardConverter(int pixel_x, int pixel_y) {

    Chess::Square square = {};

    square.file = pixel_x / SQUARE_SIZE;
    square.rank = pixel_y / SQUARE_SIZE;
    if (_is_flipped) {
        square.file = (BOARD_SIZE - 1) - square.file;
        square.rank = (BOARD_SIZE - 1) - square.rank;
    }

    return square;
}

void Renderer::present() {
    
    SDL_RenderPresent(_renderer);
}

void Renderer::clear(Color color) {
    
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderFillRect(_renderer, &_screen);

    // SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    // SDL_RenderDrawLine(_renderer, _screen.w / 2, 0, _screen.w / 2, _screen.h);
}

void Renderer::fillSquare(Chess::Square square, Color color) {

    SDL_Rect rect;

    // NOTE(Tejas): This filp board check needs to happen only after all the no
    //              board related manipulations are done.
    if (_is_flipped) {
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

SDL_Texture* Renderer::getPieceTexture(Chess::Piece piece) {

    SDL_Texture *texture = nullptr;

    if (piece == Chess::WHITE_PAWN)   texture = _piece_textures.wPawn;
    if (piece == Chess::WHITE_KNIGHT) texture = _piece_textures.wKnight;
    if (piece == Chess::WHITE_BISHOP) texture = _piece_textures.wBishop;
    if (piece == Chess::WHITE_ROOK)   texture = _piece_textures.wRook;
    if (piece == Chess::WHITE_QUEEN)  texture = _piece_textures.wQueen;
    if (piece == Chess::WHITE_KING)   texture = _piece_textures.wKing;

    if (piece == Chess::BLACK_PAWN)   texture = _piece_textures.bPawn;
    if (piece == Chess::BLACK_KNIGHT) texture = _piece_textures.bKnight;
    if (piece == Chess::BLACK_BISHOP) texture = _piece_textures.bBishop;
    if (piece == Chess::BLACK_ROOK)   texture = _piece_textures.bRook;
    if (piece == Chess::BLACK_QUEEN)  texture = _piece_textures.bQueen;
    if (piece == Chess::BLACK_KING)   texture = _piece_textures.bKing;

    return texture;
}

SDL_Texture* Renderer::loadTexture(const char *file_path) {

    SDL_Surface *image = IMG_Load(file_path);

    if (image == nullptr) {
        log(ERR, "Could not open file: %s", file_path);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, image);

    if (texture == nullptr) {
        log(ERR, "Could not load the texture from: %s", file_path);
        return nullptr;
    }

    SDL_FreeSurface(image);
    return texture;
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

    SDL_Texture* piece_texture = getPieceTexture(piece);

    SDL_Rect rect = { };

    // NOTE(Tejas): This filp board check needs to happen only after all the
    //              board related manipulations are done.
    if (_is_flipped) {
        square.file = (BOARD_SIZE - 1) - square.file;
        square.rank = (BOARD_SIZE - 1) - square.rank;
    }

    rect.x = square.file * SQUARE_SIZE;
    rect.y = square.rank * SQUARE_SIZE;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    SDL_RenderCopy(_renderer, piece_texture, NULL, &rect);
}

void Renderer::drawText(FontType font_type, const char *text, Rect position, Color text_color) {

    // SDL_SetRenderDrawColor(_renderer, 18, 18, 18, 255);
    // SDL_RenderFillRect(_renderer, &position);

    uint8_t r = (text_color >> 24) & 0xFF;
    uint8_t g = (text_color >> 16) & 0xFF;
    uint8_t b = (text_color >> 8) & 0xFF;
    uint8_t a = text_color & 0xFF;

    SDL_Color c = { r, g, b, a };

    TTF_Font *font = _menu_font.regular;
    if (font_type == BOLD) font = _menu_font.bold;
    if (font_type == SMALL) font = _menu_font.small;

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, c);
    if (surface == nullptr) {
        log(ERR, "Could not create surface while loading the Bold font for text \"%s\"", text);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == nullptr) {
        log(ERR, "Could not create the texture from surface for text \"%s\"", text);
        return;
    }

    SDL_FreeSurface(surface);

    SDL_RenderCopy(_renderer, texture, NULL, &position);
    SDL_DestroyTexture(texture);
}

void Renderer::displayFog(Color color) {
    
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderFillRect(_renderer, &_screen);
}
