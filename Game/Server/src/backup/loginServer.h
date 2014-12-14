// ----------------------------------------------------------------------
// loginServer.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Backbone of the loginServer. Handles connections.
*/
// ------------------------------------------------------------------------
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <DS_Map.h>
#include "loginPlayer.h"
#include "MYSQLHandler.h"
#include "loginServerGameServerManager.h"
#include "gameDataMysql.h"

class loginServer;

class loginServer {
public:
	void initialize(unsigned short listenPort, unsigned int gameServerPort); //Initialize the server
	bool handle(); //one "step" that handles messages. Should be called once per "Frame".
	void shutdown(); //Shuts down the server
	accountMysql* mysqlAccounts; //The mysql handle
	gameDataMysql* mysqlGameData; //Data for the gameplay data

	uint32_t sendMessage(RakNet::BitStream *bitStream,RakNet::AddressOrGUID systemIdentifier, bool broadcast = false, PacketPriority priority = MEDIUM_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, int orderingChannel = 0);
	static unsigned char GetPacketIdentifier(RakNet::Packet *p); //Get a packet identifier
	loginServerGameServerManager gameServerManager; //Object used for managing game servers connected to this login server.
private:
	RakNet::RakPeerInterface* clientInterface; //The main interface for the connected clients

	DataStructures::Map<RakNet::RakNetGUID,loginPlayer*> playerList; //List of players on the login server
	//Packet handlers
	void acceptPlayer(RakNet::Packet *packet); //Accept a new player's connection
};