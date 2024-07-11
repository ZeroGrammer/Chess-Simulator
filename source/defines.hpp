
#ifndef _GAME_DEFINES_HPP_
#define _GAME_DEFINES_HPP_

#include "Graphics/graphics.hpp"
#include "Chess/chess.hpp"

#include <iostream>

#define RGB(r,g,b) ((r<<24) | (g<<16) | (b<<8) | 0xFF)
#define RGBA(r,g,b,a) ((r<<24) | (g<<16) | (b<<8) | a)

namespace Colors {

struct Theme {
    Color dark_sq;
    Color light_sq;
    Color highlight_sq;
    Color legal_sq;
};

constexpr Theme REGULAR_THEME = { 0x333333FF, 0xCCCCCCFF, 0x6999FFFF, 0x66666666 };
}

#endif // _GAME_DEFINES_HPP_
