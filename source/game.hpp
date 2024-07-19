#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Graphics/graphics.hpp"
#include "Chess/chess.hpp"

using namespace Graphics;
using namespace Chess;

#include <iostream>

#define RGB(r,g,b)    ((r<<24) | (g<<16) | (b<<8) | 0xFF)
#define RGBA(r,g,b,a) ((r<<24) | (g<<16) | (b<<8) | a)

namespace Colors {

struct Theme {
    Graphics::Color dark_sq;
    Graphics::Color light_sq;
    Graphics::Color highlight_sq;
    Graphics::Color legal_sq;
};

constexpr Theme REGULAR_ONE = { 0x333333FF, 0xCCCCCCFF, 0x6999FFFF, 0x88888888 };
constexpr Theme REGULAR_TWO = { 0x333333AA, 0x666666AA, 0x336666AA, 0x666699AA };

} // namespace Colors

namespace Game {

int run();

} // namespace Game

#endif // _GAME_HPP_
