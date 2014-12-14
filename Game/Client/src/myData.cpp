

#include "myData.h"
#include "gameServer.h"
character::characterData myData::cData;
combatEntity	myData::myCombatEntity;
int myData::myUID;
entities::gameMap::entityPlayerMe* myData::myPlayer = NULL;
ItemContainerLinker myData::containerLinks;
ItemContainer myData::Inventory_Usable; //Make a container for each type of item
ItemContainer myData::Inventory_Equip; //Make a container for each type of item
ItemContainer myData::Inventory_Regular; //Make a container for each type of item
ItemContainer myData::equipmentContainer;
skillHandlerList myData::skills;
miscPlayerData myData::miscData;

void myData::executeSkill(int skillUniqueID) {
	abstractSkillHandler* skillH = myData::skills.getSkillHandler(skillUniqueID);
	if (myData::myPlayer!=NULL) {
		myData::myPlayer->addSkillHandler(skillH);
		//We would want to check if we can cast the skill here
		skillH->ExecuteSkill(); //Execute the skill
		networking::gameServer::skill_execute(skillUniqueID);
	}

}