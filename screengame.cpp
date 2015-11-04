#include "screengame.h"
#include "resourcesmanager.h"
#include "config.h"
#include <iostream>

ScreenGame::ScreenGame() {}
ScreenGame::~ScreenGame() {}

void ScreenGame::init() {
	//_bg = ResourcesManager::getInstance().getPicture();
	_gameUi.setListener(this);
	_tileMap.setListener(this);
}

void ScreenGame::draw() const {
	//_bg->draw(0, 0);
	_tileMap.draw();
	_gameUi.draw();
	_fps.draw();
}

bool ScreenGame::handleEvent(SDL_Event &event) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			_nextScreen = SS_Menu;
		} else {
			_gameUi.handleEvent(event);
			_tileMap.handleEvent(event);
		}
}

void ScreenGame::handleWidgetEvent(WidgetEvent event) {
	switch (event._baseEvent) {
	case BE_Menu:
		std::cout << "Menu pressed\n";
		_nextScreen = SS_Menu;
		break;
	case BE_Quit:
		std::cout << "Quit pressed\n";
		_nextScreen = SS_Quit;
		break;
	default:
		std::cout << "unknown event\n";
		break;
	}
}

void ScreenGame::update() {
	_tileMap.update();
}
