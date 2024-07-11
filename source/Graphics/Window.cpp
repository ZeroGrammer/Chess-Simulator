
#include "window.hpp"

using namespace Graphics;

Window::Window()
    : _window(nullptr), _running(true), rend(nullptr) 
{
    _board.x = 0;
    _board.y = 0;
    _board.w = BOARD_WIDTH;
    _board.h = BOARD_HEIGHT;

    _logs.x = 0;
    _logs.y = _board.h;
    _logs.w = _board.w;
    _logs.h = (2 * SQUARE_SIZE);

    _menu.x = _board.w;
    _menu.y = 0;
    _menu.w = (4 * SQUARE_SIZE);
    _menu.h = _board.h + _logs.h;

    _wnd.w = _board.w + _menu.w;
    _wnd.h = _menu.h;
}

Window::~Window() {

    delete rend;
    SDL_DestroyWindow(_window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int Window::initialize() {

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    _window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, _wnd.w, _wnd.h, 0);
    if (_window == nullptr) {
        std::cerr << "Failed to create the SDL Window: ";
        std::cerr << SDL_GetError() << std::endl;
        return -1;
    }

    rend = new Renderer(_window, _wnd, _board, _menu, _logs);
    if (rend->initialize() == -1) return -1;

    std::memset(&kbd, 0, sizeof(Keyboard));
    std::memset(&mouse, 0, sizeof(Keyboard));

    return 0;
}

void Window::pollEvents() {

    SDL_Event event;
    SDL_WaitEvent(&event);

    if (event.type == SDL_QUIT) _running = false;

    // fill the keybord and mouse events here
}

bool Window::shouldClose() const {

    return !_running;
}
