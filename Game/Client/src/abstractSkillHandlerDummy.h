#include <iostream>
#include <skillCastMode.h>
#ifndef _H_ABSTRACTSKILLHANDLERDUMMY
#define _H_ABSTRACTSKILLHANDLERDUMMY
namespace entities
{
	namespace gameMap
	{
class entityPlayer;
	}
}
namespace RakNet {
	class BitStream;
}
class abstractSkillHandlerDummy {
public:
	virtual void Handle(entities::gameMap::entityPlayer* playerHandler) {

	}
	virtual void ExecuteSkill() {
		std::cout << "Executing skill: " << this->getUniqueID() << std::endl;
	}

	int getLevel() { return level; }
	void setLevel(int level) { this->level = level; }
	int getSkillID() { return skillID; }
	void setSkillID(int ID) { skillID = ID; }
	double getTimeCast() { return timeCast; }
	SkillCastMode getMode() {return mode; }
	int getUniqueID() { return uniqueID; }
	void setUniqueID(int UID) { uniqueID = UID; }

	virtual void writeSkillHandlerData(RakNet::BitStream &data);
	virtual void readSkillHandlerData(RakNet::BitStream &data);
private:
	int level; //Level of the skill
	int skillID; //ID of this skill
	double timeCast; //Time elapsed since the skill was cast
	SkillCastMode mode; //Current mode of this skill
	int uniqueID; //Unique ID for this handler
protected:
	int skillState; //Variable for controlling the state of the skill. USed in derived handlers

};

#endif