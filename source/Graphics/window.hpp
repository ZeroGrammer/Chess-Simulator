
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "defines.hpp"

#include "renderer.hpp"
#include "input.hpp"
#include "log.hpp"

namespace Graphics {

const char APPLICATION_NAME[] = "Chess Simulator";

class Window {

public:    

    Window();
    ~Window();

    int initialize();
    void pollEvents();

    bool shouldClose() const;

    void closeWindow();

    int getWidth() const;
    int getHeight() const;

public:

    Keyboard kbd;
    Mouse mouse;
    Renderer *rend;

private:

    bool _running;

    int _width;
    int _height;

    SDL_Window *_window;
};
    
} // namespace Graphics

#endif // _WINDOW_HPP
