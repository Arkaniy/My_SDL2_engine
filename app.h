#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

class App {
public:
    App();
    int execute();
private:
    bool _run;
};

#endif // APP_H
