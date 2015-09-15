#include "app.h"
#include "gfx_engine.h"
#include "resourcesmanager.h"

#include "screenmenu.h"

App::App() {
    _run = true;
}


int App::execute() {
    initVideo();
    loadResources();

    //SDL_Delay(400);
    setScreenWait();
    setScreenWait();
    SDL_Delay(500);

    _nextScreen = SS_Menu;
    while (_nextScreen != SS_Quit) {
        switch(_nextScreen) {
        case SS_Menu:
            setScreenMenu();
            break;
        }
    }

    setScreenWait();
    SDL_Delay(500);

    close();
    return 0;
}

void App::initVideo() {
    GfxEngine::getInstanse().init();
}

void App::loadResources() {
    ResourcesManager::getInstance().loadResources();
}

void App::close() {
    ResourcesManager::getInstance().unload();
    GfxEngine::getInstanse().close();
}

void App::setScreenMenu() {
    ScreenMenu screenMenu;
    _nextScreen = screenMenu.run();
}

void App::setScreenWait() {
    ScreenWait screenWait;
    screenWait.drawFrame();
}
