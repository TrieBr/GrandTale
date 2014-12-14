#include "abstractClient.h"
#include "characterData.h"


#ifndef _GTGAMECLIENT_
#define _GTGAMECLIENT_

class gameMap;
class GTGameClient : public abstractClient {
public:
	GTGameClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface);
	int charDBID;
	int userDBID;
	int UID; //Unique ID, can be different every time the player connects
	character::characterData cData;
	gameMap* currentMap;


	void mapGoto(gameMap *map); //Transfer the player to a new map
	void sendInitialData(); //Send player initial data when logging in..
	void sendPlayerData(GTGameClient* dest);
};

#endif