
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "defines.hpp"
#include "log.hpp"

#define FontType uint8_t
#define REGULAR  0x00
#define BOLD     0x01
#define SMALL    0x02

namespace Graphics {

class Renderer  {

public:

    Renderer(SDL_Window *window);
    ~Renderer();

    int initialize();

    void present();

    void clear(Color color);

    void setIsFlipped(bool value);

    Chess::Square pixelToBoardConverter(int pixel_x, int pixel_y);

    void fillSquare(Chess::Square square, Color color);
    void renderPieceTexture(Chess::Square square, Chess::Piece piece);

    void drawText(FontType font_type, const char *text, Rect position, Color text_color);

    void displayFog(Color color);

private:

    std::string getPieceFilePath(Chess::Piece piece);
    SDL_Texture* getPieceTexture(Chess::Piece piece);
    SDL_Texture* loadTexture(const char *file_path);

private:

    SDL_Renderer *_renderer;

    bool _is_flipped;

    SDL_Rect _screen; // the screen dimentions

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

    struct MenuFont {
        TTF_Font *bold;
        TTF_Font *regular;
        TTF_Font *small;
    };
    MenuFont _menu_font;
};

} // namespace Graphics

#endif // _RENDERER_HPP_
