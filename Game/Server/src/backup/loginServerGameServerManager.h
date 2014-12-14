// ----------------------------------------------------------------------
// loginServerGameServerManager.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	This is used for controling all the game servers connected to a login server.
*/
// ------------------------------------------------------------------------

#include <RakPeerInterface.h>
#include <DS_Map.h>
#include <RakString.h>
#include "gameServerLoginServer_InterfaceData.h"

#ifndef _H_LOGINSERVERGAMESERVERMANAGER_
#define _H_LOGINSERVERGAMESERVERMANAGER_
class loginServerGameServerManager;
class gameServerClient { //A handle for a game server that is connected to the login server
public:
	loginServerGameServerManager* parentManager;
	void handlePacket(RakNet::Packet *packet);
	RakNet::RakNetGUID guid;
	RakNet::RakString broadcastIP;
	short broadcastPort;
	//Server properties
	RakNet::RakString serverName;

	//Packets
	void receiveServerInfo(RakNet::Packet *packet); //Receive property data from the connected game server

	//Outgoing
	void prepareTicket(unsigned char ticket[8],transferData &extraData);
};


class loginServerGameServerManager
{
public:
	void initialize(unsigned short portListen); //Initialize and begin listening on the specified port.
	bool handle(); //Handle packets
	void shutdown(); //Cleanup
	DataStructures::Map<RakNet::RakNetGUID,gameServerClient*> peerList; //List of peers/clients (a.k.a. game Servers) connected 
	RakNet::RakPeerInterface* gameServerInterface; //The main interface for the connected game Servers
	
};

#endif