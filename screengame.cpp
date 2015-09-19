#include "screengame.h"
#include "gfx_engine.h"
#include "resourcesmanager.h"
#include "config.h"
#include <iostream>

ScreenGame::ScreenGame() {}
ScreenGame::~ScreenGame() {}

void ScreenGame::init() {
	_bg = ResourcesManager::getInstance().getPicture("resources/bg_picture2.png");
	_gameUi.setListener(this);
}

void ScreenGame::draw() const {
	GfxEngine::getInstanse().draw(_bg, 0, 0);
	_gameUi.draw();
	_fps.draw();
}

void ScreenGame::tick() {
	_fps.calculateFps();
}

void ScreenGame::handleEvent(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			_nextScreen = SS_Menu;
		}
	} else {
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			_gameUi.handleEvent(event);
		}
	}
}

void ScreenGame::handleWidgetEvent(WidgetEvent event) {
	switch (event) {
	case WE_Menu:
		std::cout << "Menu pressed\n";
		_nextScreen = SS_Menu;
		break;
	default:
		std::cout << "unknown event\n";
		break;
	}
}
