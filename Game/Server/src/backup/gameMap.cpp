#include "gameMap.h"


gameMap gameMap::loadMapFromID(int id, mapType type) {
	gameMap newMap;
	newMap.m_dataID =id;
	newMap.m_type = type;

	return newMap;
}


void gameMap::addCharacter(GTGameClient* c) {
	characterList.push_back(c);
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]!=c) {
			c->sendPlayerData(characterList[i]);
		}
	}
}

void gameMap::removeCharacter(GTGameClient* c) {
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]==c) {
			characterList.erase(characterList.begin()+i);
			return;
		}
	}
}

void gameMap::sendMapObjects(GTGameClient *c){
	sendMapPlayers(c);
}

void gameMap::sendMapPlayers(GTGameClient *c){
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]!=c) {
			characterList[i]->sendPlayerData(c);
		}
	}
}