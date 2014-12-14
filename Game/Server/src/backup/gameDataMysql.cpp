// ----------------------------------------------------------------------
// gameDataMysql.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------



#include "gameDataMysql.h"


std::vector<int> gameDataMysql::getCharaceterIDs(int accountID) { //Gets a list of characters on an account
	std::vector<int> characterIDs;

	mysqlpp::Query query = this->connection->query(RakNet::RakString("SELECT * FROM characters WHERE userid = %i",accountID).C_String());
	if (mysqlpp::StoreQueryResult res = query.store()) { //Store the result
		if (res.num_rows()>0) { //If some rows were returned
			for (unsigned int row=0; row<res.num_rows(); row++) { //For each character returned
					characterIDs.push_back(res[row][0]);
			}
		}

	}
	return characterIDs;
}

character::characterData gameDataMysql::getCharacterData(int charID) { //Downloads a list of characters associated with the specified account ID
	character::characterData newCharacter;

	mysqlpp::Query query = this->connection->query(RakNet::RakString("SELECT * FROM characters WHERE id = %i",charID).C_String());
	if (mysqlpp::StoreQueryResult res = query.store()) { //Store the result
		if (res.num_rows()>0) { //If some rows were returned
			for (unsigned int row=0; row<res.num_rows(); row++) { //For each character returned
                mysqlpp::String t = res[row][2];
				newCharacter.charName = t.c_str();
				newCharacter.mapID = res[row][3];
				newCharacter.x = res[row][4];
				newCharacter.y = res[row][5];

				newCharacter.hairType = res[row][6];
				newCharacter.hairColor = res[row][7];
				newCharacter.facialHairType = res[row][8];
				newCharacter.eyeType = res[row][9];
				newCharacter.mouthType = res[row][10];
				newCharacter.skinColor = res[row][11];
				newCharacter.race = res[row][12];
				newCharacter.gender = res[row][13];

				newCharacter.currentHP = res[row][14];
				newCharacter.maxHP = res[row][15];
				newCharacter.currentMP= res[row][16];
				newCharacter.maxMP = res[row][17];


				/*newCharacter.equipmentBelt = 0;
				newCharacter.equipmentGlove = 0;
				newCharacter.equipmentHelmet = 0;
				newCharacter.equipmentPants = 0;
				newCharacter.equipmentShirt = 0;
				newCharacter.equipmentShoe = 0;
				newCharacter.equipmentShoulder = 0;
				*/

				newCharacter.equipmentBelt = 8;
				newCharacter.equipmentGlove = 9;
				newCharacter.equipmentHelmet = 0;
				newCharacter.equipmentPants = 13;
				newCharacter.equipmentShirt = 10;
				newCharacter.equipmentShoe = 11;
				newCharacter.equipmentShoulder = 12;
				
				
			}
			return newCharacter;
		}else{ //No rows returned; username not found; username does not exist, so return the error
			return newCharacter;
		}
	}else{
		std::cout << "[MYSQL (Game Data)] " << connection->error() << std::endl;
		return newCharacter;
	}

}

	int gameDataMysql::addCharacter(character::characterCustomization &customization, std::string charName,  int accountID) { //Adds a character and returns its ID
		mysqlpp::Query query = this->connection->query(RakNet::RakString("INSERT INTO characters (userid, charname, mapid, x, y, hairtype, haircolor, facialHairType, eyeType, mouthType, skincolor, race, gender)\
																						VALUES   (%i, '%s', %i,%i, %i, %i, %i, %i, %i, %i, %i, %i, %i )",
																						accountID, //User ID
																						charName.c_str(), //Charname
																						0, //mapid
																						0, //x
																						0, //y
																						customization.hairType, //Hair type
																						customization.hairColor, //Hair color
																						customization.facialHairType, //Facial hair type
																						customization.eyeType, //Eye type
																						customization.mouthType, //Mouth type
																						customization.skinColor, //Skin color
																						customization.race, //Race
																						customization.gender //Gender
																						).C_String());
		
		if (mysqlpp::SimpleResult res = query.execute()) {
			return query.insert_id();
			
		}else{
			std::cout << "[MYSQL (Game Data)] " << connection->error() << std::endl;
			return -1;
		}

		
	}

	int gameDataMysql::removeCharacter(int charID) { //Deletes a character
		mysqlpp::Query query = this->connection->query(RakNet::RakString("DELETE FROM characters WHERE id = %i",
																						charID));
		if (mysqlpp::SimpleResult res = query.execute()) {
			return 1 ;
		}else{
			std::cout << "[MYSQL (Game Data)] " << connection->error() << std::endl;
			return 0;
		}

	}
