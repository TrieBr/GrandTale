#include "GTGameServer.h"
#include "packetOpCodes.h"
#include "prepareTransferTicket.h"
#include "verifyTicket.h"
#include "playerPositionUpdate.h"
#include "playerChatMessage.h"
#include "playerDisconnect.h"
#include "playerItemContainerOperation.h"
#include "playerEquipOperations.h"
#include "playerSkillOperations.h"
#include "itemCustomizationFetch.h"
#include "statCommand.h"
#include <allegro5/allegro.h>

GTGameServer::GTGameServer(std::string serverName, short listenPort, std::string broadcastIP) {
	this->::abstractServer::setIdentifier(serverName);
	this->listeningPort = listenPort;
	this->broadcastIP = broadcastIP;
	targetFramerate = 60;
	FPS = 0;
	deltaTime = 0;
	slowFPS = al_get_time();
	lastFrameTime = al_get_time();
}

void GTGameServer::initialize() {
	this->::abstractServer::initialize();
	queries::downloadItems(gameDB,&iManager); //Download all of the game's item data
	mobFactory::InitializeMobs();
	mobNPCFactory::InitializeMobs();
	std::cout << "GTGameServer initialized." << std::endl;

	//_mHandler.addMap(gameMap::loadMapFromID(0, e_default));

	this->loginServerConnection.connect(this,"localhost", 1338); //Connect to the login server
	this->loginServerConnection.registerPacketProcessor(worldLoginInterfacePackets::PREPARE_TICKET, new prepareTransferTicket());

	this->publicAcceptor.start(this, listeningPort); //Create listener on Port 1337 (accepts public people wanting to login)
	this->publicAcceptor.registerPacketProcessor(gamePackets::TICKET_VERIFY, new verifyTicket());
	this->publicAcceptor.registerPacketProcessor(gamePackets::PLAYER_POSITIONUPDATE, new playerPositionUpdate());
	this->publicAcceptor.registerPacketProcessor(gamePackets::PLAYER_CHAT, new playerChatMessage());
	this->publicAcceptor.registerPacketProcessor(ID_DISCONNECTION_NOTIFICATION, new playerDisconnect());
	this->publicAcceptor.registerPacketProcessor(ID_CONNECTION_LOST, new playerDisconnect());
	this->publicAcceptor.registerPacketProcessor(gamePackets::ITEM_CONTAINER_ACTION,new playerItemContainerOperation());
	this->publicAcceptor.registerPacketProcessor(gamePackets::EQUIPMENT_ACTION,new playerEquipOperations());
	this->publicAcceptor.registerPacketProcessor(gamePackets::SKILLHANDLER_ACTION,new playerSkillOperations());
	this->publicAcceptor.registerPacketProcessor(gamePackets::ITEM_CUSTOMIZATION_FETCH,new itemCustomizationFetch());
	this->publicAcceptor.registerPacketProcessor(gamePackets::STAT_COMMAND,new statCommand());

	
}

void GTGameServer::handle(){

	
	FPS = 1/(al_get_time()-lastFrameTime);
	if (al_get_time()-slowFPS>1) {
		std::cout << "Simulation FPS: " << FPS << std::endl;
		slowFPS = al_get_time();
	}

	deltaTime = double(targetFramerate/FPS);
	lastFrameTime = al_get_time();
	// this->_mHandler.updateMaps(deltaTime);


	static double accumulatedTime = 0;
				accumulatedTime += deltaTime;
				const double fixedFrameTime = 1/targetFramerate;
				while( accumulatedTime > fixedFrameTime )
				{
				  accumulatedTime -= fixedFrameTime;
				  this->_mHandler.updateMaps(fixedFrameTime);
				}
				
				
	
	this->publicAcceptor.handle();
	this->loginServerConnection.handle();
	this->::abstractServer::handle();
	al_rest(0.001);
}

void GTGameServer::shutdown() {
	this->::abstractServer::shutdown();
}

