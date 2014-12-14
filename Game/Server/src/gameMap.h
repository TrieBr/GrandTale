#include "GTGameClient.h"
#include <vector>
#include "chatChannel.h"
#include <combatEntity.h>
#include "settings.h"
#include <mapCollisionData.h>

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
	void addCombatEntity(combatEntity* object);
	int generateCombatEntityUID();
	void removeCombatEntity(combatEntity* object);
	void sendMapObjects(GTGameClient *c);
	void sendMapPlayers(GTGameClient *c);
	void broadcastCombatEntityChanges(combatEntity* entity);
	void broadcastPacket(RakNet::BitStream &data, GTGameClient* exclude = NULL, PacketPriority priority = MEDIUM_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, int orderingChannel = 0);
	chatChannel* getMapChatChannel() { return &mapChatChannel; }
	void simulate(double deltaTime);
	mapCollisionData &getCollisionData() { return collisionData; }
	collisionLine* getLineUnderArea(float x, float y, float width); //Gets the first line under the specified area
	std::vector<combatEntity*> getCombatEntitiesInArea(float x, float y, float radius); //Gets list of combat entities in an area
private:
	mapType m_type;
	int m_dataID;
	std::vector<GTGameClient*> characterList;
	std::vector<combatEntity*> combatEntityList;
	chatChannel mapChatChannel;
	mapCollisionData	collisionData;
};

#endif