#ifndef UNIT_H
#define UNIT_H

#include "landoverlay.h"

class Unit : public LandOverlay {
public:
	Unit();
	void draw() const;
	void tick(bool *keyState);
	virtual bool handleEvent(SDL_Event& event);
	void initRandomCoordinates();
	void setTileMap(TileMap *tileMap);
	void move(int di, int dj);
	void searchWay(int iFinish, int jFinish);
	int getSpeed() const;
	bool isMoving() const;
private:
	TileMap *_tileMap;
	unsigned int _speed;
	Uint32	_lastMove;

public:
	int _oldI;
	int _oldJ;
};

#endif // UNIT_H
