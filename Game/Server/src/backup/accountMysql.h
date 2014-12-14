// ----------------------------------------------------------------------
// accountMysql.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	Used for handling queries to the accounts database (mainly authenticating users)
*/
// ------------------------------------------------------------------------

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include "MYSQLHandler.h"
#include <string>
#include <RakString.h>

#ifndef _H_ACCOUNTMYSQL
#define _H_ACCOUNTMYSQL

enum verifyCredentialError
{
	INVALID_PASSWORD = -1,
	UNKNOWN_USERNAME = -2,
	DATABASE_ERROR = -3
};


class accountMysql : public MYSQLHandler
{
public:
	int verifyCredentials(std::string username, std::string password); //Verifies user credentials. Returns the userID on success or verifyCredentialError on error.

};

#endif