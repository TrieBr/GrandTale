
#include "abstractSkillHandler.h"
#include <vector>

#ifndef _H_SKILLHANDLERURUNNER
#define _H_SKILLHANDLERURUNNER

class skillHandlerRunner {
public:
	void addSkillHandler(abstractSkillHandler* handler);
	int getSkillHandlerCount();
	abstractSkillHandler* getSkillHandlerAt(int index);
private:
	std::vector<abstractSkillHandler*> handlerList;

};

#endif