#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <vector>
#include "tilemap.h"

class MapGenerator {
public:
	static MapGenerator& getInstance();
	void generate(TileMap *tileMap);
private:
	MapGenerator();
	struct Room {
		int i, j;   // left top corner
		int w, h;   // wigth, height
		int iS, jS; // point for create passages
		int cost;   // cost for A*
		Room() : i(0), j(0), w(0), h(0), iS(0), jS(0), cost(0) {}
		Room(int iS, int jS, int cost) : i(0), j(0), w(0), h(0), iS(iS), jS(jS), cost(cost) {}
		bool operator==(const Room &rhs) const {
			return iS == rhs.iS && jS == rhs.jS;
		}
		bool operator<(const Room &rhs) const {
			return cost > rhs.cost;
		}
		bool operator()(const Room &rhs) const { // test intersection
			return !(rhs.i > (i + h) || i > (rhs.i + rhs.h) || rhs.j > (j + w) || j > (rhs.j + rhs.w));
		}
	};

	static constexpr int _RoomsMaxSize = 6; // in tiles
	int _nRooms;
	TileMap *_tileMap;
	int _mapSize;
	std::vector<Room> _rooms;

	int calculateRoomCost(Room room, const Room& finish);
	Room createRoom();
	void generatePassage(const Room& from, Room to);
	void generateWalls();
};

#endif // MAPGENERATOR_H
