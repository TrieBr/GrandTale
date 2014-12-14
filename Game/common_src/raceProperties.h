
#include <iostream>

#ifndef _H_RACEPROPERTIES
#define _H_RACEPROPERTIES

enum RACE {
	RACE_ELDER = 1,
	RACE_OORKA = 2, 
	RACE_UNDEAD = 4,
	RACE_NORELF = 8,
};


class raceProperties {
public:
	static bool requiresEar(RACE race) {
		switch (race) {
		case RACE_ELDER: return false; break;
		case RACE_OORKA: return true; break;
		case RACE_UNDEAD: return false; break;
		case RACE_NORELF: return true; break;
		default : {
			std::cout << "[ERROR] Requested 'requiredEar()' for unknown race. See raceProperties.h" << std::endl;
			return false;
			break;
				  }
		}

	}



};

#endif

