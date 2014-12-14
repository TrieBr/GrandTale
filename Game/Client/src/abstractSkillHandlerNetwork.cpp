#include "abstractSkillHandler.h"
#include <BitStream.h>
void abstractSkillHandler::writeSkillHandlerData(RakNet::BitStream &data) {
	this->::abstractSkillHandlerDummy::writeSkillHandlerData(data);
	data.Write<double>(cooldown);

}

void abstractSkillHandler::readSkillHandlerData(RakNet::BitStream &data) {
	this->::abstractSkillHandlerDummy::readSkillHandlerData(data);
	data.Read<double>(cooldown);

}