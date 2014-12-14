// ----------------------------------------------------------------------
// loginPlayer.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------


#include "loginPlayer.h"
#include "loginServer.h"
#include <iostream>
loginPlayer::loginPlayer() { //Constructor
	authenticated = false; //Not authenticated
	userID = 0;
	for (int i=0; i<CHARACTERSLOTS; i++) {
		characterSlots[i].inUse = false;
	}
	selectedSlot = -1; //No slot selected
}

void loginPlayer::handlePacket(RakNet::Packet *packet) { //Handle a packet
		unsigned char packetID = loginServer::GetPacketIdentifier(packet); //Get the packet ID
			switch (packetID) {
			case AUTHENTICATE_REQUEST: authenticate(packet); break; //Authenticate the user
			case GAMESERVERLIST_REQUEST: sendGameServerList(packet); break; //Send the server list.
			case CHARACTERLIST_REQUEST: sendCharacterList(packet); break;
			case CHARACTERCREATE: createCharacter(packet); break;
			case GAMESERVERLIST_SELECT: selectWorld(packet); break;
			case CHARACTERDELETE:	deleteCharacter(packet); break; //Delete a character
			case CHARACTERSELECT: selectCharacter(packet); break; //Select a character/connect to game server
			case GAMESERVER_CONNECTREQUEST: requestGameServerConnection(packet); break; //Request gameserver information
			default: { //Login server did not handle the packet, so pass it on to it's player object to handle
					std::cout << "Message was unhandled: " << (int)packetID << std::endl;
				}

			}
}



void loginPlayer::authenticate(RakNet::Packet *packet) { //Authenticate the user
	RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
					RakNet::RakString		username;
					RakNet::RakString		password;
					data.Read<RakNet::RakString>(username);
					data.Read<RakNet::RakString>(password);
					int authenticationResult = this->parentServer->mysqlAccounts->verifyCredentials(username.C_String(),password.C_String());
					if (authenticationResult>0) { //Successfull authentication
						authenticated = true; //We are now authenticated.
						userID = authenticationResult; //Set our user ID

						RakNet::BitStream data; //The bitstrea,
						data.Write<RakNet::MessageID>(AUTHENTICATE_RESULT);
						data.Write<bool>(true); //Unable to authenticate
						this->parentServer->sendMessage(&data,guid);
					}else if (authenticationResult==INVALID_PASSWORD || authenticationResult==UNKNOWN_USERNAME) { //Invalid credentials
						RakNet::BitStream data; //The bitstrea,
						data.Write<RakNet::MessageID>(AUTHENTICATE_RESULT);
						data.Write<bool>(false); //Unable to authenticate
						this->parentServer->sendMessage(&data,guid);

					}
}

void loginPlayer::sendGameServerList(RakNet::Packet *packet) { //Sebd game server list
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(GAMESERVERLIST_REQUEST); //Message ID
	data.Write<unsigned char>(this->parentServer->gameServerManager.peerList.Size()); //Number of servers.
	for (unsigned int i=0; i<this->parentServer->gameServerManager.peerList.Size(); i++) {
		data.Write<RakNet::RakString>(this->parentServer->gameServerManager.peerList[i]->serverName); //The server name
		data.Write<unsigned char>(i); //The ID of the server (currently just the number in the map...) TODO: Possibly make a safer way to identify game servers.
	}
	this->parentServer->sendMessage(&data,guid);

}

void loginPlayer::sendCharacterList(RakNet::Packet *packet) { //Send character list
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(CHARACTERLIST_REQUEST); //Message ID

	data.Write<unsigned char>(CHARACTERSLOTS); //Number of characters
	for (int i=0; i<CHARACTERSLOTS; i++) {
		data.Write<bool>(characterSlots[i].inUse);
		if (characterSlots[i].inUse) {
		characterSlots[i].cData.writeCharacterData(data);
		}
	}

	this->parentServer->sendMessage(&data,guid);
}

void loginPlayer::createCharacter(RakNet::Packet *packet) { //Add a new character to the account
	RakNet::BitStream dataRead(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
	RakNet::RakString		characterName;
	character::characterData customization;
	dataRead.Read<RakNet::RakString>(characterName);
	customization.charName = characterName;
	customization.readCharacterCustomization(dataRead);
	//TODO: See if username already exists..
	int charID = this->parentServer->mysqlGameData->addCharacter(customization, characterName.C_String(), this->userID);
	for (int i=0; i<CHARACTERSLOTS; i++) {
		if (characterSlots[i].inUse==false) {
		characterSlots[i].cData = customization;
		characterSlots[i].inUse = true;
		characterSlots[i].UID = charID;
		break;
		}
	}
	sendCharacterList(NULL);
}

void loginPlayer::selectWorld(RakNet::Packet *packet) { //Select a world (game server)
	RakNet::BitStream dataRead(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);

	unsigned short serverInd;
	dataRead.Read<unsigned short>(serverInd); //Read the ID that was selected
	selectedServer = serverInd;
	gameServerClient* selectedServer = this->parentServer->gameServerManager.peerList[serverInd]; //Get the server handle for the server they selected

	log("Player Selected Server: %i [%s] \n", serverInd,selectedServer->serverName.C_String());

	//Populate character slots
	std::vector<int> charList =  this->parentServer->mysqlGameData->getCharaceterIDs(this->userID); //Get all the character ID's
	for (int i=0; i<CHARACTERSLOTS && i<charList.size(); i++) {
		characterSlots[i].cData = this->parentServer->mysqlGameData->getCharacterData(charList[i]);
		characterSlots[i].inUse = true;
		characterSlots[i].UID = charList[i];
	}

	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(GAMESERVERLIST_SELECT); //Message ID
	this->parentServer->sendMessage(&data,guid); //Reply and tell the client it can safely move onto the character select
}

void loginPlayer::deleteCharacter(RakNet::Packet *packet) { //Delete a character
	RakNet::BitStream dataRead(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);

	unsigned short slotID;
	dataRead.Read<unsigned short>(slotID); //Read the ID that was selected

	log("Player Deleted character in slot: %i \n", slotID);
	characterSlots[slotID].inUse = false; //No longer in use..

	int deleteResult = this->parentServer->mysqlGameData->removeCharacter(characterSlots[slotID].UID); //Delete the player

	if (deleteResult>0) {
		RakNet::BitStream data; //The bitstream
		data.Write<RakNet::MessageID>(CHARACTERDELETE); //Message ID
		data.Write<unsigned short>(slotID); //Tell the client to delete the character 
		this->parentServer->sendMessage(&data,guid); //Reply and tell the client it can safely move onto the character select
	}


}

void loginPlayer::selectCharacter(RakNet::Packet *packet) { //select a character
	RakNet::BitStream dataRead(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
	dataRead.Read<char>(selectedSlot); //Read the ID that was selected

	log("Player selected character in slot: %i \n", selectedSlot);
}

void loginPlayer::requestGameServerConnection(RakNet::Packet *packet) { //request game server information
	log("Player requesting game server connection info..\n");
	unsigned char ticketBytes[8];
	ticketBytes[0] = rand() % 4294967295;
	ticketBytes[1] = rand() % 4294967295;
	ticketBytes[2] = rand() % 4294967295;
	ticketBytes[3] = rand() % 4294967295;
	ticketBytes[4] = rand() % 4294967295;
	ticketBytes[5] = rand() % 4294967295;
	ticketBytes[6] = rand() % 4294967295;
	ticketBytes[7] = rand() % 4294967295;
	log("Generated unique ticket: %02X %02X %02X %02X %02X %02X %02X %02X\n",ticketBytes[0],ticketBytes[1],ticketBytes[2],ticketBytes[3],ticketBytes[4],ticketBytes[5],ticketBytes[6],ticketBytes[7]);

	transferData tData;
	tData.characterSelected = this->characterSlots[this->selectedSlot].UID;

	this->parentServer->gameServerManager.peerList[selectedServer]->prepareTicket(ticketBytes,tData);

	RakNet::BitStream data; //The bitstream
		data.Write<RakNet::MessageID>(GAMESERVER_CONNECTREQUEST); //Message ID
		for(char i=0; i<8; i++) {
			data.Write<unsigned char>(ticketBytes[i]); //TWrite byte of the ticket
		}
		data.Write<RakNet::RakString>(this->parentServer->gameServerManager.peerList[selectedServer]->broadcastIP); //Send the IP to connect to
		data.Write<short>(this->parentServer->gameServerManager.peerList[selectedServer]->broadcastPort); //Send the port to connect to
		this->parentServer->sendMessage(&data,guid); //Reply and tell the client it can safely move onto the character select

	
}