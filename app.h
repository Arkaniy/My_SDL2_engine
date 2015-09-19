#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "enums.h"
#include "screen.h"

class App {
public:
    App();
    int execute();
private:
    void initVideo();
    void loadResources();
    void close();

	template<typename ScreenType>
	void setScreen();

private:
    ScreenState _nextScreen;
};

template <>
inline void App::setScreen<ScreenWait>() {
	ScreenWait screen;
	screen.init();
	screen.drawFrame();
}

template <typename ScreenType>
inline void App::setScreen() {
	ScreenType screen;
	screen.init();
	_nextScreen = screen.run();
}

#endif // APP_H
