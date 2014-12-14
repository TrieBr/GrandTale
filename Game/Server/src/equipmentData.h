
#include <string>
#include <map>
#include <equipmentTypes.h>

#ifndef _H_EQUIPMENTDATA
#define _H_EQUIPMENTDATA



struct equipmentData {
	int id;
	int type;
	std::string name;
};


class equipmentDataManager {
public:
	static void getAllEquipmentData(std::string databaseName, std::map<int,equipmentData*> *mapFill = &equipmentList); //Grab all equipment data from sqllite database, and fill the container
	static std::map<int,equipmentData*> equipmentList; //Container with all of the equipment data
};

#endif