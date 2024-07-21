
#include "window.hpp"

using namespace Graphics;

Window::Window()
    : _window(nullptr), _running(true), rend(nullptr) 
{
    _board.x = 0;
    _board.y = 0;
    _board.w = BOARD_WIDTH;
    _board.h = BOARD_HEIGHT;

    _menu.x = _board.w;
    _menu.y = 0;
    _menu.w = 3 * SQUARE_SIZE;
    _menu.h = _board.h;

    _wnd.w = _board.w + _menu.w;
    _wnd.h = _board.h;
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

    rend = new Renderer(_window, _wnd, _board, _menu);
    if (rend->initialize() == -1) return -1;

    std::memset(&kbd, 0, sizeof(Keyboard));
    std::memset(&mouse, 0, sizeof(Keyboard));

    return 0;
}

void Window::pollEvents() {

    std::memset(&kbd, 0, sizeof(Keyboard));
    std::memset(&mouse, 0, sizeof(Keyboard));

    SDL_Event event;
    SDL_WaitEvent(&event);

    if (event.type == SDL_QUIT) _running = false;

    if (event.type == SDL_KEYDOWN) {

        SDL_Keycode key_pressed = event.key.keysym.sym;

        if (key_pressed == SDLK_f)
            kbd.type = Keyboard::Type::FLIP_BOARD;

        if (key_pressed == SDLK_x)
            kbd.type = Keyboard::Type::RESET_BOARD;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {

        SDL_MouseButtonEvent mouse_event = event.button;

        mouse.x = mouse_event.x;
        mouse.y = mouse_event.y;

        if (mouse_event.button == SDL_BUTTON_RIGHT) {

            // TODO(Tejas): Improv these check, they feel really hack at the moment

            if (mouse.x > _board.x && mouse.y > _board.y &&
                mouse.x < _board.w && mouse.y < _board.h)
            {
                mouse.type = Mouse::Type::RBOARD;
            }

            if (mouse.x > _menu.x && _menu.y > _menu.y &&
                mouse.x < (_menu.w + _board.w) && mouse.y < _menu.h)
            {
                mouse.type = Mouse::Type::RMENU;
            }
        }

        if (mouse_event.button == SDL_BUTTON_LEFT) {

            // TODO(Tejas): Improv these check, they feel really hack at the moment

            if (mouse.x > _board.x && mouse.y > _board.y &&
                mouse.x < _board.w && mouse.y < _board.h)
            {
                mouse.type = Mouse::Type::LBOARD;
            }

            if (mouse.x > _menu.x && mouse.y > _menu.y &&
                mouse.x < (_menu.w + _board.w) && mouse.y < _menu.h)
            {
                mouse.type = Mouse::Type::LMENU;
            }
        }
    }
}

bool Window::shouldClose() const {

    return !_running;
}
