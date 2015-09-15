#include "picture.h"
#include "gfx_engine.h"
#include "helper.h"

Picture::Picture() {
    _texture    = nullptr;
    _w          = 0;
    _h          = 0;
}

void Picture::load(std::string name) {
    free();
    SDL_Renderer *renderer = GfxEngine::getInstanse().getRenderer();
    SDL_Surface *loadedSurface = IMG_Load(name.c_str());
    if (loadedSurface == NULL) {
        Helper::logError("load image");
        return;
    }
    //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0x00, 0xFF));
    _texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (_texture == nullptr) {
        Helper::logError("create texture");
        SDL_FreeSurface(loadedSurface);
        return;
    }
    _w = loadedSurface->w;
    _h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
}

void Picture::loadFromText(TTF_Font *font, std::string text, SDL_Color color) {
    free();
    SDL_Renderer *renderer = GfxEngine::getInstanse().getRenderer();
    SDL_Surface *loadedSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (loadedSurface == NULL) {
        Helper::logError("load from text");
        return;
    }
    _texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (_texture == nullptr) {
        Helper::logError("create texture");
        SDL_FreeSurface(loadedSurface);
        return;
    }
    _w = loadedSurface->w;
    _h = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
}

SDL_Texture *Picture::getTexture() const {
    return _texture;
}

int Picture::getW() const {
    return _w;
}

int Picture::getH() const {
    return _h;
}

void Picture::free() {
    if (_texture != nullptr) {
        SDL_DestroyTexture(_texture);
        _w = 0;
        _h = 0;
    }
}
