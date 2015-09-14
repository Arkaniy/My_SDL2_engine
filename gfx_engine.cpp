#include "gfx_engine.h"
#include "helper.h"
#include <SDL2/SDL_image.h>


GfxEngine::GfxEngine() {
    _renderer   = nullptr;
    _window     = nullptr;
    _font       = nullptr;
}

GfxEngine& GfxEngine::getInstanse() {
    static GfxEngine instance;
    return instance;
}

bool GfxEngine::init() {
    bool result = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Helper::logError("init video");
        result = false;
    }
    _window = SDL_CreateWindow("My window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        Helper::logError("create window");
        result = false;
    }
    _renderer = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr) {
        Helper::logError("create render");
        result = false;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Helper::logError("init img");
        result = false;
    }
    if (TTF_Init() < 0) {
        Helper::logError("init font");
        result = false;
    }
    return result;
}

void GfxEngine::close() {
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void GfxEngine::startFrame() {
    SDL_RenderClear(_renderer);
}

void GfxEngine::draw(const Picture &picture, int x, int y, const SDL_Rect * const clip) {
    SDL_Rect rect = { x, y, picture.getW(), picture.getH() };
    if (clip != nullptr) {
        rect.w = clip->w;
        rect.h = clip->h;
    }
    SDL_RenderCopy(_renderer, picture.getTexture(), clip, &rect);
}

void GfxEngine::endFrame() {
    SDL_RenderPresent(_renderer);
}

SDL_Renderer* GfxEngine::getRenderer() const {
    return _renderer;
}
