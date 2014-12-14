#include "equipmentData.h"
#include <sstream>


std::map<int,equipmentData*> equipmentDataManager::equipmentList; //Container with all of the equipment data


void equipmentDataManager::getAllEquipmentData(std::string databaseName, std::map<int,equipmentData*> *mapFill) { //Grab all equipment data from sqllite database, and fill the container
	sqlite3			*database; //Handle to the SQL database
	int				result; //Used for storing results
	sqlite3_stmt	*preparedStatement; //Used for the prepared query
	const char		*tailChar; //Used for the returned tailchar pointer

	result = sqlite3_open(databaseName.c_str(),&database); //Attempt to open the database
	if (result) { //Failed to open it..
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(database));
      sqlite3_close(database);
	}
	//Generate the query
	std::stringstream query;
	query << "SELECT * FROM equipmentData;";
	
	result = sqlite3_prepare(database,query.str().c_str(),query.str().length(),&preparedStatement,&tailChar); //Prepare the statement

	int res = sqlite3_step(preparedStatement);
	while (res==SQLITE_ROW) { //While a row is being returned..
		equipmentData* newEquip =  new equipmentData();

		newEquip->id = sqlite3_column_int(preparedStatement,0);
		newEquip->type = sqlite3_column_int(preparedStatement,1);
		newEquip->name = (const char*)sqlite3_column_text(preparedStatement,2);

		(*mapFill)[newEquip->id] = newEquip; //Add the equip to the container
		res = sqlite3_step(preparedStatement); //Step again, to possibly return another row.
	}
}
	
