// ----------------------------------------------------------------------
// loginServerPackets.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	Various functions for handling packets for the login server
*/
// ------------------------------------------------------------------------


#include "loginServer.h"


void loginServer::acceptPlayer(RakNet::Packet *packet) { //Accept a new player's connection
	std::cout<< "[Login Server] " << "New player connected..."<<std::endl;
	loginPlayer* newPlayer = new loginPlayer(); //Create a new login player
	newPlayer->parentServer = this; //Set the new players parent to this server instance
	newPlayer->guid = packet->guid; //Set the new player's guid
	playerList.SetNew(packet->guid,newPlayer); //Add the player to the map
}
