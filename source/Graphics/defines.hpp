
#ifndef _GRAPHICS_DEFINES_HPP_
#define _GRAPHICS_DEFINES_HPP_

#include "../Chess/chess.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#define WND_WIDTH 800
#define WND_HEIGHT 800
#define SQUARE_SIZE (WND_HEIGHT / 8)

namespace Graphics {

typedef uint32_t Color;

} // namespace Graphics

#endif // _GRAPHICS_DEFINES_HPP_
