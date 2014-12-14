#include "attackTarget.h"
#include <vector>
#include <skillCastMode.h>
#include "attackController.h"
#ifndef _H_ABSTRACTSKILLHANDLER
#define _H_ABSTRACTSKILLHANDLER

namespace RakNet {
	class BitStream;
}

class skillUser;
class abstractSkillHandler {

public:
	//Returns the cast time of this skill in seconds
	virtual double getCastTime() {return 1;}
	//Can the "user" execute this skill? This checks basic cooldowns and stuff. Other requirements such as equipment must be done externally
	virtual bool canExecuteSkill() { return false; }
	//Execute the skill, and begin casting it
	virtual void executeSkill() {}
	//Set the cast position (Sets position where this skill was casted)
	virtual void setCastPosition(int x, int y) {}
	//Set attackable targets (eg a list of attackable things in the area, that this skill can target)
	virtual void setAttackableTargets(std::vector<attackTarget*> *targets) {}

	int getLevel() { return level; }
	void setLevel(int level) { this->level = level; }
	int getSkillID() { return skillID; }
	void setSkillID(int ID) { skillID = ID; }
	double getTimeCast() { return timeCast; }
	double getCooldown() { return cooldown; }//Time left until cooldown is complete
	void setCooldown(double cooldown) { this->cooldown = cooldown; }
	SkillCastMode getMode() {return mode; }
	int getUniqueID() { return uniqueID; }
	void setUniqueID(int UID) { uniqueID = UID; }

	skillUser* getCaster() { return caster; }
	void setCaster(skillUser* p) { caster = p; }

	void writeSkillHandlerData(RakNet::BitStream &data);
	void writeSkillHandlerDataDummy(RakNet::BitStream &data);

	void readSkillHandlerData(RakNet::BitStream &data);
	void readSkillHandlerDataDummy(RakNet::BitStream &data);
private:
	int level; //Level of the skill
	int skillID; //ID of this skill
	double timeCast; //Time elapsed since the skill was cast
	double cooldown; //Cooldown left on the skill
	SkillCastMode mode; //Current mode of this skill
	int uniqueID; //Unique ID for this handler
	skillUser* caster; //The caster for this skill
protected:
	int skillState; //Variable for controlling the state of the skill. USed in derived handlers
};


//An skill execution might look like this (Pseudo code)
/*
abstractSkillHandler attack;
if (attack.canExecuteSkill()) {
	attack.setCastPosition(0,0);
	attack.setAttackableTargets(Map.getAttackableTargets());
	attack.executeSkill();
}



*/

#endif