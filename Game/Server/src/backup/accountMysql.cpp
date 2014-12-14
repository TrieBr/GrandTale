// ----------------------------------------------------------------------
// accountMysql.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------


#include "accountMysql.h"


int accountMysql::verifyCredentials(std::string username, std::string password) {  //Verifies user credentials. Returns the userID on success or verifyCredentialError on error.
	mysqlpp::Query query = this->connection->query(RakNet::RakString("SELECT password,id FROM members WHERE username = '%s'",username.c_str()).C_String());
	if (mysqlpp::StoreQueryResult res = query.store()) { //Store the result
		if (res.num_rows()>0) { //If some rows were returned
			if (res[0][0]==password){ //Password matches, so user is authenticated.
				return res[0][1]; //Return the user ID
			}else{ //Password does not match
				return INVALID_PASSWORD; //Invalid password
			}
		}else{ //No rows returned; username not found; username does not exist, so return the error
			return UNKNOWN_USERNAME;
		}
	}else{
		std::cout << "[MYSQL (Accounts)] " << connection->error() << std::endl;
		return DATABASE_ERROR;
	}
}