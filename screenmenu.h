#ifndef SCREENMENU_H
#define SCREENMENU_H

#include "screen.h"
#include "button.h"
#include <vector>

class ScreenMenu : public Screen {
public:
    ScreenMenu();
	~ScreenMenu();
    void init() override;
    void draw() const override;
    bool handleEvent(SDL_Event &event) override;
    void handleWidgetEvent(WidgetEvent event) override;
private:
	std::vector<TextButton*> _buttons;
};

#endif // SCREENMENU_H
