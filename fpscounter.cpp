#include "fpscounter.h"
#include "resourcesmanager.h"
#include <SDL2/SDL.h>
#include <sstream>

FpsCounter::FpsCounter() {
    _currentFps     = 0;
    _currentFrame   = 0;
	_text.setFont(ResourcesManager::getInstance().getFont("resources/font1.ttf"));
	_text.setXOffset(5);
	_text.setYOffset(5);
}

FpsCounter& FpsCounter::getInstance() {
	static FpsCounter instance;
	return instance;
}

void FpsCounter::draw() const {
	_text.draw(5, 5);
}

void FpsCounter::calculateFps() {
    static Uint32 start = SDL_GetTicks();
    _currentFrame++;
    Uint32 end = SDL_GetTicks();
    if (end - start >= 1000) {
        _currentFps = _currentFrame;
        _currentFrame = 0;
        start = end;
    }

	std::stringstream ss("");
	ss << "FPS: " << _currentFps;
	_text.loadFromText(ss.str(), {0xFF, 0xFF, 0xFF, 0xFF});
}
