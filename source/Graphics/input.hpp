
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

namespace Graphics {

struct Keyboard {

    enum Type {
        // On Board Keybinds
        NONE = 0,
        FLIP_BOARD,    // f key
        RESET_BOARD,   // x key
        PROMOTE_TO,    // any key in { 1, 2, 3, 4 }
        PREVIOUS_MOVE, // Left arrow key
        NEXT_MOVE,     // Right Arrow Key 
        LATEST_MOVE,   // r key

        TOGGLE_MENU,   // ESC key

        // On Menu Keybinds
        NEXT_ITEM,     // Arrow Down key
        PREVIOUS_ITEM, // Arrow Up key

        ACTION         // Return (Enter) Key
    } type;

    // NOTE(Tejas): if any key from 1 to 4 is held, the pawn 
    //              will be promoted to the corresponding piece.
    //              This is only relevent if the Type is PROMOTE_TO
    enum PieceType {
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT
    } piece_type;
};

struct Mouse {

    enum Type {
        NONE = 0,
        LCLICK,
        RCLICK
    } type;

    int x, y;
};
    
} // namepace Graphics

#endif // _INPUT_HPP_
