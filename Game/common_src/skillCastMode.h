#ifndef _H_SILLCASTMODE
#define _H_SILLCASTMODE

enum SkillCastMode {
	SCM_CASTINGWAIT, //Waiting for cast time to end
	SCM_CASTING, //Executing the skill
	SCM_IDLE, //Not casting or anything
};
#endif