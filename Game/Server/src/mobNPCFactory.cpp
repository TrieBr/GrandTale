#include "mobNPCFactory.h"

#include "database.h"
std::vector<mobNPC> mobNPCFactory::mobList;

//Downloads all the mobs from the database into the "default" mob list
void mobNPCFactory::InitializeMobs() {
	queries::downloadNPCMobs(gameDB);
}

//Generate a new mob based on the Mob ID 
mobNPC* mobNPCFactory::getMobNPC(int mobID) {
	if (mobID<=mobList.size()) {
		return new mobNPC(mobList[mobID-1]);
	}
}
//Add a new mob to the mob list
void mobNPCFactory::addMobNPC(mobNPC newMob) {
	mobList.push_back(newMob);
}
