#include "screen.h"
#include "resourcesmanager.h"
#include "gfx_engine.h"
#include "button.h"
#include "config.h"
#include <iostream>

Screen::Screen() : _fps(FpsCounter::getInstance()) {
	_bg = nullptr;
    _nextScreen = SS_TOTAL;
}

Screen::~Screen() {}

ScreenState Screen::run() {
    SDL_Event event;
	while (_nextScreen == SS_TOTAL) {
		tick();
        drawFrame();		
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                _nextScreen = SS_Quit;
			} else {
                handleEvent(event);
            }
        }
    }
    return _nextScreen;
}

void Screen::drawFrame() const {
    GfxEngine engine = GfxEngine::getInstanse();
    engine.startFrame();
	draw();
    engine.endFrame();
}

ScreenWait::ScreenWait() {}
ScreenWait::~ScreenWait() {}

void ScreenWait::init() {
	_bg = ResourcesManager::getInstance().getPicture(TP_BackgroundWait);
}

void ScreenWait::draw() const {
	_bg->draw(0, 0);
}
void ScreenWait::tick() {}
void ScreenWait::handleEvent(SDL_Event&) {}
void ScreenWait::handleWidgetEvent(WidgetEvent) {}


ScreenCredits::ScreenCredits() {}

ScreenCredits::~ScreenCredits() {
	delete _back;
	delete _firstLine;
	delete _secondLine;
}

void ScreenCredits::init() {
	_bg = ResourcesManager::getInstance().getPicture(TP_BackgroundMenu);

	_back = new TextButton();
	_back->setListener(this);
	_back->setPictureActive(TP_Button);
	_back->setPicturePressed(TP_ButtonPressed);
	_back->setX(15);
	_back->setY(Config::WindowH - _back->getH() - 5);
	_back->setWidgetEvent(BE_Menu);
	_back->setText("Back");

	_firstLine = new TextPicture();
	_firstLine->setFont(ResourcesManager::getInstance().getFont("resources/font.ttf"));
	_firstLine->loadFromText("First long long long line", {255, 0, 0, 255});

	_secondLine = new TextPicture();
	_secondLine->setFont(ResourcesManager::getInstance().getFont("resources/font.ttf"));
	_secondLine->loadFromText("Another line", {255, 0, 0, 255});
}

void ScreenCredits::draw() const {
	_bg->draw(0, 0);
	_firstLine->draw(Config::WindowW / 2 - _firstLine->getW() / 2, Config::WindowH / 2);
	_secondLine->draw(Config::WindowW / 2 - _secondLine->getW() / 2, Config::WindowH / 2 + _secondLine->getH());
	_back->draw();
	_fps.draw();
}

void ScreenCredits::tick() {
	_fps.calculateFps();
}

void ScreenCredits::handleEvent(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			_nextScreen = SS_Menu;
		}
	} else {
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			_back->handleEvent(event);
		}
	}
}

void ScreenCredits::handleWidgetEvent(WidgetEvent event) {
	if (event._baseEvent == BE_Menu) {
		_nextScreen = SS_Menu;
	} else {
		std::cout << "unknown event";
	}
}
