#include "button.h"
#include "resourcesmanager.h"
#include "gfx_engine.h"
#include <iostream>
#include "screen.h"

Button::Button() {
	_widgetEvent = WE_TOTAL;
	_listener = nullptr;
    _x = 0;
    _y = 0;
	_pictureNormal = nullptr;
	_picturePressed = nullptr;
	_pictureCurrent = nullptr;
    _isActive = true;
}

void Button::draw() const {
	GfxEngine::getInstanse().draw(_pictureCurrent, _x, _y);
}

void Button::handleEvent(SDL_Event &event) {
	if (event.button.x >= _x && event.button.x <= _x + _pictureNormal->getW() &&
			event.button.y >= _y && event.button.y <= _y + _pictureNormal->getH()) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			_pictureCurrent = _picturePressed;
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			_pictureCurrent = _pictureNormal;
			_listener->handleWidgetEvent(_widgetEvent);
		}
	} else {
		_pictureCurrent = _pictureNormal;
	}
}

void Button::setWidgetEvent(const WidgetEvent widgetEvent) {
	_widgetEvent = widgetEvent;
}

void Button::setPictureActive(const std::string name) {
	_pictureNormal = ResourcesManager::getInstance().getPicture(name);
	_pictureCurrent = _pictureNormal;
}

void Button::setPicturePressed(const std::string name) {
	_picturePressed = ResourcesManager::getInstance().getPicture(name);
}

void Button::setX(int x) {
	_x = x;
}

void Button::setY(int y) {
	_y = y;
}

int Button::getW() const {
	return _pictureNormal->getW();
}

int Button::getH() const {
	return _pictureNormal->getH();
}

TextButton::TextButton() {
	_textPicture.setFont(ResourcesManager::getInstance().getFont("resources/font.ttf"));
	_text = "";
}

void TextButton::draw() const {
	Button::draw();
	if (_text != "") {
		GfxEngine::getInstanse().draw(&_textPicture, _x + getW() / 2 - _textPicture.getW() / 2,
									  _y + getH() / 2 - _textPicture.getH() / 2);
	}
}

void TextButton::setText(std::string str) {
	_text = str;
	_textPicture.loadFromText(_text, {0, 0, 0, 0});
}
