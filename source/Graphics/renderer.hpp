
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "defines.hpp"

namespace Graphics {

class Renderer  {

public:

    Renderer(SDL_Window *window, Dim wnd, Dim board, Dim menu);
    ~Renderer();
    int initialize();

    void setFlippedBoard(bool value);
    void present();

    void clear();

    Chess::Square pixelToBoardConverter(int pixel_x, int pixel_y);

    void fillSquare(Chess::Square square, Color color);
    void renderPieceTexture(Chess::Square square, Chess::Piece piece);
    void displayFog(Color color);

private:

    std::string getPieceFilePath(Chess::Piece piece);

private:

    SDL_Renderer *_renderer;
    Dim _wnd;
    Dim _board;
    Dim _menu;

    TTF_Font *_menu_font;

    bool _is_board_flipped;
};

} // namespace Graphics

#endif // _RENDERER_HPP_
