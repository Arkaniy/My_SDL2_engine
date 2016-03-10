#include "screenmenu.h"
#include "resourcesmanager.h"
#include "config.h"
#include <iostream>

ScreenMenu::ScreenMenu() {}
ScreenMenu::~ScreenMenu() {}

void ScreenMenu::init() {
	_bg = ResourcesManager::getInstance().getPicture(TP_BackgroundMenu);

	_newGameButton.setListener(this);
	_newGameButton.setPictureActive(TP_Button);
	_newGameButton.setPicturePressed(TP_ButtonPressed);
	_newGameButton.setX(Config::WindowW / 2 - _newGameButton.getW() / 2);
	_newGameButton.setY(15 + 0 * (_newGameButton.getH() + 5));
	_newGameButton.setWidgetEvent(BE_NewGame);
	_newGameButton.setText("New Game");

	_CreditsButton.setListener(this);
	_CreditsButton.setPictureActive(TP_Button);
	_CreditsButton.setPicturePressed(TP_ButtonPressed);
	_CreditsButton.setX(Config::WindowW / 2 - _newGameButton.getW() / 2);
	_CreditsButton.setY(15 + 1 * (_CreditsButton.getH() + 5));
	_CreditsButton.setWidgetEvent(BE_Credits);
	_CreditsButton.setText("Credits");

	_QuitButton.setListener(this);
	_QuitButton.setPictureActive(TP_Button);
	_QuitButton.setPicturePressed(TP_ButtonPressed);
	_QuitButton.setX(Config::WindowW / 2 - _newGameButton.getW() / 2);
	_QuitButton.setY(15 + 2 * (_QuitButton.getH() + 5));
	_QuitButton.setWidgetEvent(BE_Quit);
	_QuitButton.setText("Quit");
}

void ScreenMenu::draw() const {
	_bg->draw();
	_newGameButton.draw();
	_CreditsButton.draw();
	_QuitButton.draw();
}

void ScreenMenu::handleEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            _nextScreen = SS_Quit;
        }
	} else {
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			_newGameButton.handleEvent(event);
			_CreditsButton.handleEvent(event);
			_QuitButton.handleEvent(event);
        }
	}
}
