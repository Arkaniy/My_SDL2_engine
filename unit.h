#ifndef UNIT_H
#define UNIT_H

#include "landoverlay.h"

class Unit : public LandOverlay {
public:
	Unit();
	void draw() const;
	virtual void handleEvent(SDL_Event& event);
	void initRandomCoordinates();
	void setTileMap(TileMap *tileMap);
	void move(int di, int dj);
private:
	TileMap *_tileMap;
};

#endif // UNIT_H
