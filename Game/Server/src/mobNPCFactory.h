#include "mobNPC.h"
#include <vector>

#ifndef _H_MOBNPCFACTORY
#define _H_MOBNPCFACTORY

class mobNPCFactory {
public:
	//Downloads all the mobs from the database into the "default" mob list
	static void InitializeMobs();
	//Generate a new mob based on the Mob ID 
	static mobNPC* getMobNPC(int mobID);

	//Add a new mob to the mob list
	static void addMobNPC(mobNPC newMob);

private:
	static std::vector<mobNPC> mobList;


};


#endif