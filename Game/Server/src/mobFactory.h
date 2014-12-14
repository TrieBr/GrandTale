#include <mob.h>
#include <vector>

#ifndef _H_MOBFACTORY
#define _H_MOBFACTORY

class mobFactory {
public:
	//Downloads all the mobs from the database into the "default" mob list
	static void InitializeMobs();
	//Generate a new mob based on the Mob ID 
	static mob* getMob(int mobID);

	//Add a new mob to the mob list
	static void addMob(mob newMob);

private:
	static std::vector<mob> mobList;


};


#endif