#include "abstractSkillHandler.h"
#include "skillHandler_1.h"


#ifndef _H_SKILLHANDLERFACTORY
#define _H_SKILLHANDLERFACTORY

//USed to generate a new instance of a skill handler based off the skill ID
class skillHandlerFactory {
public:
	//Returns a new instance of a skill handler for the specified ID
	static abstractSkillHandler* generateSkillHandler(int skillID) {
		switch (skillID) {
			case 1: return new skillHandler_1(); break;
		}
		return NULL; //Unable to find a skill handler for the specified ID
	}

};

#endif