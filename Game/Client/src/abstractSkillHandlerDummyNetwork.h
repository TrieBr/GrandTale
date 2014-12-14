#include "abstractSkillHandlerDummy.h"
#include <BitStream.h>

void abstractSkillHandlerDummy::writeSkillHandlerData(RakNet::BitStream &data) {
	data.Write<int>(level);
	data.Write<int>(skillID);
	data.Write<double>(timeCast);
	data.Write<SkillCastMode>(mode);
	data.Write<int>(uniqueID);
	data.Write<int>(skillState);
}

void abstractSkillHandlerDummy::readSkillHandlerData(RakNet::BitStream &data) {
	data.Read<int>(level);
	data.Read<int>(skillID);
	data.Read<double>(timeCast);
	data.Read<SkillCastMode>(mode);
	data.Read<int>(uniqueID);
	data.Read<int>(skillState);
}