#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Picture {
public:
    Picture();
    void            load(std::string name);
    void            loadFromText(TTF_Font *font, std::string text, SDL_Color color);
    SDL_Texture*    getTexture() const;
    int             getW() const;
    int             getH() const;
    void            free();
private:
    SDL_Texture *_texture;
    int         _w;
    int         _h;
};

#endif // PICTURE_H
