// ----------------------------------------------------------------------
// gameDataMysql.h
//     Copyright � Brad Triebwasser 2010
/* Description:

*/

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include "MYSQLHandler.h"
#include <string>
#include <RakString.h>
#include <vector>
#include <characterData.h>

#ifndef _H_GAMEDATAMYSQL
#define _H_GAMEDATAMYSQL

class gameDataMysql : public MYSQLHandler
{
public:
	character::characterData getCharacterData(int charID); //Downloads a list of characters associated with the specified account ID
	std::vector<int> getCharaceterIDs(int accountID); //Gets a list of characters on an account
	int addCharacter(character::characterCustomization &customization, std::string charName, int accountID); //Adds a character and returns its ID
	int removeCharacter(int charID); //Deletes a character
};

#endif