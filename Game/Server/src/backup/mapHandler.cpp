#include "mapHandler.h"


void mapHandler::addMap(const gameMap &newMap) { //Add a new map to the handler
	this->mapList.push_back(newMap);
}
void mapHandler::removeMap(gameMap *mapRemove) {
	for(unsigned int i=0; i<mapList.size(); i++) {
		if (&mapList[i]==mapRemove) {
			mapList.erase(mapList.begin()+i);
			break;
		}
	}
}

gameMap* mapHandler::getDefaultMap(int mapDataID) {
	for(std::vector<gameMap>::iterator it = mapList.begin(); it!=mapList.end(); it++) {
		if (it->getMapType()==e_default) {
			if (it->getMapDataID()==mapDataID) {
				return &(*it);
			}
		}
	}
	return NULL;
}