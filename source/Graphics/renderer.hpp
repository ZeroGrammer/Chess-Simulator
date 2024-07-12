
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "defines.hpp"

namespace Graphics {

class Renderer  {

public:

    Renderer(SDL_Window *window, Dim wnd, Dim board, Dim menu, Dim logs);
    ~Renderer();
    int initialize();

    void setFlippedBoard(bool value);
    void present();

    void clear();
    void fillSquare(Chess::Square square, Color color);
    void renderPieceTexture(Chess::Square square, Chess::Piece piece);

private:

    std::string getPieceFilePath(Chess::Piece piece);

private:

    SDL_Renderer *_renderer;
    Dim _wnd;
    Dim _board;
    Dim _menu;
    Dim _logs;

    bool _is_board_flipped;
};

}

#endif // _RENDERER_HPP_
