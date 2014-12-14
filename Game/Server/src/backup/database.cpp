#include "database.h"

database accountDB;
database gameDB;

database::database(std::string host, std::string db, std::string username, std::string password) {
	connect(host,db,username,password);
}

database::database() {

}
bool database::connect(std::string host, std::string db, std::string username, std::string password) {
	connection = new mysqlpp::Connection(false); //Create the connection object
	if (connection->connect(db.c_str(),host.c_str(),username.c_str(),password.c_str())) { //connect to the mysql server
		connection->set_option(new mysqlpp::ReconnectOption(true)); //Set to reconnect automatically
		std::cout << "[MYSQL] " << "Connected to MYSQL server." << std::endl;
		return true; //Sucessful connect
	}else{
		std::cout <<"[MYSQL] " << connection->error() << std::endl;
		return false; //Failed to connect
	}
}

bool database::query(std::string queryString) {
	mysqlpp::Query query = this->connection->query(queryString);
	lquery = &query;
	if (lastResult = query.store()) { //Store the result
			return true;
		}else{
			std::cout << "[MYSQL Error] " << connection->error() << std::endl;
			return false;
		}
		return false;
	}



character::characterData queries::getCharacterData(database& db, int charID) {
	character::characterData newCharacter;
	db.pushResult();
	if (db.query(RakNet::RakString("SELECT * FROM characters WHERE id = %i",charID).C_String())) {
		if (db.result().num_rows()>0) {
            mysqlpp::String t = (db.result()[0][2]);
			newCharacter.charName = t.c_str();
            
				newCharacter.mapID = db.result()[0][3];
				newCharacter.x = db.result()[0][4];
				newCharacter.y = db.result()[0][5];

				newCharacter.hairType = db.result()[0][6];
				newCharacter.hairColor = db.result()[0][7];
				newCharacter.facialHairType = db.result()[0][8];
				newCharacter.eyeType = db.result()[0][9];
				newCharacter.mouthType = db.result()[0][10];
				newCharacter.skinColor = db.result()[0][11];
				newCharacter.race = db.result()[0][12];
				newCharacter.gender = db.result()[0][13];

				newCharacter.currentHP = db.result()[0][14];
				newCharacter.maxHP = db.result()[0][15];
				newCharacter.currentMP= db.result()[0][16];
				newCharacter.maxMP = db.result()[0][17];

				newCharacter.equipmentBelt = 8;
				newCharacter.equipmentGlove = 9;
				newCharacter.equipmentHelmet = 0;
				newCharacter.equipmentPants = 13;
				newCharacter.equipmentShirt = 10;
				newCharacter.equipmentShoe = 11;
				newCharacter.equipmentShoulder = 12;
		}else{
		  std::cout << "DB Handler fetching invalid character ID." << charID << std::endl;
		}
		 
	}
		db.popResult();
		return newCharacter;
}