#include "app.h"
#include "gfx_engine.h"
#include "resourcesmanager.h"

#include "screenmenu.h"
#include "screengame.h"

App::App() {}

int App::execute() {
    initVideo();
    loadResources();

    _nextScreen = SS_Menu;
    while (_nextScreen != SS_Quit) {
        switch(_nextScreen) {
	case SS_Game:
		setScreen<ScreenGame>();
		break;
        case SS_Menu:
		setScreen<ScreenMenu>();
        	break;
	case SS_Credits:
		setScreen<ScreenCredits>();
		break;
	}
    }

	setScreen<ScreenWait>();
	SDL_Delay(100);

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
