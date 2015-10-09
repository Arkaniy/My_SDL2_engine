#include "unit.h"
#include "helper.h"
#include "resourcesmanager.h"

Unit::Unit() {
	_tileMap = nullptr;
	_isMoving = false;
}

void Unit::draw() const {
	if (_isMoving) {
		_animation->draw(_masterTile->getX(), _masterTile->getY());
	} else {
		_picture->draw(_masterTile->getX(), _masterTile->getY());
	}
}

void Unit::handleEvent(SDL_Event &event) {
	switch (event.key.keysym.sym) {
	case SDLK_w:
		_animation = ResourcesManager::getInstance().getAnimation(TA_ManRight);
		move(-1, 0);
		break;
	case SDLK_s:
		_animation = ResourcesManager::getInstance().getAnimation(TA_ManLeft);
		move(1, 0);
		break;
	case SDLK_a:
		_animation = ResourcesManager::getInstance().getAnimation(TA_ManLeft);
		move(0, -1);
		break;
	case SDLK_d:
		_animation = ResourcesManager::getInstance().getAnimation(TA_ManRight);
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
	static int oldDi = di;
	static int oldDj = dj;
	static Uint32 previuos = SDL_GetTicks();
	Uint32 current = SDL_GetTicks();
	// 100 - delay, how quick unit moves; todo: set unit speed
	if (current - previuos > 100 || di != oldDi || dj != oldDj) {
		previuos = current;
		if (_tileMap->getTile(_masterTile->getI() + di, _masterTile->getJ() + dj)->getTileType() == TT_Passable) {
			oldDi = di;
			oldDj = dj;
			setMasterTile(_tileMap->getTile(_masterTile->getI() + di, _masterTile->getJ() + dj));
		}
	}
}
