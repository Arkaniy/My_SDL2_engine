#include "game_ui.h"
#include "config.h"

Game_UI::Game_UI() {
	_buttons.push_back(new TextButton());

	_buttons[0]->setListener(this);
	_buttons[0]->setPictureActive("resources/button.png");
	_buttons[0]->setPicturePressed("resources/button_pressed.png");
	_buttons[0]->setX(Config::WindowW / 2 - _buttons[0]->getW() / 2);
	_buttons[0]->setY(15);
	_buttons[0]->setWidgetEvent(WE_Menu);
	_buttons[0]->setText("SomeMenuBtton");

}

void Game_UI::draw() const {
	_buttons[0]->draw();
}

void Game_UI::handleEvent(SDL_Event &event) {
	_buttons[0]->handleEvent(event);
}

void Game_UI::handleWidgetEvent(WidgetEvent event) {
	switch (event) {
	case WE_Menu:
		_listener->handleWidgetEvent(event);
		break;
	}
}