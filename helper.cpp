#include "helper.h"
#include <SDL2/SDL.h>
#include <iostream>

void Helper::logError(const std::string text) {
    std::cout << "Error " << text << ": " << SDL_GetError() << std::endl;
}
