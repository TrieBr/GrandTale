#include "mobFactory.h"
#include "database.h"
std::vector<mob> mobFactory::mobList;

//Downloads all the mobs from the database into the "default" mob list
void mobFactory::InitializeMobs() {
	queries::downloadMobs(gameDB);
}

//Generate a new mob based on the Mob ID 
mob* mobFactory::getMob(int mobID) {
	if (mobID<=mobList.size()) {
		mob* nMob = new mob(mobList[mobID-1]);
		nMob->setCurrentHealth(nMob->getTotalStat(STAT_HP));
		nMob->setCurrentMana(nMob->getTotalStat(STAT_MP));
		return nMob;
	}
}
//Add a new mob to the mob list
void mobFactory::addMob(mob newMob) {
	mobList.push_back(newMob);
}
