#ifndef TILEMAP_H
#define TILEMAP_H

#include "picture.h"
#include <vector>
#include "enums.h"
#include "widget.h"
#include "scroller.h"

class Unit;
class LandOverlay;
class Tile {
	friend class TileMap;
public:
	Tile();
	~Tile();
	void		setTileType(TileType tileType);
	void		setLandOverlay(LandOverlay *landOverlay);
	void		setPicture(const TilePicture tilePicture);
	TileType	getTileType() const;
	LandOverlay*getLandOverlay();
	int			getI() const;
	int			getJ() const;
	int			getX() const;
	int			getY() const;
	void		draw() const;
private:
	TileType	_tileType;
	LandOverlay	*_landOverlay;
	Picture		*_picture;
	int			_i;
	int			_j;
	int			_x;
	int			_y;
};

class TileMap : public Widget {
	friend class MapGenerator;
public:
	TileMap();
	void draw() const override;
	void handleEvent(SDL_Event &event) override;
	void update(); // make center on _centerUnit after every frame
	Tile *getTile(int i, int j);
	Tile *getRandomTile();
	bool isInRange(int i, int j) const;
	void setCenterUnit(Unit *centerUnit);
private:
	int								_Size;
	std::vector<std::vector<Tile>>	_tiles;
	Unit							*_centerUnit;
	Scroller						_scroller;
	int								_offsetX;
	int								_offsetY;
	int								_centerX;
	int								_centerY;

	bool _cen = false;
};

#endif // TILEMAP_H
