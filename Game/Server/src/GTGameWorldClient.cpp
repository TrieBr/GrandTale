#include "GTGameWorldClient.h"
#include "abstractServer.h"
#include <iostream>

GTGameWorldClient::GTGameWorldClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface) : abstractClient(guid,parentServer,clientInterface) {
	std::cout << "[" << this->parentServer().getIdentifier() << "]" << "Game World connected:" << this->name.C_String() << std::endl;
}