#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include "enums.h"
#include "picture.h"
#include "fpscounter.h"
#include "widget.h"

class Screen : public Listener {
public:
    Screen();
	virtual ~Screen();
	virtual void init() = 0;
	virtual void update();
	ScreenState run();
	void drawFrame() const;
protected:
	const Picture *_bg;
    ScreenState _nextScreen;
	FpsCounter& _fps;
};


class ScreenWait : public Screen {
public:
    ScreenWait();
	~ScreenWait();
	void init() override;
	void draw() const override;
	bool handleEvent(SDL_Event &event) override;
	void handleWidgetEvent(WidgetEvent event) override;
};

class TextButton;
class ScreenCredits : public Screen {
public:
	ScreenCredits();
	~ScreenCredits();
	void init() override;
	void draw() const override;
	bool handleEvent(SDL_Event &event) override;
	void handleWidgetEvent(WidgetEvent event) override;
private:
	TextButton *_back;
	TextPicture *_firstLine;
	TextPicture *_secondLine;
};

#endif // SCREEN_H
