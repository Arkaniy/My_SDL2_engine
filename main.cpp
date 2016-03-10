#include "app.h"
#include <iostream>

int main() {

	int result = 1;
	try {
		App app;
		result = app.execute();
	} catch(SDL_errorcode) {
		std::cout << SDL_GetError();
	}
	return result;
}
