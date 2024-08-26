
#ifndef _GRAPHICS_DEFINES_HPP_
#define _GRAPHICS_DEFINES_HPP_

#include "../Chess/chess.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include <stdint.h>
#include <string>
#include <cstring>

// in pixels
constexpr int SQUARE_SIZE = 100;
constexpr int WND_WIDTH = SQUARE_SIZE * BOARD_SIZE;
constexpr int WND_HEIGHT = SQUARE_SIZE * BOARD_SIZE;

namespace Graphics {

typedef uint32_t Color;

} // namespace Graphics

#endif // _GRAPHICS_DEFINES_HPP_
