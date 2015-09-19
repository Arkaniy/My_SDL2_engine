#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "screen.h"
#include "button.h"
#include "game_ui.h"

class ScreenGame : public Screen {
public:
	ScreenGame();
	~ScreenGame();
	void init() override;
	void draw() const override;
	void tick() override;
	void handleEvent(SDL_Event &event) override;
	void handleWidgetEvent(WidgetEvent event) override;
private:
	const Picture *_bg;
	Game_UI _gameUi;
};

#endif // SCREENGAME_H
