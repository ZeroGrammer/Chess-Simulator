
#ifndef _GRAPHICS_DEFINES_HPP_
#define _GRAPHICS_DEFINES_HPP_

#include "../Chess/chess.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#define BOARD_WIDTH 800
#define BOARD_HEIGHT 800
#define SQUARE_SIZE (BOARD_HEIGHT / 8)

typedef SDL_Rect Dim;
typedef uint32_t Color;

#endif // _GRAPHICS_DEFINES_HPP_
