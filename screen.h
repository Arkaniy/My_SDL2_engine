#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include "picture.h"
#include "widget.h"
#include "button.h"

class FpsCounter;
class Screen : public Listener {
public:
    Screen();
	virtual ~Screen();
	virtual void init() = 0;
	virtual void draw() const = 0;
	virtual void update();
	virtual void handleEvent(SDL_Event &event) = 0;
	void handleWidgetEvent(WidgetEvent widgetEvent);
	ScreenState run();
	void drawFrame() const;
protected:
    ScreenState _nextScreen;
	FpsCounter& _fps;
};

class ScreenWait : public Screen {
public:
    ScreenWait();
	~ScreenWait();
	void init() override;
	void draw() const override;
	void handleEvent(SDL_Event &event) override;
private:
	const Picture *_bg;
};

class ScreenCredits : public Screen {
public:
	ScreenCredits();
	~ScreenCredits();
	void init() override;
	void draw() const override;
	void handleEvent(SDL_Event &event) override;
private:
	const Picture *_bg;
	TextButton  _back;
	TextPicture _firstLine;
	TextPicture _secondLine;
};

#endif // SCREEN_H
