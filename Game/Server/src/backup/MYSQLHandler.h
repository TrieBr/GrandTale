// ----------------------------------------------------------------------
// MYSQL.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Provides an interface with a database.
*/
// ------------------------------------------------------------------------

#include <mysql++.h>
#include <string>

#ifndef _H_MYSQLHANDLER
#define _H_MYSQLHANDLER

class MYSQLHandler
{
public:
	bool connect(std::string host, std::string db, std::string username, std::string password);
	~MYSQLHandler(); //Destructor

private:

protected:
	mysqlpp::Connection* connection; //The connection to the database

};

#endif