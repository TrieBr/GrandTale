// ----------------------------------------------------------------------
// myData.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Very important static class. Stores information about the user who is playing. Stores their inventory information, equipment info, and pretty much everything.
*/
// ------------------------------------------------------------------------

#include "characterData.h"
#include "entityPlayerMe.h"
#include "skillHandlerList.h"
#include <miscPlayerData.h>

#ifndef _H_MYDATA
#define _H_MYDATA

class myData {
public:
	static character::characterData cData;
	static combatEntity	myCombatEntity;
	static int myUID;
	static entities::gameMap::entityPlayerMe* myPlayer;
	static ItemContainerLinker containerLinks;
	static ItemContainer Inventory_Usable; //Make a container for each type of item
	static ItemContainer Inventory_Equip; //Make a container for each type of item
	static ItemContainer Inventory_Regular; //Make a container for each type of item
	static ItemContainer equipmentContainer;
	static skillHandlerList skills;
	static miscPlayerData miscData;
	static void executeSkill(int skillUniqueID);

};

#endif