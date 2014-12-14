#include "attackController.h"
#include "gameMap.h"

void attackController::entityDamage(combatEntity* src, combatEntity* dest, hitData &data)
{
	dest->hit(data);
	RakNet::BitStream dataPacket; //The bitstream
	dataPacket.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY); //Message ID
	dataPacket.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY_HIT); //Message ID
	dataPacket.Write<int>(dest->getUID()); //Send the combat entities unique ID
	dataPacket.Write<hitData>(data);
	dest->getParentMap()->broadcastPacket(dataPacket);
}