#include "gamePlayer.h"
#include "gameServer.h"
#include "map.h"

void gamePlayer::sendInitialInfo() { //Send the player all their neccessary info to play the game
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(SEND_INITIAL_INFO); //Message ID
	this->pData.character.writeCharacterData(data); //Write the character Data
	this->parentServer->clientInterface->Send(&data,LOW_PRIORITY,RELIABLE,0,this->guid,false);

}


void gamePlayer::gotoMap(map *newMap) {
	newMap->addPlayer(this); //Add this player to the specified map
	currentMap = newMap; //Set the player's current map
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(MAP_GOTO); //Message ID
	data.Write<unsigned short>(newMap->uniqueID); //Send the unique ID
	this->parentServer->clientInterface->Send(&data,LOW_PRIORITY,RELIABLE,0,this->guid,false);
	newMap->sendMapEntities(this); //Send all the players in the map to the client
	newMap->broadcastPlayerData(this);
	
	this->pController->setMapData(newMap->mData);
}