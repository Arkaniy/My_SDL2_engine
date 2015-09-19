#ifndef BUTTON_H
#define BUTTON_H

#include "picture.h"
#include <SDL2/SDL.h>
#include "enums.h"
#include "widget.h"

class Button : public Widget {
public:
    Button();
	void draw() const override;
	void handleEvent(SDL_Event& event) override;

	void setWidgetEvent(const WidgetEvent widgetEvent);
	void setPictureActive(const std::string name);
	void setPicturePressed(const std::string name);
	void setX(int x);
	void setY(int y);

	int getW() const;
	int getH() const;
protected:
	int		    _x;
	int			_y;
	WidgetEvent _widgetEvent;
	Picture		*_pictureNormal;
	Picture		*_picturePressed;
	Picture		*_pictureCurrent;
	bool	    _isActive;
};

class TextButton : public Button {
public:
	TextButton();
	~TextButton();
	void draw() const override;
	void setText(std::string str);
private:
	TextPicture _textPicture;
	std::string _text;
};

#endif // BUTTON_H
