#include "mob.h"
#include <characterCustomization.h>

#ifndef _H_MOBNPC
#define _H_MOBNPC

class mobNPC : public mob {
public:
	character::characterCustomization customization;
	void setCustomization(character::characterCustomization c);
	virtual void readCombatData(RakNet::BitStream &data);
	virtual void writeCombatData(RakNet::BitStream &data);
private:



};


#endif