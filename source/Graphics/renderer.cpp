
#include "renderer.hpp"

using namespace Graphics;

Renderer::Renderer(SDL_Window *window, Dim wnd, Dim board, Dim menu, Dim logs)
    : _renderer(nullptr), _wnd(wnd), _board(board), _menu(menu), _logs(logs)
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

    SDL_Rect rect = { square.file * SQUARE_SIZE,
                      square.rank * SQUARE_SIZE,
                      SQUARE_SIZE, SQUARE_SIZE};

    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderFillRect(_renderer, &rect);
}
