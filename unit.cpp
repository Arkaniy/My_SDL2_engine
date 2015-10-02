#include "unit.h"
#include "helper.h"

Unit::Unit() {
	_tileMap = nullptr;
}

void Unit::draw() const {
	_picture->draw(_masterTile->getX(), _masterTile->getY());
}

void Unit::handleEvent(SDL_Event &event) {
	switch (event.key.keysym.sym) {
	case SDLK_w:
		move(-1, 0);
		break;
	case SDLK_s:
		move(1, 0);
		break;
	case SDLK_a:
		move(0, -1);
		break;
	case SDLK_d:
		move(0, 1);
		break;
	}
}

void Unit::initRandomCoordinates() {
	Tile *tile = nullptr;
	do {
		tile = _tileMap->getRandomTile();
	} while (tile->getTileType() != TT_Passable);
	setMasterTile(tile);
}

void Unit::setTileMap(TileMap *tileMap) {
	_tileMap = tileMap;
}

void Unit::move(int di, int dj) {
	if (_tileMap->getTile(_masterTile->getI() + di, _masterTile->getJ() + dj)->getTileType() == TT_Passable) {
		setMasterTile(_tileMap->getTile(_masterTile->getI() + di, _masterTile->getJ() + dj));
	}
}
