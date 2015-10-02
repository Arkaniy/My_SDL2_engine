#include "game_ui.h"
#include "config.h"

Game_UI::Game_UI() {
	_buttons.push_back(TextButton());
	_buttons.push_back(TextButton());

	for (TextButton& button : _buttons) {
		button.setListener(this);
		button.setPictureActive(TP_Button);
		button.setPicturePressed(TP_ButtonPressed);
	}

//	_buttons[0].setX(15);
//	_buttons[0].setY(Config::WindowH - _buttons[0].getH() - 15);
	_buttons[0].setX(Config::WindowW / 2 - _buttons[0].getW() / 2);
	_buttons[0].setY(15);
	_buttons[0].setWidgetEvent(BE_Menu);
	_buttons[0].setText("Menu");

	_buttons[1].setX(_buttons[0].getW() + 30);
	_buttons[1].setY(Config::WindowH - _buttons[1].getH() - 15);
	_buttons[1].setWidgetEvent(BE_Quit);
	_buttons[1].setText("Quit");
}

void Game_UI::draw() const {
	for (const TextButton& button : _buttons) {
		button.draw();
	}
}

void Game_UI::handleEvent(SDL_Event &event) {
	for (TextButton& button : _buttons) {
		button.handleEvent(event);
	}
}

void Game_UI::handleWidgetEvent(WidgetEvent event) {
	switch (event._gameEvent) {
	default:
		_listener->handleWidgetEvent(event);
		break;
	}
}
