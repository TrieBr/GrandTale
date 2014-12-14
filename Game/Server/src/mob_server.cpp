#include <mob.h>
#include "gameMap.h"

void mob::hit(hitData &data) {
	RakNet::BitStream dataPacket; //The bitstream
	dataPacket.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY); //Message ID
	dataPacket.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY_HIT); //Message ID
	dataPacket.Write<int>(getUID()); //Send the combat entities unique ID
	dataPacket.Write<hitData>(data);
	this->getParentMap()->broadcastPacket(dataPacket);
	this->::combatEntity::hit(data);
}