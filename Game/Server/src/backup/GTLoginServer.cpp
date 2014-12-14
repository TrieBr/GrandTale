#include "GTLoginServer.h"
#include "packetOpCodes.h"

#include "clientAuthenticate.h"
#include "characterCreate.h"
#include "characterDelete.h"
#include "characterSelect.h"
#include "requestCharacterList.h"
#include "requestWorldList.h"
#include "worldSelect.h"
#include "worldConnect.h"
#include "gameWorldSendData.h"

void GTLoginServer::initialize() {
	this->::abstractServer::initialize();
	std::cout << "GTLoginServer initialized." << std::endl;

	this->gameWorldAcceptor.start(this,1338); //Listen for game worlds on port1338
	this->gameWorldAcceptor.registerPacketProcessor(worldLoginInterfacePackets::WORLD_SEND_DATA, new  gameWorldSendData());
	
	this->publicAcceptor.start(this, 1337); //Create listener on Port 1337 (accepts public people wanting to login)
	this->publicAcceptor.registerPacketProcessor(loginPackets::CLIENT_AUTHENTICATE, new clientAuthenticate());
	this->publicAcceptor.registerPacketProcessor(loginPackets::REQUEST_WORLDLIST, new requestWorldList());
	this->publicAcceptor.registerPacketProcessor(loginPackets::REQUEST_CHARACTERLIST, new requestCharacterList());
	this->publicAcceptor.registerPacketProcessor(loginPackets::CHARACTER_CREATE, new characterCreate());
	this->publicAcceptor.registerPacketProcessor(loginPackets::WORLDLIST_SELECT, new worldSelect());
	this->publicAcceptor.registerPacketProcessor(loginPackets::CHARACTER_DELETE, new characterDelete());
	this->publicAcceptor.registerPacketProcessor(loginPackets::CHARACTER_SELECT, new characterSelect());
	this->publicAcceptor.registerPacketProcessor(loginPackets::GAMEWORLD_CONNECT, new worldConnect());

}

void GTLoginServer::handle(){
	this->publicAcceptor.handle();
	this->gameWorldAcceptor.handle();
	this->::abstractServer::handle();
}

void GTLoginServer::shutdown() {
	this->::abstractServer::shutdown();
}

