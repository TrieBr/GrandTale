#include "itemManager.h"
#include "gameEngineResources.h"
#include "skillManager.h"

#ifndef _H_GLOBALDATA
#define _H_GLOBALDATA


class globalData {
public:
	static void initializeItemManager();
	static void cleanupItemManager();
	static itemManager* getItemManager();

	static void initializeSkillManager();
	static void cleanupSkillManager();
	static skillManager* getSkillManager();



private:
	static itemManager* iManager;
	static skillManager* sManager;
};

#endif