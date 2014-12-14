#include "mobNPC.h"


void mobNPC::readCombatData(RakNet::BitStream &data) {
	this->::mob::readCombatData(data);
	this->customization.readCharacterCustomization(data);

}
void mobNPC::writeCombatData(RakNet::BitStream &data) {
	this->::mob::writeCombatData(data);
	this->customization.writeCharacterCustomization(data);
}