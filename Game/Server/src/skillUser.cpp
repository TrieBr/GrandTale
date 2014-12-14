#include "skillUser.h"

	int skillUser::addAvailableSkill(abstractSkillHandler* skillHandler) { //Adds a handler and returns its Unique ID
		int UID =generateSkillHandlerUniqueID();
		skillHandler->setCaster(this);
		skillHandler->setUniqueID(UID);
		availableSkills[UID] = skillHandler;
		return UID;
	}
	int skillUser::getAvailableSkillCount() {
		return availableSkills.size();
	}
	abstractSkillHandler* skillUser::getSkillHandlerAt(int index) { //Get the specified index
		int indexCount = 0;
		for (std::map<int, abstractSkillHandler*>::const_iterator i = availableSkills.begin(); i!=availableSkills.end(); i++) {
			if (indexCount==index) {
				return i->second;
			}
			indexCount++;
		}
		return NULL;
	}
	abstractSkillHandler* skillUser::getSkillHandler(int UniqueID) { //Get handler based on unique ID
		if (availableSkills.find(UniqueID)!=availableSkills.end()) {
			return availableSkills.find(UniqueID)->second; //TODO: Optimize to it doesnt find() twice
		}
		return NULL;
	}

	int skillUser::generateSkillHandlerUniqueID() {

		int uid = rand() % 200000;
		while (1) {
			if (availableSkills.find(uid)==availableSkills.end()) { //Unique ID was not found in available skills
				return uid; //Return the unique ID
			}
			uid = rand() % 200000; //Generate another uinque ID
		}
	}