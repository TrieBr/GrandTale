

#include <gender.h>
#include <faction.h>
#include <equipmentTypes.h>
#include <map>
#include <vector>
#ifndef __CHARACTERCLASS_
#define __CHARACTERCLASS_


namespace character {
enum classType {
	CLASS_NOVICE = 1,
	CLASS_MAGE = 2,
	CLASS_HUNTER = 4,
	CLASS_ALL = 0xFFFFFFFF
};

}



class defaultClassEquipment {
public:
	static std::map<std::vector<int>,int> defaultEquipment;

	static void InitializeDefaultIDs() {
		std::vector<int> vec(4);

		vec[0] = EQUIP_SHIRT;
		vec[1] = character::MALE;
		vec[2] = character::CLASS_NOVICE;
		vec[3] = character::FACTION_GOOD;
		defaultEquipment[vec] = 73; //MALE NOVICE SHIRT GOOD
		vec[0] = EQUIP_GLOVE;
		defaultEquipment[vec] = 74; //MALE NOVICE GLOVE GOOD
		vec[0] = EQUIP_SHOE;
		defaultEquipment[vec] = 72; //MALE NOVICE SHOE GOOD

		vec[0] = EQUIP_SHIRT;
		vec[3] = character::FACTION_BAD; 
		defaultEquipment[vec] = 75; //MALE NOVICE SHIRT BAD
		vec[0] = EQUIP_GLOVE;
		defaultEquipment[vec] = 74; //MALE NOVICE GLOVE BAD
		vec[0] = EQUIP_SHOE;
		defaultEquipment[vec] = 72; //MALE NOVICE SHOE BAD


	}

	static int GetDefaultID(equipType equipmentType, character::genderType gender, character::classType charClass, character::faction charFaction = character::FACTION_GOOD) {
		std::vector<int> vec(4);

		vec[0] = equipmentType;
		vec[1] = gender;
		vec[2] = charClass;
		vec[3] = charFaction;
		std::map<std::vector<int>,int>::iterator i = defaultEquipment.find(vec);
		if (i!=defaultEquipment.end()) {
			return i->second;
		}
		return 0;

	}


};




#endif