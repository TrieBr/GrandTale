#include "skillHandlerList.h"


	int skillHandlerList::addSkillHandler(abstractSkillHandler* handler){
		skillList.push_back(handler);
		return skillList.size();
	}
	int skillHandlerList::getSkillHandlerCount() {
		return skillList.size();
	}
	abstractSkillHandler* skillHandlerList::getSkillHandlerAt(int index) {
		return skillList[index];
	}
	abstractSkillHandler* skillHandlerList::getSkillHandler(int UniqueID) {
		for (unsigned int i=0; i<skillList.size(); i++) {
			if (skillList[i]->getUniqueID()==UniqueID) {
				return skillList[i];
			}
		}
		return NULL;
	}
