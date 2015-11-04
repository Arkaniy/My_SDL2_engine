#include "unit.h"
#include "helper.h"
#include "resourcesmanager.h"
#include <iostream>
#include "config.h"

Unit::Unit() {
	_tileMap = nullptr;
	//_isMoving = false;
	_lastMove = 0;
	_speed = 15; // tile/second
}

void Unit::draw() const {
	if (isMoving()) {
		_animation->draw(_masterTile->getX(), _masterTile->getY());
	} else {
		_picture->draw(_masterTile->getX(), _masterTile->getY());
	}
}

bool Unit::handleEvent(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
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
	static Uint32 previuos = SDL_GetTicks();
	Uint32 current = SDL_GetTicks();
	if (current - previuos > 1000 / _speed/* || di != _oldDi || dj != _oldDj*/) {
		previuos = current;
		if (_tileMap->getTile(_masterTile->getI() + di, _masterTile->getJ() + dj)->getTileType() == TT_Passable) {
			_oldI = _masterTile->getI();
			_oldJ = _masterTile->getJ();
			_lastMove = current;
			setMasterTile(_tileMap->getTile(_masterTile->getI() + di, _masterTile->getJ() + dj));
		}
	}
}

void Unit::searchWay(int iFinish, int jFinish) {
	int ways[8][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
	int matrix[Config::SizeTileMap][Config::SizeTileMap] = { 0 };
	int count = 1;
	matrix[_masterTile->getI()][_masterTile->getJ()] = count++;
	bool searchOver = false;
	// search
	while (matrix[iFinish][jFinish] == 0 && !searchOver) {
		searchOver = true;  // флаг окончания поиска, защита от зацикливания
		for (int i = 1; i < Config::SizeTileMap - 1; i++) {
			for (int j = 1; j < Config::SizeTileMap - 1; j++) {
				if (matrix[i][j] == count - 1) {
					for (int k = 0; k < 8; k++) {
						if (matrix[i + ways[k][0]][j + ways[k][1]] == 0 &&  // проверка по массиву волны: не проходил тут
								// проходимая и пустая клетка
								((_tileMap->getTile(i + ways[k][0], j + ways[k][1])->getTileType() == TileType::TT_Passable &&
								  _tileMap->getTile(i + ways[k][0], j + ways[k][1])->getLandOverlay() == nullptr) ||
								 ((i + ways[k][0]) == iFinish && (j + ways[k][1]) == jFinish))) { //&&    // или конечная клетка
								//world[i + ways[k][0]][j + ways[k][1]].wasHere) { // + был там
							// ограничение на срез углов у стен
							//if((k>3 && world[i + ways[k][0]][j].state == 1 &&
							//        world[i][j + ways[k][1]].state == 1) || k<4) {
								matrix[i + ways[k][0]][j + ways[k][1]] = count;
								searchOver = false;
							//}
						}
					}
				}
			}
		}
		count++;
	}

	count--;
	int i = iFinish;
	int j = jFinish;

	// come back
	if (!searchOver) {
		std::vector<int> pathBack;
		while (!(_masterTile->getI() == i && _masterTile->getJ() == j)) {
			for (int k = 0; k < 8; k++) {
				if (matrix[i + ways[k][0]][j + ways[k][1]] == count - 1) {
					pathBack.push_back(k);
					i += ways[k][0];
					j += ways[k][1];
					count--;
					break;
				}
			}
		}

		while (!pathBack.empty()) {
//			if(isMoving) {
//				locking.unlock();
//				return;
//			}
			int i = pathBack[pathBack.size() - 1];
			pathBack.pop_back();

			move(-ways[i][0], -ways[i][1]);
//			isMoving = false;
			SDL_Delay(1000 / _speed + 15);
		}

//		if (world[iFinish][jFinish].object == target && target != nullptr)
//			action(world[iFinish][jFinish].object);
	}
}

int Unit::getSpeed() const {
	return _speed;
}

bool Unit::isMoving() const {
	//_isMoving = SDL_GetTicks() - _lastMove < 1000.0 / _speed;
	//return _isMoving;
	return SDL_GetTicks() - _lastMove < 1000 / _speed;
}
