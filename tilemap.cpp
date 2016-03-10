#include <iostream>
#include "tilemap.h"
#include "resourcesmanager.h"
#include "config.h"
#include <ctime>
#include "landoverlay.h"
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
	_centerUnit = nullptr;
	_scroller.init(50, Config::WindowW-50, 100, Config::WindowH-50, 2);
	_offsetX = 0;
	_offsetY = 0;
	_centerX = 0;
	_centerY = 0;

	int i = 0;
	for (auto& subVector : _tiles) {
		int j = 0;
		subVector.resize(_Size);
		for (Tile& tile : subVector) {
			tile.setTileType(TT_Passable);
			tile._i = i;
			tile._j = j;
			tile._x = (j - i) * 32;
			tile._y = (i + j) * 16;
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

void TileMap::handleEvent(SDL_Event &event) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN: {
		int cx = _scroller.getCenterX();
		int cy = _scroller.getCenterY();

		int i = floor((-2*event.button.x + Config::WindowW + 4*event.button.y - 2*Config::WindowH - 2*cx + 4*cy) / 128. + 0.5);
		int j = floor(( 2*event.button.x - Config::WindowW + 4*event.button.y - 2*Config::WindowH + 2*cx + 4*cy) / 128. - 1.5);

		std::cout << "Handled in  " << i << ", " << j << std::endl;
		break;
	}
	case SDL_MOUSEMOTION:
		_scroller.scroll(event.button.x, event.button.y);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_q) {
			_cen = true;
		} else {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				_listener->handleWidgetEvent(BE_Credits);
			}
		}
		break;
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

//	int dx = 0; // temporary value
//	int dy = 0; // until fix above

//	int centerX = _centerUnit->getX() - Config::WindowW / 2 + 32 - dx * 32;
//	int centerY = _centerUnit->getY() - Config::WindowH / 2 + 32 - dy * 16;

	if (_cen) {
		_scroller.setCenter(_tiles[0][0]._x, _tiles[0][0]._y);
		_cen = false;
	}

	for (auto& subVector : _tiles) {
		for (Tile& tile : subVector) {
			tile._x -= _scroller.getDx();
			tile._y -= _scroller.getDy();
		}
	}

	_scroller.updateCenter();
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
