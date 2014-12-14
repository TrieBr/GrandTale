#include "abstractSkillHandler.h"
#include <map>
#include <combatEntity.h>
#ifndef _H_SKILLUSER
#define _H_SKILLUSER

//A class that can execute skills on attackTarget's
class skillUser :public combatEntity {
public:
	int addAvailableSkill(abstractSkillHandler* skillHandler); //Adds a handler and returns its Unique ID
	int getAvailableSkillCount();
	abstractSkillHandler* getSkillHandlerAt(int index); //Get the specified index
	abstractSkillHandler* getSkillHandler(int UniqueID); //Get handler based on unique ID
private:
	std::map<int, abstractSkillHandler*> availableSkills; //List of available skills for this skill user. Mapped by Unique ID
	int generateSkillHandlerUniqueID();
}; 

#endif