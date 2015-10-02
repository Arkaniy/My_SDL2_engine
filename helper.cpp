#include "helper.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "assert.h"
#include "config.h"

void Helper::logError(const std::string text) {
	std::cout << "Error " << text << ": " << SDL_GetError() << std::endl;
}

int Helper::random(int min, int max) {
	assert(max >= min);
	return rand() % (max - min + 1) + min;
}
