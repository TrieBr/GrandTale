
#include "abstractSkillHandlerDummy.h"
#include "equipmentConfiguration.h"
#ifndef _H_ABSTRACTSKILLHANDLER
#define _H_ABSTRACTSKILLHANDLER
namespace RakNet {
	class BitStream;
}

class abstractSkillHandler : public abstractSkillHandlerDummy {
public:
	double getCooldown() { return cooldown; }//Time left until cooldown is complete
	void setCooldown(double cooldown) { this->cooldown = cooldown; }

	virtual void writeSkillHandlerData(RakNet::BitStream &data);
	virtual void readSkillHandlerData(RakNet::BitStream &data);
private:
	

	double cooldown; //Cooldown left on the skill
	
};

#endif