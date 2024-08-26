
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "defines.hpp"
#include "log.hpp"

namespace Graphics {

class Renderer  {

public:

    Renderer(SDL_Window *window);
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
    SDL_Texture* getPieceTexture(Chess::Piece piece);
    SDL_Texture* loadTexture(const char *file_path);

private:

    SDL_Renderer *_renderer;

    SDL_Rect _screen; // the screen dimentions

    bool _is_board_flipped;

    struct PieceTextures {
        SDL_Texture *wPawn;
        SDL_Texture *wKnight;
        SDL_Texture *wBishop;
        SDL_Texture *wRook;
        SDL_Texture *wQueen;
        SDL_Texture *wKing;
        SDL_Texture *bPawn;
        SDL_Texture *bKnight;
        SDL_Texture *bBishop;
        SDL_Texture *bRook;
        SDL_Texture *bQueen;
        SDL_Texture *bKing;
    };

    PieceTextures _piece_textures;
};

} // namespace Graphics

#endif // _RENDERER_HPP_
