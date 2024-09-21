#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Graphics/graphics.hpp"
#include "Chess/chess.hpp"

#include "move_stack.hpp"
#include "bot.hpp"

#include <string>

#define RGB(r,g,b)    ((r<<24) | (g<<16) | (b<<8) | 0xFF)
#define RGBA(r,g,b,a) ((r<<24) | (g<<16) | (b<<8) | a)

namespace Colors {

struct Theme {
    Graphics::Color dark_sq;
    Graphics::Color light_sq;
    Graphics::Color highlight_sq;
    Graphics::Color legal_sq;
};

constexpr Graphics::Color WHITE_FOG = 0xFFFFFF88;
constexpr Graphics::Color BLACK_FOG = 0x00000088;

constexpr Theme REGULAR_ONE = { 0x333333FF, 0xCCCCCCFF, 0x6999FFFF, 0x69BBFF99 };
constexpr Theme REGULAR_TWO = { 0x996666FF, 0xFFCCCCFF, 0xFFAAEEFF, 0xFFCCFF99 };
constexpr Theme LIGHT_THEME = { 0xAAAAAAFF, 0xFFFFFFFF, 0x0000FF99, 0x00FF0099 };

} // namespace Colors

namespace Game {

int run();

} // namespace Game

#endif // _GAME_HPP_
