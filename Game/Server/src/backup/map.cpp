

#include "map.h"
#include "mapReader.h"



void map::addPlayer(gamePlayer *newPlayer) { //Adds a new player to the map
	this->playerList.push_back(newPlayer); //Add the player to the map player list
}


void map::sendMapEntities(gamePlayer* client) { //Sends map information (players, mobs, etc) to the specified client
	sendPlayerList(client); //Send the list of other players in the map
}

void map::sendPlayerList(gamePlayer* client) { //Sends all the players in the map to the client
	for(unsigned int i=0; i<this->playerList.size(); i++) {
		if (this->playerList[i]!=client) {
			sendPlayerData(this->playerList[i], client);
		}
	}
}

void map::sendPlayerData(gamePlayer* player, gamePlayer* destination) { //Sends info on a player in the map
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(MAP_PLAYERDATA_INITIAL); //Message ID
	data.Write<unsigned short>(player->UID); //Send the players Unique ID
	player->pData.character.writeCharacterData(data); //Write the player's data
	destination->parentServer->clientInterface->Send(&data,LOW_PRIORITY,RELIABLE,0,destination->guid,false);
}

void map::broadcastPlayerData(gamePlayer* player) { //Broadcasts a player to the whole map
	for(unsigned int i=0; i<this->playerList.size(); i++) { //For each player in the map
		if (this->playerList[i]!=player) {
			sendPlayerData(player, this->playerList[i]);
		}
	}
}

void map::broadcastPacket(RakNet::BitStream &data, gamePlayer* notInclude) { //Broadcast a packet to everyone in the map
	for(unsigned int i=0; i<this->playerList.size(); i++) { //For each player in the map
		if (this->playerList[i]!=notInclude) {
			this->playerList[i]->parentServer->clientInterface->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,this->playerList[i]->guid,false);
		}
	}
}

void map::loadMapData() { //Loads the map collision data, etc.
	mData = new mapData();

	std::stringstream * mapFormat = new std::stringstream();
	(*mapFormat) << ":map:" << this->uniqueID << ".map";
	ALLEGRO_FILE* mapFileData = gameEngine::resources::data.openSubFile(mapFormat->str().c_str(),false);
	mapReader reader(mData, SKIPBACKGROUNDS | SKIPTILES);
	reader.readData(mapFileData); //Read the map data
	al_fclose(mapFileData);

	return;
}

void map::simulate(double timeStep) { //Simulate the map
	for (unsigned int i=0; i<this->playerList.size(); i++) { //For each player in the map, we want to step their physics..
		this->playerList[i]->pController->step(timeStep); //Step the physics for the player
		cout << this->playerList[i]->pController->getState().x << "," << this->playerList[i]->pController->getState().y << std::endl;
	}
	
}