
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "defines.hpp"

#include "renderer.hpp"
#include "input.hpp"

namespace Graphics {

const char APPLICATION_NAME[] = "Chess Simulator";

class Window {

public:    

    Window();
    ~Window();

    int initialize();
    void pollEvents();

    bool shouldClose() const;

public:

    Keyboard kbd;
    Mouse mouse;
    Renderer *rend;

private:

    bool _running;

    Dim _board;
    Dim _menu;
    Dim _logs;
    Dim _wnd;

    SDL_Window *_window;
};
    
}

#endif // _WINDOW_HPP
