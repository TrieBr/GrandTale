#include "skillHandlerRunner.h"


	void skillHandlerRunner::addSkillHandler(abstractSkillHandler* handler) {
		handlerList.push_back(handler);
	}
	int skillHandlerRunner::getSkillHandlerCount() {
		return handlerList.size();
	}
	abstractSkillHandler* skillHandlerRunner::getSkillHandlerAt(int index) {
		return handlerList[index];
	}
