// ----------------------------------------------------------------------
// gameServer.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "gameServer.h"
#include "map.h"
#include <iostream>
#include <allegro5/allegro.h>
void gameServer::initialize(unsigned short listenPort, std::string loginServerHost, unsigned short loginServerPort, std::string serverName) { //Initialize the server
	 clientInterface = RakNet::RakPeerInterface::GetInstance(); //Get a new peer interface
	 RakNet::StartupResult sRes = clientInterface->Startup(255,new RakNet::SocketDescriptor(listenPort,0),1); //Startup the interface
	 if (sRes==RakNet::RAKNET_STARTED) { //If started sucessfully
		 clientInterface->SetMaximumIncomingConnections(255); //Set the max number of connections
		 //clientInterface->ApplyNetworkSimulator(0.5,200,200);
	 }

	 this->loginServerConnection.initialize(loginServerHost, loginServerPort, this); //Connect to the login server.
	 mysqlAccounts = new accountMysql(); //Create the mysql connection handler
	 mysqlAccounts->connect("triebr.com","triebrco_accounts","triebrco_GTSERVE","e{@IFo46@J&1");

	 mysqlGameData = new gameDataMysql();
	 mysqlGameData->connect("triebr.com","triebrco_GTdata","triebrco_GTSERVE","e{@IFo46@J&1");

	 this->serverName = serverName;
	 this->broadcastIP = "gtserver.zapto.org";
	 this->broadcastPort = listenPort;
	 std::cout << "[Game Server: " << serverName << "] " << "Started." << std::endl;

	 playerUIDcount = 0; //Start the unique ID at 0
	 lastTick = 0; //Last tick is 0
	 lastSnapshot = 0; //Last snapshot is 0
	 loadMapData(); //Load map data
}

void gameServer::shutdown() { //Shuts down the server
	this->loginServerConnection.shutdown(); //Cleanup the connection with login server
	clientInterface->Shutdown(500); //Shutdown the client interface 
	RakNet::RakPeerInterface::DestroyInstance(clientInterface); //Destroy the client interface
	delete mysqlAccounts; //Delete the mysql
}

bool gameServer::handle() { //one "step" that handles messages. Should be called once per "Frame".
	RakNet::Packet *packet = clientInterface->Receive(); //Attempt to receive a packet
	if (packet!=NULL){ //If a packet was received
		unsigned char packetID = GetPacketIdentifier(packet); //Get the packet ID
			switch (packetID) {
				case ID_NEW_INCOMING_CONNECTION: acceptPlayer(packet); break;
				default: playerList[playerList.GetIndexAtKey(packet->guid)]->handlePacket(packet); //Handle the packet using the player's object
			}
		clientInterface->DeallocatePacket(packet); //Deallocate the packet
	}
	if ((al_get_time()-lastTick)>=(1/ticksPerSecond)) {
		for (unsigned int i = 0; i< this->mapList.size(); i++) { //For each map..
			this->mapList[i]->simulate((1/ticksPerSecond)); //Simulate the map
		}
		lastTick = al_get_time();
	}
	return this->loginServerConnection.handle(); //Handle packets with login Server.
}


uint32_t gameServer::sendMessage(RakNet::BitStream *bitStream,RakNet::AddressOrGUID systemIdentifier, bool broadcast, PacketPriority priority, PacketReliability reliability, int orderingChannel) {
	return this->clientInterface->Send(bitStream,priority,reliability,orderingChannel,systemIdentifier,broadcast);
}

unsigned char gameServer::GetPacketIdentifier(RakNet::Packet *p) {
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	else
	return (unsigned char) p->data[0];
}

void gameServer::loadMapData() { //Load all of the map data
	map* newMap = new map();
	newMap->uniqueID = 0;
	newMap->loadMapData(); //Load the map tiles/collision lines and stuff
	this->mapList.push_back(newMap);
}

map* gameServer::getMap(unsigned short ind) { //Get map from index
	return this->mapList[ind];
}

short	gameServer::generatePlayerUID() { //Generates a unique ID for a player
	return playerUIDcount++;
}