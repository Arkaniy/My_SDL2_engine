#include "screengame.h"
#include "resourcesmanager.h"
#include "config.h"
#include <iostream>

ScreenGame::ScreenGame() {}
ScreenGame::~ScreenGame() {}

void ScreenGame::init() {
	//_gameUi.setListener(this);
	_tileMap.setListener(this);

	_windows.push_back(PopupWindow());
	_windows.back().setCoordinates(50,50);
}

void ScreenGame::draw() const {
	_tileMap.draw();
	//_gameUi.draw();
	for(const PopupWindow& window : _windows) {
		window.draw();
	}
}

void ScreenGame::handleEvent(SDL_Event &event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		for(PopupWindow& window : _windows) {
			window.handleEvent(event);
		}
	} else {
		_windows.back().handleEvent(event);
	}
	_tileMap.handleEvent(event);
}

void ScreenGame::handleWidgetEvent(WidgetEvent event) {
	Screen::handleWidgetEvent(event);
}

void ScreenGame::update() {
	_tileMap.update();
}
