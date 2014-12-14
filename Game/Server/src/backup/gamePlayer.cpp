// ----------------------------------------------------------------------
// loginPlayer.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------


#include "gamePlayer.h"
#include "gameServer.h"
#include "map.h"
#include <iostream>
#include "log.h"
gamePlayer::gamePlayer() { //Constructor
	authenticated = false; //Not authenticated
	userID = 0;
	currentMap = NULL;
	pController = new physicsController(physicsController::getDefaultPlayerPhysics(),NULL);
	pController->setDimensions((62/2),64,(62/2),26);
}

void gamePlayer::handlePacket(RakNet::Packet *packet) { //Handle a packet
		unsigned char packetID = gameServer::GetPacketIdentifier(packet); //Get the packet ID
			switch (packetID) {
			case AUTHENTICATETICKET_REQUEST: authenticateTicket(packet); break; //verify/authenticate ticket
			case PLAYER_MOVEMENTACTION: movementActionUpdate(packet); break; //Player pressed a button for movement
			default: { //Login server did not handle the packet, so pass it on to it's player object to handle
					std::cout << "Message was unhandled: " << (int)packetID << std::endl;
				}

			}
}



void gamePlayer::authenticateTicket(RakNet::Packet *packet) { //Authenticate the user
	RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);

	unsigned char ticket[8];
	for (char i =0; i<8; i++) { //For each of the 8 bytes
		data.Read<unsigned char>(ticket[i]);
	}

	for (unsigned int i=0; i<this->parentServer->loginServerConnection.transferClientList.size(); i++) { //For each client waiting for transfer
		bool match = true; //Is this waiting client a match for the requested ticket?
		for (char t =0; t<8; t++) { //For each of the 8 bytes
			if (ticket[t]!=this->parentServer->loginServerConnection.transferClientList[i]->ticket[t]) {
				match = false;
				break;
			}
		}

		if (match) { //Waiting client matches
			log ("[Game Server] Client has matched ticket sucessfully.\n");
			UID = this->parentServer->generatePlayerUID(); //Generate a unique ID from the server that is managing us
			this->pData.character = this->parentServer->mysqlGameData->getCharacterData(this->parentServer->loginServerConnection.transferClientList[i]->extraData.characterSelected);
			this->sendInitialInfo(); //Send player data
			this->gotoMap(this->parentServer->getMap(0)); //Goto a map
			return;
			break;
		}
	}

	log("[Game Server] A Client has tried verifying an unknown ticket. \n");
	//Tell the client their ticket is invalid..
	RakNet::BitStream dataW; //The bitstream
	dataW.Write<RakNet::MessageID>(AUTHENTICATETICKET_REQUEST); //Message ID
	dataW.Write<unsigned short>(1); //Invalid ticket
	this->parentServer->sendMessage(&dataW,guid); //Reply and tell the client it can safely move onto the character select
}

void gamePlayer::movementActionUpdate(RakNet::Packet *packet) { //Update movement ebcause an action was executed
	//TODO : a bunch of shit here.. This is simply rebounding the packet to all the other clients
	RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);

	RakNet::BitStream newData;

	newData.Write<RakNet::MessageID>(PLAYER_MOVEMENTACTION); //Message ID
	newData.Write<short>(this->UID); //Write our UID
	newData.Write(data); //Write the data we received, because we are simple rebounding it
	this->currentMap->broadcastPacket(newData,this);

}

