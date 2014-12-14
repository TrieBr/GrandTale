
#include "GTGameClient.h"
#include "gameMap.h"
#include <vector>

#ifndef _MAPHANDLER_
#define _MAPHANDLER_

class mapHandler {
public:
	void addMap(const gameMap &newMap); //Add a new map to the handler
	void removeMap(gameMap *mapRemove);
	void updateMaps(double deltaTime);
	gameMap* getDefaultMap(int mapDataID);

private:
	std::vector<gameMap> mapList;

};

#endif