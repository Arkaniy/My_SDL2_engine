#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "screen.h"
#include "game_ui.h"
#include "tilemap.h"
#include "unit.h"

class ScreenGame : public Screen {
public:
	ScreenGame();
	~ScreenGame();
	void init() override;
	void draw() const override;
	bool handleEvent(SDL_Event &event) override;
	void handleWidgetEvent(WidgetEvent event) override;
	void update() override;
private:
	TileMap				_tileMap;
	Game_UI				_gameUi;
	std::vector<Unit*>	_units;
};

#endif // SCREENGAME_H
