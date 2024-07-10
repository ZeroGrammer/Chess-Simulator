
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "input.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdint.h>
#include <iostream>

#define BOARD_WIDTH 800
#define BOARD_HEIGHT 800
#define SQUARE_SIZE (BOARD_HEIGHT / 8)

typedef SDL_Rect Dimention;
typedef uint32_t Color;

namespace Graphics {

const char APPLICATION_NAME[] = "Chess Simulator";

class Window {

public:    

    Window();
    ~Window();

    int initialize();

    void pollEvents();
    void present();

    void clear();

    bool shouldClose() const;

public:

    Keyboard kbd;
    Mouse mouse;

private:

    bool _running;

    Dimention _board;
    Dimention _menu;
    Dimention _logs;
    Dimention _wnd;

    SDL_Window *_window;
    SDL_Renderer *_renderer;
};
    
}

#endif // _WINDOW_HPP
