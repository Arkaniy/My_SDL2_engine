#include "screenmenu.h"
#include "resourcesmanager.h"
#include "config.h"
#include <iostream>

ScreenMenu::ScreenMenu() {}

ScreenMenu::~ScreenMenu() {
	for (size_t i = 0; i < _buttons.size(); ++i) {
		delete _buttons[i];
	}
}

void ScreenMenu::init() {
	_bg = ResourcesManager::getInstance().getPicture(TP_BackgroundMenu);

	_buttons.push_back(new TextButton());
	_buttons.push_back(new TextButton());
	_buttons.push_back(new TextButton());

	for (size_t i = 0; i < _buttons.size(); ++i) {
		_buttons[i]->setListener(this);
		_buttons[i]->setPictureActive(TP_Button);
		_buttons[i]->setPicturePressed(TP_ButtonPressed);
		_buttons[i]->setX(Config::WindowW / 2 - _buttons[i]->getW() / 2);
		_buttons[i]->setY(15 + i * (_buttons[i]->getH() + 5));
	}

	_buttons[0]->setWidgetEvent(BE_NewGame);
	_buttons[0]->setText("New Game");

	_buttons[1]->setWidgetEvent(BE_Credits);
	_buttons[1]->setText("Credits");

	_buttons[2]->setWidgetEvent(BE_Quit);
	_buttons[2]->setText("Quit");
}

void ScreenMenu::draw() const {
	_bg->draw(0, 0);
	for (TextButton *button : _buttons) {
		button->draw();
	}
	_fps.draw();
}

bool ScreenMenu::handleEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            _nextScreen = SS_Quit;
        }
	} else {
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			for (TextButton *button : _buttons) {
				button->handleEvent(event);
			}
        }
    }
}

void ScreenMenu::handleWidgetEvent(WidgetEvent event) {
	switch (event._baseEvent) {
    case BE_NewGame:
		std::cout << "New Game pressed\n";
		_nextScreen = SS_Game;
		break;
	case BE_Credits:
		std::cout << "Credits pressed\n";
		_nextScreen = SS_Credits;
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
