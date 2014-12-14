// ----------------------------------------------------------------------
// gamePlayer.h
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------


#include <RakPeerInterface.h>
#include <BitStream.h>
#include "packetIdentifiers.h"
#include "accountMysql.h"
#include "playerData.h"
#include "physicsController.h"

#ifndef _H_GAMEPLAYER
#define _H_GAMEPLAYER
class gameServer;
class map;
class gamePlayer
{
public:
	gamePlayer(); //Constructor
	void handlePacket(RakNet::Packet *packet); //Handle a packet
	gameServer* parentServer; //The parent login server that is managing this player
	bool				authenticated; //Is the player authenticated?
	int					userID; //Our user ID
	RakNet::RakNetGUID	guid; //Raknet GUID
	playerData			pData; //player daya
	short				UID; //Our unique ID 
	map*				currentMap; //Current map
	physicsController*	pController;

	//Functions
	void gotoMap(map *newMap);

	//Outgoing packets
	void sendInitialInfo(); //Send the player all their neccessary info to play the game
private:
	//Incoming packets
	void authenticateTicket(RakNet::Packet *packet); //Generate a transfer ticket
	void movementActionUpdate(RakNet::Packet *packet); //Update movement ebcause an action was executed
};


#endif