#include "app.h"
#include "gfx_engine.h"
#include "resourcesmanager.h"
#include <sstream>

App::App() {
    _run = true;
}


int App::execute() {
    GfxEngine& engine = GfxEngine::getInstanse();
    engine.init();
    ResourcesManager::getInstance().loadResources();
    SDL_Event event;

    while (_run) {
        engine.startFrame();

        engine.endFrame();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                _run = false;
            }
        }
    }
    engine.close();
    return 0;
}
