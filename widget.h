#ifndef WIDGET_H
#define WIDGET_H

#include <SDL2/SDL.h>
#include "enums.h"

class Listener;
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual void draw() const = 0;
	virtual void handleEvent(SDL_Event& event) = 0;

	void setListener(Listener *listener);
protected:
	Listener *_listener;
};

class Listener : public Widget {
public:
	Listener();
	virtual ~Listener();
	virtual void handleWidgetEvent(WidgetEvent event) = 0;
};

#endif // WIDGET_H
