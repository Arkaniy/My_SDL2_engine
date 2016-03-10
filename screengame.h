#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "screen.h"
#include "game_ui.h"
#include "tilemap.h"
#include "popupwindow.h"

class ScreenGame : public Screen {
public:
	ScreenGame();
	~ScreenGame();
	void init() override;
	void draw() const override;
	void handleEvent(SDL_Event &event) override;
	void handleWidgetEvent(WidgetEvent event) override;
	void update() override;
private:
	TileMap		_tileMap;
	std::vector<PopupWindow> _windows;
	PopupWindow	_window1;
	PopupWindow	_window2;
//	Game_UI				_gameUi;
};

#endif // SCREENGAME_H
