#include <iostream>
#include "tilemap.h"
#include "resourcesmanager.h"
#include "config.h"
#include <ctime>
#include "landoverlay.h"
#include "unit.h"
#include "mapgenerator.h"
#include "helper.h"
#include "fpscounter.h"
#include "screen.h"
#include "iomanip"

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
	default:
		_picture = nullptr;
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

LandOverlay *Tile::getLandOverlay() {
	return _landOverlay;
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


void Tile::draw() const {
	if (_picture != nullptr) {
		_picture->draw(_x, _y);
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
	for (auto& subVector : _tiles) {
		int j = 0;
		subVector.resize(_Size);
		for (Tile& tile : subVector) {
			tile.setTileType(TT_Passable);
			tile.setI(i);
			tile.setJ(j);
			tile.setX((j - i) * 32);
			tile.setY((i + j) * 16);
			++j;
		}
		++i;
	}
	MapGenerator::getInstance().generate(this);
}

void TileMap::draw() const {
	for (const auto& subVector : _tiles) {
		for (const Tile& tile : subVector) {
			tile.draw();
		}
	}
}


#include <thread>
bool TileMap::handleEvent(SDL_Event &event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int i = _centerUnit->getI() + (-2 * event.motion.x + Config::WindowW + 4 * event.motion.y - 2 * Config::WindowH) / 128.;
		int j = _centerUnit->getJ() + ( 2 * event.motion.x - Config::WindowW + 4 * event.motion.y - 2 * Config::WindowH) / 128.;
		if (isInRange(i, j)) {
			Unit *lo = dynamic_cast<Unit*>(_tiles[i][j].getLandOverlay());
			if (lo != nullptr) {
				lo->echo();
			}
			else {
				std::cout << "Nobody is here\n";
				std::thread thr(&Unit::searchWay, _centerUnit, i, j);
				thr.detach();
			}
		}
	}
}

void TileMap::update() {

//  TODO: soft moving

//	static double start = 0;
//	static int n = 1;
//	//int fps = FpsCounter::getInstance().getFps();
//	int fps = 60;
//	float d = 0;
//	float dx = 0;
//	float dy = 0;
//	if (start++ == fps / _centerUnit->getSpeed() || !_centerUnit->isMoving()) {
//		start = 0;
//		n = 1;
//	} else {
//		d = start / static_cast<double>(fps) * _centerUnit->getSpeed();

//		std::cout << std::setw(3) << n++ << " -> " << std::setw(9) << 1 - d <<
//				  "; " << _centerUnit->getX() << ", " << _centerUnit->getY() <<
//				  "; " << _centerUnit->getI() << ", " << _centerUnit->getJ() << "\n";
//		if (_centerUnit->getI() != _centerUnit->_oldI) { // 0
//			if (_centerUnit->getI() < _centerUnit->_oldI) { // -1
//				dx = 1;
//				dy = -1;
//			} else { // 1
//				dx = -1;
//				dy = 1;
//			}
//		} else {
//			if (_centerUnit->getJ() < _centerUnit->_oldJ) {
//				dx = -1;
//				dy = -1;
//			} else {
//				dx = 1;
//				dy = 1;
//			}
//		}
//	}
//	dx *= 1.0 - d;
//	dy *= 1.0 - d;

	int dx = 0; // temporary value
	int dy = 0; // until fix above

	int centerX = _centerUnit->getX() - Config::WindowW / 2 + 32 - dx * 32;
	int centerY = _centerUnit->getY() - Config::WindowH / 2 + 32 - dy * 16;
	for (auto& subVector : _tiles) {
		for (Tile& tile : subVector) {
			tile.setX(tile.getX() - centerX);
			tile.setY(tile.getY() - centerY);
		}
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
