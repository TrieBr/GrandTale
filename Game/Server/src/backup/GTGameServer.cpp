#include "GTGameServer.h"
#include "packetOpCodes.h"
#include "prepareTransferTicket.h"
#include "verifyTicket.h"

GTGameServer::GTGameServer(std::string serverName, short listenPort, std::string broadcastIP) {
	this->::abstractServer::setIdentifier(serverName);
	this->listeningPort = listenPort;
	this->broadcastIP = broadcastIP;
}

void GTGameServer::initialize() {
	this->::abstractServer::initialize();
	std::cout << "GTGameServer initialized." << std::endl;

	_mHandler.addMap(gameMap::loadMapFromID(0, e_default));

	this->loginServerConnection.connect(this,"localhost", 1338); //Connect to the login server
	this->loginServerConnection.registerPacketProcessor(worldLoginInterfacePackets::PREPARE_TICKET, new prepareTransferTicket());

	this->publicAcceptor.start(this, listeningPort); //Create listener on Port 1337 (accepts public people wanting to login)
	this->publicAcceptor.registerPacketProcessor(gamePackets::TICKET_VERIFY, new verifyTicket());
}

void GTGameServer::handle(){
	this->publicAcceptor.handle();
	this->loginServerConnection.handle();
	this->::abstractServer::handle();
}

void GTGameServer::shutdown() {
	this->::abstractServer::shutdown();
}

