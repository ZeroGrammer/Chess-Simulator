
#include "window.hpp"

using namespace Graphics;

Window::Window()
    : _window(nullptr), _running(true), rend(nullptr) 
{
    _width = WND_WIDTH;
    _height = WND_HEIGHT;
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
                               SDL_WINDOWPOS_UNDEFINED, _width, _height, 0);
    if (_window == nullptr) {
      log(ERR, "Failed to create the SDL Window: %s", SDL_GetError());
      return -1;
    }

    std::memset(&kbd, 0, sizeof(Keyboard));
    std::memset(&mouse, 0, sizeof(Keyboard));

    rend = new Renderer(_window);
    if (rend->initialize() == -1) return -1;

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

        if (key_pressed == SDLK_1) {
            kbd.piece_type = Keyboard::PieceType::QUEEN;
            kbd.type = Keyboard::Type::PROMOTE_TO;
        }

        if (key_pressed == SDLK_2) {
            kbd.piece_type = Keyboard::PieceType::ROOK;
            kbd.type = Keyboard::Type::PROMOTE_TO;
        }

        if (key_pressed == SDLK_3) {
            kbd.piece_type = Keyboard::PieceType::BISHOP;
            kbd.type = Keyboard::Type::PROMOTE_TO;
        }

        if (key_pressed == SDLK_4) {
            kbd.piece_type = Keyboard::PieceType::KNIGHT;
            kbd.type = Keyboard::Type::PROMOTE_TO;
        }

        if (key_pressed == SDLK_ESCAPE) {
            kbd.type = Keyboard::Type::TOGGLE_MENU;
        }

        if (key_pressed == SDLK_LEFT) {
            kbd.type = Keyboard::Type::PREVIOUS_MOVE;
        }

        if (key_pressed == SDLK_RIGHT) {
            kbd.type = Keyboard::Type::NEXT_MOVE;
        }

        if (key_pressed == SDLK_r) {
            kbd.type = Keyboard::Type::LATEST_MOVE;
        }

        if (key_pressed == SDLK_UP) {
            kbd.type = Keyboard::Type::PREVIOUS_ITEM;
        }

        if (key_pressed == SDLK_DOWN) {
            kbd.type = Keyboard::Type::NEXT_ITEM;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {

        SDL_MouseButtonEvent mouse_event = event.button;

        mouse.x = mouse_event.x;
        mouse.y = mouse_event.y;

        if (mouse_event.button == SDL_BUTTON_RIGHT)
            mouse.type = Mouse::Type::RCLICK;

        if (mouse_event.button == SDL_BUTTON_LEFT)
            mouse.type = Mouse::Type::LCLICK;
    }
}

bool Window::shouldClose() const {

    return !_running;
}
