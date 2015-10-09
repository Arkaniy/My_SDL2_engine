#include "picture.h"
#include "gfx_engine.h"
#include "helper.h"

Picture::Picture() {
	_resource	= "";
    _texture    = nullptr;
	_xOffset	= 0;
	_yOffset	= 0;
    _w          = 0;
	_h          = 0;
	_exist		= true;
}

void Picture::setResource(std::string resource) {
	_resource = resource;
}

void Picture::load(std::string name) {
    free();
    SDL_Renderer *renderer = GfxEngine::getInstanse().getRenderer();
    SDL_Surface *loadedSurface = IMG_Load(name.c_str());
    if (loadedSurface == NULL) {
        Helper::logError("load image");
        return;
    }
    //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0x00, 0xFF));
    _texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (_texture == nullptr) {
        Helper::logError("create texture");
        SDL_FreeSurface(loadedSurface);
        return;
    }
    _w = loadedSurface->w;
    _h = loadedSurface->h;
	_resource = name;
	SDL_FreeSurface(loadedSurface);
}

void Picture::setXOffset(int x) {
	_xOffset = x;
	if (x != 0) {
		_w = 64;
		_h = 64;
	}
}

void Picture::setYOffset(int y) {
	_yOffset = y;
	if (y != 0) {
		_w = 64;
		_h = 64;
	}
}

void Picture::setW(int w) {
	_w = w;
}

void Picture::setH(int h) {
	_h = h;
}

void Picture::setExist(bool exist) {
	_exist = exist;
}

std::string Picture::getResource() const {
	return _resource;
}

SDL_Texture *Picture::getTexture() const {
	return _texture;
}

int Picture::getW() const {
    return _w;
}

int Picture::getH() const {
    return _h;
}

void Picture::free() {
	if (_texture != nullptr && _exist == true) {
        SDL_DestroyTexture(_texture);
		_xOffset = 0;
		_yOffset = 0;
        _w = 0;
		_h = 0;
		_exist = false;
	}
}

void Picture::draw(int x, int y) const {
	SDL_Rect clip = { _xOffset, _yOffset, _w, _h };
	GfxEngine::getInstanse().draw(this, x, y, &clip);
}

TextPicture::TextPicture() {
	_font = nullptr;
}

void TextPicture::loadFromText(std::string text, SDL_Color color) {
	free();
	SDL_Renderer *renderer = GfxEngine::getInstanse().getRenderer();
	SDL_Surface *loadedSurface = TTF_RenderText_Solid(_font, text.c_str(), color);
	if (loadedSurface == NULL) {
		Helper::logError("load from text");
		return;
	}
	_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (_texture == nullptr) {
		Helper::logError("create texture");
		SDL_FreeSurface(loadedSurface);
		return;
	}
	_w = loadedSurface->w;
	_h = loadedSurface->h;
	_exist = true;
	SDL_FreeSurface(loadedSurface);
}

void TextPicture::setFont(TTF_Font *font) {
	_font = font;
}
