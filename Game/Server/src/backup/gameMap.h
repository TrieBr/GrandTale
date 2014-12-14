#include "GTGameClient.h"
#include <vector>

#ifndef _GAMEMAP_
#define _GAMEMAP_
enum mapType {
	e_default, //Default map for a specific ID (eg mapID 0)
	e_instanced, //Like a default map, but not the "default/global" version, its an instanced version seperate from the maon
	e_custom //Custom created map, doesn't usually have a mapID for data
};

class gameMap {
public:
	static gameMap loadMapFromID(int id, mapType type = e_default);
	mapType	getMapType() { return m_type; }
	int getMapDataID() { return m_dataID; }
	void addCharacter(GTGameClient* c);
	void removeCharacter(GTGameClient* c);
	void sendMapObjects(GTGameClient *c);
	void sendMapPlayers(GTGameClient *c);
private:
	mapType m_type;
	int m_dataID;
	std::vector<GTGameClient*> characterList;
};

#endif