
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "../Chess/defines.hpp"
#include "defines.hpp"

#include <iostream>

namespace Graphics {

class Renderer  {

public:

    Renderer(SDL_Window *window, Dim wnd, Dim board, Dim menu, Dim logs);
    ~Renderer();
    int initialize();

    void present();

    void clear();
    void fillSquare(Square square, Color color);

private:

    SDL_Renderer *_renderer;
    Dim _wnd;
    Dim _board;
    Dim _menu;
    Dim _logs;
};

}

#endif // _RENDERER_HPP_
