
#ifndef _BOT_HPP_
#define _BOT_HPP_

#include "Chess/chess.hpp"

using namespace Chess;

namespace Bot {
   
Move getBestMove(Board &board, Player player);
 
} // namespace Bot

#endif // _BOT_HPP_
