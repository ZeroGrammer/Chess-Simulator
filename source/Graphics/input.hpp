
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

namespace Graphics {

struct Keyboard {

    enum Type {
        NONE = 0,
        FLIP_BOARD,  // f key
        RESET_BOARD, // x key
    } type;
};

struct Mouse {

    enum Type {
        NONE = 0,
        RBOARD,   // right click on the board area
        RMENU,    // right click on the menu area 
        LBOARD,   // left click on the board area
        LMENU,    // left click on the menu area 
    } type;

    int x, y;
};
    
} // namepace Graphics

#endif // _INPUT_HPP_
