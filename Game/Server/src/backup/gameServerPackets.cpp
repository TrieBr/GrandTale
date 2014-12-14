// ----------------------------------------------------------------------
// gameServerPackets.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "gameServer.h"
void gameServer::acceptPlayer(RakNet::Packet *packet) { //Accept a new player's connection
	std::cout<<"[Game Server] New player connected..."<<std::endl;
	gamePlayer* newPlayer = new gamePlayer(); //Create a new login player
	newPlayer->parentServer = this; //Set the new players parent to this server instance
	newPlayer->guid = packet->guid; //Set the new player's guid
	playerList.SetNew(packet->guid,newPlayer); //Add the player to the map
}
