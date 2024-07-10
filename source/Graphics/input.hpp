
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
        SQUARE_CLICKED,  // left click on the board area
        RESET_SELECTION, // right click on the board area
        MENU_CLICKED,    // left click on the menu area 
        LOGS_CLICKED,    // left click on the logs area
    } type;

    int x, y;
};
    
}

#endif // _INPUT_HPP_
