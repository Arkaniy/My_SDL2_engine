#include "screenmenu.h"
#include "gfx_engine.h"
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
    _bg = ResourcesManager::getInstance().getPicture("resources/bg_picture.png");

	_buttons.push_back(new TextButton());
	_buttons.push_back(new TextButton());
	_buttons.push_back(new TextButton());

	for (size_t i = 0; i < _buttons.size(); ++i) {
		_buttons[i]->setListener(this);
		_buttons[i]->setPictureActive("resources/button.png");
		_buttons[i]->setPicturePressed("resources/button_pressed.png");
		_buttons[i]->setX(Config::WindowW / 2 - _buttons[i]->getW() / 2);
		_buttons[i]->setY(15 + i * (_buttons[i]->getH() + 5));
	}

	_buttons[0]->setWidgetEvent(WE_NewGame);
	_buttons[0]->setText("New Game");

	_buttons[1]->setWidgetEvent(WE_Credits);
	_buttons[1]->setText("Credits");

	_buttons[2]->setWidgetEvent(WE_Quit);
	_buttons[2]->setText("Quit");
}

void ScreenMenu::draw() const {
    GfxEngine::getInstanse().draw(_bg, 0, 0);
	for (TextButton *button : _buttons) {
		button->draw();
	}
	_fps.draw();
}

void ScreenMenu::tick() {
	_fps.calculateFps();
}

void ScreenMenu::handleEvent(SDL_Event &event) {
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
    switch (event) {
    case WE_NewGame:
		std::cout << "New Game pressed\n";
		_nextScreen = SS_Game;
		break;
	case WE_Credits:
		std::cout << "Credits pressed\n";
		_nextScreen = SS_Credits;
		break;
	case WE_Quit:
		std::cout << "Quit pressed\n";
		_nextScreen = SS_Quit;
		break;
	default:
		std::cout << "unknown event\n";
		break;
    }
}
