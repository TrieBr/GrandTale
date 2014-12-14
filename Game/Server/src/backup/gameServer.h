// ----------------------------------------------------------------------
// gameServer.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	The backbone of the game server
*/
// ------------------------------------------------------------------------
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <DS_Map.h>
#include "gamePlayer.h"
#include "accountMysql.h"
#include "gameDataMysql.h"
#include "gameServerLoginServerManager.h"

#ifndef _H_GAMESERVER
#define _H_GAMESERVER

#define ticksPerSecond 33 //How many simulations per second we want to do...
#define snapshotsPerSecond 20 //How many snapshots per second we want to send out..

class gameServer
{
public:
	void initialize(unsigned short listenPort, std::string loginServerHost, unsigned short loginServerPort, std::string serverName); //Initialize the server
	bool handle(); //one "step" that handles messages. Should be called once per "Frame". 
	void shutdown(); //Shuts down the server
	void loadMapData(); //Load all of the map data
	map* getMap(unsigned short ind); //Get map from index
	uint32_t sendMessage(RakNet::BitStream *bitStream,RakNet::AddressOrGUID systemIdentifier, bool broadcast = false, PacketPriority priority = MEDIUM_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, int orderingChannel = 0);
	static unsigned char GetPacketIdentifier(RakNet::Packet *p); //Get a packet identifier
	short	generatePlayerUID(); //Generates a unique ID for a player

	accountMysql*					mysqlAccounts; //The mysql handle
	gameDataMysql*					mysqlGameData; //The mysql handle
	std::string						serverName;
	std::string						broadcastIP;
	short							broadcastPort;
	gameServerLoginServerManager	loginServerConnection;
	RakNet::RakPeerInterface*		clientInterface; //The main interface for the connected clients
	std::vector<map*> mapList; //All of the maps
	
private:
	DataStructures::Map<RakNet::RakNetGUID,gamePlayer*> playerList; //List of players on the game server
	//Packet handlers
	void acceptPlayer(RakNet::Packet *packet); //Accept a new player's connection
	short playerUIDcount;
	double			lastTick; //Timestamp of last simulation tick
	double			lastSnapshot; //Timestamp of last snapshot
};

#endif