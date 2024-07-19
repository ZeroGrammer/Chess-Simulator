
#ifndef _GRAPHICS_DEFINES_HPP_
#define _GRAPHICS_DEFINES_HPP_

#include "../Chess/chess.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

#define BOARD_WIDTH 800
#define BOARD_HEIGHT 800
#define SQUARE_SIZE (BOARD_HEIGHT / 8)

namespace Graphics {

typedef SDL_Rect Dim;
typedef uint32_t Color;

} // namespace Graphics

#endif // _GRAPHICS_DEFINES_HPP_
