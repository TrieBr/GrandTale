#include <vector>
#include "abstractSkillHandler.h"

#ifndef _H_SILLHANDLERLIST
#define _H_SILLHANDLERLIST

class skillHandlerList {
public:
	int addSkillHandler(abstractSkillHandler *handler);
	int getSkillHandlerCount();
	abstractSkillHandler* getSkillHandlerAt(int index); 
	abstractSkillHandler* getSkillHandler(int UniqueID); 

private:
	std::vector<abstractSkillHandler*> skillList;
};

#endif