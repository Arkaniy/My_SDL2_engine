#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Picture {
public:
    Picture();
	void			setResource(std::string resource);
	void            load(std::string name);
	void			setXOffset(int x);
	void			setYOffset(int y);
	void			setW(int w);
	void			setH(int h);

	std::string		getResource() const;
    SDL_Texture*    getTexture() const;
	int             getW() const;
	int             getH() const;
    void            free();
	void			draw(int x = 0, int y = 0) const;
protected:
	std::string _resource;
    SDL_Texture *_texture;
	int			_xOffset;
	int			_yOffset;
    int         _w;
	int         _h;
	bool		_exist;
};

class TextPicture : public Picture {
public:
	TextPicture();
	void loadFromText(std::string text, SDL_Color color);
	void setFont(TTF_Font *font);
private:
	TTF_Font *_font;
};

#endif // PICTURE_H
