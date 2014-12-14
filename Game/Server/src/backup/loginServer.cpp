
#include "loginServer.h"
#include <iostream>
void loginServer::initialize(unsigned short listenPort, unsigned int gameServerPort) { //Initialize the server
	 clientInterface = RakNet::RakPeerInterface::GetInstance(); //Get a new peer interface
	 RakNet::StartupResult sRes = clientInterface->Startup(255,new RakNet::SocketDescriptor(listenPort,0),1); //Startup the interface
	 if (sRes==RakNet::RAKNET_STARTED) { //If started sucessfully
		 clientInterface->SetMaximumIncomingConnections(255); //Set the max number of connections
	 }
	 this->gameServerManager.initialize(gameServerPort); //Initialize the gameServer manager
	
	 mysqlAccounts = new accountMysql(); //Create the mysql connection handler
	 mysqlAccounts->connect("triebr.com","triebrco_accounts","triebrco_GTSERVE","e{@IFo46@J&1");
	mysqlGameData = new  gameDataMysql();
	mysqlGameData->connect("triebr.com","triebrco_GTdata","triebrco_GTSERVE","e{@IFo46@J&1");
	
	 std::cout << "[Login Server] " << "Started." << std::endl;
}

void loginServer::shutdown() { //Shuts down the server
	clientInterface->Shutdown(500); //Shutdown the client interface 
	RakNet::RakPeerInterface::DestroyInstance(clientInterface); //Destroy the client interface
	this->gameServerManager.shutdown(); //Cleanup the game server manager
	delete mysqlAccounts; //Delete the mysql
	delete mysqlGameData;
}

bool loginServer::handle() { //one "step" that handles messages. Should be called once per "Frame".
	RakNet::Packet *packet = clientInterface->Receive(); //Attempt to receive a packet
	if (packet!=NULL){ //If a packet was received
		unsigned char packetID = GetPacketIdentifier(packet); //Get the packet ID
			switch (packetID) {
				case ID_NEW_INCOMING_CONNECTION: acceptPlayer(packet); break;
				default: playerList[playerList.GetIndexAtKey(packet->guid)]->handlePacket(packet); //Handle the packet using the player's object
			}
		clientInterface->DeallocatePacket(packet); //Deallocate the packet
	}
	return this->gameServerManager.handle(); //Handle the game servers
}

uint32_t loginServer::sendMessage(RakNet::BitStream *bitStream,RakNet::AddressOrGUID systemIdentifier, bool broadcast, PacketPriority priority, PacketReliability reliability, int orderingChannel) {
	return this->clientInterface->Send(bitStream,priority,reliability,orderingChannel,systemIdentifier,broadcast);
}

unsigned char loginServer::GetPacketIdentifier(RakNet::Packet *p) {
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	else
	return (unsigned char) p->data[0];
}