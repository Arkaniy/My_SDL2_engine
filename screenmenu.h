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
	void handleEvent(SDL_Event &event) override;
private:
	const Picture *_bg;
	TextButton _newGameButton;
	TextButton _CreditsButton;
	TextButton _QuitButton;
};

#endif // SCREENMENU_H
