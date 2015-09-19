#ifndef PICTURE_H
#define PICTURE_H

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Picture {
public:
    Picture();
    void            load(std::string name);
	void			setX(int x);
	void			setY(int y);
	void			setW(int w);
	void			setH(int h);

    SDL_Texture*    getTexture() const;
	int             getX() const;
	int             getY() const;
	int             getW() const;
	int             getH() const;
    void            free();
protected:
    SDL_Texture *_texture;
	int			_x;
	int			_y;
    int         _w;
    int         _h;
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
