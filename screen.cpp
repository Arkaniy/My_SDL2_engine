#include "screen.h"
#include "fpscounter.h"
#include "resourcesmanager.h"
#include "gfx_engine.h"
#include "config.h"
#include <iostream>

Screen::Screen() : _fps(FpsCounter::getInstance()) {
    _nextScreen = SS_TOTAL;
}

Screen::~Screen() {}

void Screen::update() {}

void Screen::handleWidgetEvent(WidgetEvent widgetEvent) {
	switch (widgetEvent._baseEvent) {
	case BE_NewGame:
		std::cout << "New Game pressed\n";
		_nextScreen = SS_Game;
		break;
	case BE_Credits:
		std::cout << "Credits pressed\n";
		_nextScreen = SS_Credits;
		break;
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
	}
}

ScreenState Screen::run() {
    SDL_Event event;

	while (_nextScreen == SS_TOTAL) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				_nextScreen = SS_Quit;
			} else {
				handleEvent(event);
			}
		}
		update();
		drawFrame();
    }

    return _nextScreen;
}

void Screen::drawFrame() const {
    GfxEngine engine = GfxEngine::getInstanse();
    engine.startFrame();
	draw();
	_fps.draw();
    engine.endFrame();
	_fps.calculateFps();
}

// Screen wait
ScreenWait::ScreenWait() {}
ScreenWait::~ScreenWait() {}

void ScreenWait::init() {
	_bg = ResourcesManager::getInstance().getPicture(TP_BackgroundWait);
}

void ScreenWait::draw() const {
	_bg->draw();
}

void ScreenWait::handleEvent(SDL_Event&) {}

// Screen credits
ScreenCredits::ScreenCredits() {}
ScreenCredits::~ScreenCredits() {}

void ScreenCredits::init() {
	_bg = ResourcesManager::getInstance().getPicture(TP_BackgroundMenu);

	_back.setListener(this);
	_back.setPictureActive(TP_Button);
	_back.setPicturePressed(TP_ButtonPressed);
	_back.setX(15);
	_back.setY(Config::WindowH - _back.getH() - 15);
	_back.setWidgetEvent(BE_Menu);
	_back.setText("Back");

	_firstLine.setFont(ResourcesManager::getInstance().getFont(FC_Main));
	_firstLine.loadFromText("First long long long line", {255, 0, 0, 255});

	_secondLine.setFont(ResourcesManager::getInstance().getFont(FC_Main));
	_secondLine.loadFromText("Another line", {255, 0, 0, 255});
}

void ScreenCredits::draw() const {
	_bg->draw();
	_firstLine.draw(Config::WindowW / 2 - _firstLine.getW() / 2, Config::WindowH / 2);
	_secondLine.draw(Config::WindowW / 2 - _secondLine.getW() / 2, Config::WindowH / 2 + _secondLine.getH());
	_back.draw();
}

void ScreenCredits::handleEvent(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			_nextScreen = SS_Menu;
		}
	} else {
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			_back.handleEvent(event);
		}
	}
}
