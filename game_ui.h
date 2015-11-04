#ifndef GAME_UI_H
#define GAME_UI_H

#include "widget.h"
#include "button.h"
#include <vector>

class Game_UI : public Listener {
public:
	Game_UI();
	void draw() const override;
	bool handleEvent(SDL_Event& event) override;
	void handleWidgetEvent(WidgetEvent event) override;
private:
	std::vector<TextButton> _textButtons;
};

#endif // GAME_UI_H
