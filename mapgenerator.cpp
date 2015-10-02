#include <queue>
#include <algorithm>
#include "mapgenerator.h"
#include "helper.h"

MapGenerator::MapGenerator() {}

MapGenerator &MapGenerator::getInstance() {
	static MapGenerator instance;
	return instance;
}

void MapGenerator::generate(TileMap *tileMap) {
	_tileMap = tileMap;
	_mapSize = tileMap->_tiles.size();
	for (auto& subVector : tileMap->_tiles) {
		for (Tile& tile : subVector) {
			tile.setTileType(TT_TOTAL);
		}
	}
	_nRooms = pow(tileMap->_tiles.size(), 2.0) / (pow(_RoomsMaxSize, 2) * 3);
	_rooms.clear();
	for (int i = 0; i < _nRooms; i++) {
		_rooms.push_back(createRoom());
	}
	for (size_t i = 1; i < _rooms.size(); i++) {
		generatePassage(_rooms[i], _rooms[i - 1]);
	}
	generateWalls();
}

int MapGenerator::calculateRoomCost(Room room, const Room &finish) {
	room.cost = abs(finish.iS - room.iS) + abs(finish.jS - room.jS); // manhetten distance
	if (_tileMap->_tiles[room.iS][room.jS].getTileType() != TT_Passable) {
		return room.cost + 30;
	}
	return room.cost;
}

MapGenerator::Room MapGenerator::createRoom() {
	Room newRoom;
	// find free space
	do {
		newRoom.h = Helper::random(2, _RoomsMaxSize);
		newRoom.w = Helper::random(2, _RoomsMaxSize);
		newRoom.i = Helper::random(2, _mapSize - newRoom.h - 2);
		newRoom.j = Helper::random(2, _mapSize - newRoom.w - 2);
	} while (std::find_if(std::begin(_rooms), std::end(_rooms), newRoom) != std::end(_rooms));
	// mark room
	for (int i = 0; i < newRoom.h; i++) {
		for (int j = 0; j < newRoom.w; j++) {
			_tileMap->_tiles[i + newRoom.i][j + newRoom.j].setTileType(TT_Passable);
		}
	}


	// set point for search
	newRoom.iS = Helper::random(newRoom.i, newRoom.i + newRoom.h - 1);
	newRoom.jS = Helper::random(newRoom.j, newRoom.j + newRoom.w - 1);
	return newRoom;
}

void MapGenerator::generatePassage(const Room& from, Room to) {
	std::vector<int> parents;
	parents.resize(_mapSize * _mapSize);
	//int parents[Config::SizeTileMap * Config::SizeTileMap];
	for (int &parent : parents) {
		parent = -1;
	}
	std::priority_queue<Room> active;
	active.push(from);

	const int directions[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	while (!active.empty()) {
		const Room current = active.top();
		active.pop();
		if (current == to) {
			break;
		}
		for (int i = 0; i < 4; ++i) {
			Room room(current.iS - directions[i][0], current.jS - directions[i][1], 0);
			if (_tileMap->isInRange(room.iS, room.jS) && parents[room.iS * _mapSize + room.jS] < 0) {
				room.cost = calculateRoomCost(room, to);

				//_tileMap->_tiles[room.iS][room.jS].setTileType(TT_Wall);
				//std::this_thread::sleep_for(std::chrono::milliseconds(65));

				parents[room.iS * _mapSize + room.jS] = i;
				active.push(room);
			}
		}
		//world[current.iS][current.jS].terrain = Map::Terrain::passability;
	}
	while (!(to == from)) {
		const int i = parents[to.iS * _mapSize + to.jS];
		_tileMap->_tiles[to.iS][to.jS].setTileType(TT_Passable);
		_tileMap->_tiles[to.iS + directions[i][1]][to.jS + directions[i][0]].setTileType(TT_Passable);
		//_tileMap->_tiles[to.iS - directions[i][1]][to.jS - directions[i][0]].setTileType(TT_Passable);
		to.iS += directions[i][0];
		to.jS += directions[i][1];
	}
}

void MapGenerator::generateWalls() {
	const int offsets[8][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 },
		{ 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
	};
	for(int i = 0; i < _mapSize; ++i) {
		for (int j = 0; j < _mapSize; ++j) {
			if (_tileMap->_tiles[i][j].getTileType() == TT_TOTAL) {
				for (int k = 0; k < 8; ++k) {
					if (_tileMap->isInRange(i + offsets[k][0], j + offsets[k][1])) {
						if (_tileMap->_tiles[i + offsets[k][0]][j + offsets[k][1]].getTileType() == TT_Passable) {
							_tileMap->_tiles[i][j].setTileType(TT_Wall);
							break;
						}
					}
				}
			}
		}
	}
}
