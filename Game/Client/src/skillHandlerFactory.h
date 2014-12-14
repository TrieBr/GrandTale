#include "abstractSkillHandler.h"

#include "skillHandler_1.h"

class skillHandlerFactory {
public:
	static abstractSkillHandler* generateHandler(int skillID) {
		switch (skillID) {
			case 1: return new skillHandler_1(); break;
		}
		return NULL;
	}


};