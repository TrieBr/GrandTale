#include "abstractClient.h"
#include "abstractServer.h"
abstractClient::abstractClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface) {
	this->guid = guid;
	this->_parentServer = parentServer;
	this->_clientInterface = clientInterface;
}

abstractServer& abstractClient::parentServer() {
	return *_parentServer;
}

void abstractClient::sendPacket(RakNet::BitStream &data, PacketPriority priority, PacketReliability reliability, int orderingChannel) {
	this->clientInterface().Send(&data,priority,reliability,orderingChannel,this->guid,false);
}