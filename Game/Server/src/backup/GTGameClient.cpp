#include "GTGameClient.h"
#include "packetOpCodes.h"
#include "gameMap.h"
#include <iostream>

GTGameClient::GTGameClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface) : abstractClient(guid,parentServer,clientInterface) {
	currentMap = NULL;
}

void GTGameClient::mapGoto(gameMap *map) { //Transfer the player to a new map
	if (currentMap!=NULL) {
		currentMap->removeCharacter(this);
	}
	currentMap = map;
	if (currentMap!=NULL) {
		map->addCharacter(this); //Add us to the new map
		RakNet::BitStream data; //The bitstream
		data.Write<RakNet::MessageID>(gamePackets::MAP_GOTO); //Message ID
		data.Write<unsigned short>(map->getMapDataID()); //Send the unique ID
		sendPacket(data);
		currentMap->sendMapObjects(this); //Send all the existing map data to this client
	}else{
		std::cout << "GTGameclient::mapGoto() called with NULL map." << std::endl;
	}
}

void GTGameClient::sendInitialData() { //Send player initial data when logging in..
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::INITIAL_INFOLOAD); //Message ID
	this->cData.writeCharacterData(data); //Write the character Data
	sendPacket(data);
}

void GTGameClient::sendPlayerData(GTGameClient* dest) {
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::PLAYER_CHARACTER_DATA); //Message ID
	data.Write<unsigned short>(this->UID); //Send the players Unique ID
	cData.writeCharacterData(data); //Write the player's data
	dest->sendPacket(data);
}