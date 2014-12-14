#include "skillData.h"
#ifndef _SKILLMANAGER
#define _SKILLMANAGER


class skillManager {
public:
	skillData GetSkill(int id); 
	void SetSkill(int id, skillData &skill);
	void allocateSkills(int size);
private:
	skillData* skills;
	int skillCount;

};
#endif 