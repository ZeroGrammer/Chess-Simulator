
#ifndef _GRAPHICS_DEFINES_HPP_
#define _GRAPHICS_DEFINES_HPP_

#include "../Chess/chess.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <cstdint>

// in pixels
constexpr int SQUARE_SIZE = 100;
constexpr int WND_WIDTH = SQUARE_SIZE * BOARD_SIZE;
constexpr int WND_HEIGHT = SQUARE_SIZE * BOARD_SIZE;

namespace Graphics {

typedef uint32_t Color;
typedef SDL_Rect Rect;

} // namespace Graphics

#define RGB(r,g,b)    ((r<<24) | (g<<16) | (b<<8) | 0xFF)
#define RGBA(r,g,b,a) ((r<<24) | (g<<16) | (b<<8) | a)

#endif // _GRAPHICS_DEFINES_HPP_
