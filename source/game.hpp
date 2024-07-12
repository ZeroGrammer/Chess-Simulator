#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Graphics/graphics.hpp"
#include "Chess/chess.hpp"

#include <iostream>

#define RGB(r,g,b) ((r<<24) | (g<<16) | (b<<8) | 0xFF)
#define RGBA(r,g,b,a) ((r<<24) | (g<<16) | (b<<8) | a)

namespace Colors {

struct Theme {
    Graphics::Color dark_sq;
    Graphics::Color light_sq;
    Graphics::Color highlight_sq;
    Graphics::Color legal_sq;
};

constexpr Theme REGULAR_THEME = { 0x333333FF, 0xCCCCCCFF, 0x6999FFFF, 0x66666666 };
}

namespace Game {

int run();

}

#endif // _GAME_HPP_
