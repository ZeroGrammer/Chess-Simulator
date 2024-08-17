
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include "../Chess/chess.hpp"

#include <string.h>

using namespace Chess;

namespace Engine {

Move getBestMove(const Board &board, Player player);

} // namespace Engine

#endif // _ENGINE_HPP_
