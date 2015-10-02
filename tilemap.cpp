#include "tilemap.h"
#include "resourcesmanager.h"
#include "config.h"
#include <ctime>
#include "landoverlay.h"
#include "unit.h"
#include "mapgenerator.h"
#include "helper.h"

Tile::Tile() {
	_landOverlay = nullptr;
	_picture = nullptr;
	_i = 0;
	_j = 0;
	_x = 0;
	_y = 0;
}

Tile::~Tile() {
	if (_landOverlay != nullptr) {
		delete _landOverlay;
	}
}

void Tile::setTileType(TileType tileType) {
	_tileType = tileType;
	switch(tileType) {
	case TT_Passable:
		setPicture(TP_Tile);
		break;
	case TT_Wall:
		setPicture(TP_Wall);
		break;
	}
}

void Tile::setLandOverlay(LandOverlay *landOverlay) {
	_landOverlay = landOverlay;
}

void Tile::setPicture(const TilePicture tilePicture) {
	_picture = ResourcesManager::getInstance().getPicture(tilePicture);
}

void Tile::setI(int i) {
	_i = i;
}

void Tile::setJ(int j) {
	_j = j;
}

void Tile::setX(int x) {
	_x = x;
}

void Tile::setY(int y) {
	_y = y;
}

TileType Tile::getTileType() const {
	return _tileType;
}

int Tile::getI() const {
	return _i;
}

int Tile::getJ() const {
	return _j;
}

int Tile::getX() const {
	return _x;
}

int Tile::getY() const {
	return _y;
}


void Tile::draw(int di, int dj) const {
	if (_picture != nullptr) {
		int dx = (dj - di) * 32;
		int dy = (dj + di) * 16;
		_picture->draw(_x + dx, _y + dy);
		if (_landOverlay != nullptr) {
			_landOverlay->draw();
		}
	}
}

TileMap::TileMap() {
	srand(time(0));
	_Size = Config::SizeTileMap;
	_tiles.resize(_Size);
	int i = 0;
	int centerX = Config::WindowW / 2 - 32;
	int centerY = Config::WindowH / 2 - 32;
	for (auto& subVector : _tiles) {
		int j = 0;
		subVector.resize(_Size);
		for (Tile& tile : subVector) {
			tile.setTileType(TT_TOTAL);
			tile.setI(i);
			tile.setJ(j);
			tile.setX((j - i) * 32 + centerX);
			tile.setY((i + j) * 16 + centerY);
			++j;
		}
		++i;
	}
	MapGenerator::getInstance().generate(this);
}

void TileMap::draw() const {
//	int I = _centerUnit->getI();
//	int J = _centerUnit->getJ();
//	for (int i = 0; i < _tiles.size(); ++i) {
//		for (int j = 0; j < _tiles.size(); ++j) {
//			int ii = i + I;
//			int jj = j + J;
//			if (isInRange(ii, jj)) {
//				_tiles[ii][jj].draw(-I, -J);
//			}
//		}
//	}
	for (const auto& subVector : _tiles) {
		for (const Tile& tile : subVector) {

			tile.draw(0, 0);
		}
	}
//	int centerX = (_centerUnit->getI() - _centerUnit->getJ()) * 32;
//	int centerY = (_centerUnit->getI() + _centerUnit->getJ()) * 16;
//	for (int i = -5; i <= 5; ++i) {
//		for (int j = -5; j <= 5; ++j) {
//			if (isInRange(i + _centerUnit->getI(), j + _centerUnit->getJ())) {

//				//_tiles[i + _centerUnit->getI()][j + _centerUnit->getJ()].draw(0, 0);
//				_tiles[i + _centerUnit->getI()][j + _centerUnit->getJ()].draw(-centerX, -centerY);
//			}
//		}
//	}
}

void TileMap::tick() {
	int i = 0;
	int centerX = _centerUnit->getX() - Config::WindowW / 2 + 32;
	int centerY = _centerUnit->getY() - Config::WindowH / 2 + 32;;
	for (auto& subVector : _tiles) {
		int j = 0;
		for (Tile& tile : subVector) {
			tile.setX(tile.getX() - centerX);
			tile.setY(tile.getY() - centerY);
			++j;
		}
		++i;
	}
}

Tile *TileMap::getTile(int i, int j) {
	return &_tiles[i][j];
}

Tile *TileMap::getRandomTile() {
	return &_tiles[Helper::random(1, _Size - 2)][Helper::random(1, _Size - 2)];
}

bool TileMap::isInRange(int i, int j) const {
	return i >= 0 && i < _Size && j >= 0 && j < _Size;
}

void TileMap::setCenterUnit(Unit *centerUnit) {
	_centerUnit = centerUnit;
}
