// ----------------------------------------------------------------------
// MYSQL.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	
*/
// ------------------------------------------------------------------------

#include "MYSQLHandler.h"


bool MYSQLHandler::connect(std::string host, std::string db, std::string username, std::string password) {
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

MYSQLHandler::~MYSQLHandler() { //Clean up 
	delete connection; //Delete the connection handle
}