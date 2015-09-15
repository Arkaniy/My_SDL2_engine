#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "enums.h"

class App {
public:
    App();
    int execute();
private:
    void initVideo();
    void loadResources();
    void close();

    void setScreenMenu();
    void setScreenWait();
private:
    bool _run;
    ScreenState _nextScreen;
};

#endif // APP_H
