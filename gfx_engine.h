#ifndef GFX_ENGINE_H
#define GFX_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "picture.h"

class GfxEngine {
public:
    static GfxEngine&   getInstanse();
    bool                init();
    void                close();

    void                startFrame();
    void                endFrame();
    void                draw(const Picture &picture, int x, int y, const SDL_Rect * const clip = nullptr);

    SDL_Renderer* getRenderer() const;
private:
    GfxEngine();
private:
    SDL_Window      *_window;
    SDL_Renderer    *_renderer;
    TTF_Font        *_font;
};

#endif // RENDERER_H
