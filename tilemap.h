#ifndef TILEMAP_H
#define TILEMAP_H

#include "picture.h"
#include <vector>
#include "enums.h"

class Unit;
class LandOverlay;
class Tile {
public:
	Tile();
	~Tile();
	void		setTileType(TileType tileType);
	void		setLandOverlay(LandOverlay *landOverlay);
	void		setPicture(const TilePicture tilePicture);
	void		setI(int i);
	void		setJ(int j);
	void		setX(int x);
	void		setY(int y);
	TileType	getTileType() const;
	int			getI() const;
	int			getJ() const;
	int			getX() const;
	int			getY() const;
	void		draw(int di, int dj) const;
private:
	TileType	_tileType;
	LandOverlay	*_landOverlay;
	Picture		*_picture;
	int			_i;
	int			_j;
	int			_x;
	int			_y;
};

class TileMap {
	friend class MapGenerator;
public:
	TileMap();
	void draw() const;
	void tick();
	Tile *getTile(int i, int j);
	Tile *getRandomTile();
	bool isInRange(int i, int j) const;
	void setCenterUnit(Unit *centerUnit);
private:
	int								_Size;
	std::vector<std::vector<Tile>>	_tiles;
	Unit							*_centerUnit;
};

#endif // TILEMAP_H
