#include "gameMap.h"
#include <packetOpCodes.h>
#include <sstream>
#include <collisionCheck.h>
#include <formulas.h>
gameMap gameMap::loadMapFromID(int id, mapType type) {
	gameMap newMap;
	newMap.m_dataID =id;
	newMap.m_type = type;

	std::stringstream buf;
	buf << GAME_MAP_DATA << id << ".map";
	ALLEGRO_FILE *mapFile = al_fopen(buf.str().c_str(),"rb");
	newMap.getCollisionData().loadMapData(mapFile);
	al_fclose(mapFile);
	
	return newMap;
}


void gameMap::addCharacter(GTGameClient* c) {
	characterList.push_back(c);
	mapChatChannel.addPlayer(c);
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]!=c) {
			c->sendPlayerData(characterList[i]);
		}
	}
}

void gameMap::removeCharacter(GTGameClient* c) {
	mapChatChannel.removePlayer(c);
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]==c) {
			characterList.erase(characterList.begin()+i);
			return;
		}
	}
}

void gameMap::addCombatEntity(combatEntity* object) {
	object->setParentMap(this);
	object->setUID(generateCombatEntityUID());
	combatEntityList.push_back(object);
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]!=object) {
			characterList[i]->sendNewCombatEntity(object);
		}
	}
}

int gameMap::generateCombatEntityUID() {
	
	int UID = rand() % 1000;
	while (true) {
		UID = rand() % 1000;
		bool unique = true;
		for (unsigned int i=0; i<combatEntityList.size(); i++) {
			if (combatEntityList[i]->getUID()==UID) {
				unique = false;
			}
		}
		if (unique) break;
	}

	return UID; 
}

void gameMap::removeCombatEntity(combatEntity* object) {
	for (unsigned int i=0; i<combatEntityList.size(); i++) {
		if (combatEntityList[i]==object) {
			combatEntityList.erase(combatEntityList.begin()+i);
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

void gameMap::broadcastCombatEntityChanges(combatEntity* entity) {
	RakNet::BitStream data;
	data.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY);
	data.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY_UPDATE);
	data.Write<int>(entity->getUID());
	entity->writeCombatData(data);
	broadcastPacket(data);
}

void gameMap::broadcastPacket(RakNet::BitStream &data, GTGameClient* exclude, PacketPriority priority, PacketReliability reliability, int orderingChannel){
	for(unsigned int i=0; i<characterList.size(); i++) {
		if (characterList[i]!=exclude) {
			characterList[i]->sendPacket(data,priority,reliability,orderingChannel);
		}
	}
}

void gameMap::simulate(double deltaTime) {
	for (unsigned int i=0; i<combatEntityList.size(); i++) {
			combatEntityList[i]->update(deltaTime);
	}
}

collisionLine* gameMap::getLineUnderArea(float x, float y, float width) { //Gets the first line under the specified area

	collisionLine* closestLine = NULL;
	for (int yy=this->getCollisionData().getHeight(); yy>y; yy--) {
		for (collisionLineListNode* i = this->getCollisionData().getRootCollisionLine(); i!=NULL; i=i->next) {
			Point p;
			p.x = x;
			p.y = yy;
			if (Collision::pointInLine(p,*i->line)) {
				closestLine = i->line;
			}
		}
	}
	return closestLine;
	
}

std::vector<combatEntity*> gameMap::getCombatEntitiesInArea(float x, float y, float radius) { //Gets list of combat entities in an are
	 std::vector<combatEntity*> ret;
	for (unsigned int i=0; i<combatEntityList.size(); i++) {
		if (formulas::pointDistance(combatEntityList[i]->getX(),combatEntityList[i]->getY(),x,y)<=radius) {
			ret.push_back(combatEntityList[i]);
		}
	}
	return ret;
}