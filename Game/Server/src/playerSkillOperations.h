

#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"

class playerSkillOperations : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		int Operation;
		data.Read<int>(Operation);
		if (Operation==(int)gamePackets::SKILL_EXECUTED) { //The client has executed a skill
			int skillUID;
			data.Read<int>(skillUID); //The UID of the skill
			abstractSkillHandler* handler = c.getSkillHandler(skillUID);
			std::cout << "Client Executed Skill: (UID:)" << skillUID << " (SkillID): " << handler->getSkillID() << std::endl;
			if (handler->canExecuteSkill()) {
				handler->executeSkill(); //Handle the actual skill logic..
				RakNet::BitStream data2;
				data2.Write<RakNet::MessageID>(gamePackets::SKILLHANDLER_ACTION);
				data2.Write<RakNet::MessageID>(gamePackets::SKILL_EXECUTED);
				data2.Write<short>(c.UID);
				data2.Write<int>(handler->getSkillID());
				c.getCurrentMap()->broadcastPacket(data2,&c);
			}
		}
	}

};