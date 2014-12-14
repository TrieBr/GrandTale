#include "GTLoginServerClient.h"
#include "GTGameServer.h"
#include "abstractServer.h"
#include <iostream>

GTLoginServerClient::GTLoginServerClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface) : abstractClient(guid,parentServer,clientInterface) {
	std::cout << "[" << this->parentServer().getIdentifier() << "]" << "Connected to login server." << std::endl;

	//Send our data
	RakNet::BitStream data; //The bitstrea,
	data.Write<RakNet::MessageID>(worldLoginInterfacePackets::WORLD_SEND_DATA);
	data.Write<RakNet::RakString>(RakNet::RakString(this->parentServer().getIdentifier().c_str())); //Server Name
	data.Write<RakNet::RakString>(RakNet::RakString(((GTGameServer*)&this->parentServer())->getBroadcastIP().c_str())); //Broadcast IP
	data.Write<short>(((GTGameServer*)&this->parentServer())->getListeningPort()); //Broadcast Port
	sendPacket(data);
}