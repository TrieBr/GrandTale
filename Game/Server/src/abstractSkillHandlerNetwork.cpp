#include "abstractSkillHandler.h"
#include <BitStream.h>
void abstractSkillHandler::writeSkillHandlerData(RakNet::BitStream &data) {
	writeSkillHandlerDataDummy(data);
	data.Write<double>(cooldown);

}

void abstractSkillHandler::writeSkillHandlerDataDummy(RakNet::BitStream &data) {
	data.Write<int>(level);
	data.Write<int>(skillID);
	data.Write<double>(timeCast);
	data.Write<SkillCastMode>(mode);
	data.Write<int>(uniqueID);
	data.Write<int>(skillState);
}

void abstractSkillHandler::readSkillHandlerData(RakNet::BitStream &data) {
	readSkillHandlerDataDummy(data);
	data.Read<double>(cooldown);
}

void abstractSkillHandler::readSkillHandlerDataDummy(RakNet::BitStream &data) {
	data.Read<int>(level);
	data.Read<int>(skillID);
	data.Read<double>(timeCast);
	
	data.Read<SkillCastMode>(mode);
	data.Read<int>(uniqueID);
	data.Read<int>(skillState);
}