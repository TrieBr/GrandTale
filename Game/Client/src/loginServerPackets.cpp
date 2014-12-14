// ----------------------------------------------------------------------
// loginServerPackets.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	Connection with the login server. This handles things like authentication, server selection, character selection/creation and then eventually transferring to the game world.
*/
// ------------------------------------------------------------------------

#include "loginServer.h"
#include <iostream>
#include "worldMainMenu.h"
#include "gameServer.h"

namespace networking {


		void loginServer::authenticateResult(RakNet::Packet *packet) { //Received authentication results from server
			RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
			bool authenticationStatus;
			data.Read<bool>(authenticationStatus);
			if (authenticationStatus==false) { //Invalid information, so we display an error
				reinterpret_cast<worlds::worldMainMenu*>(loginServer::parentWorld)->showError("Invalid credentials.");
			}else{//Login was a success
				reinterpret_cast<worlds::worldMainMenu*>(loginServer::parentWorld)->loginToServerSelect();
			}

		}


		void loginServer::serverListResult(RakNet::Packet *packet) { //Received the server list.
			RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
			unsigned char serverCount; //Number of servers
			data.Read<unsigned char>(serverCount); //Read number of servers
			for (unsigned char i=0; i<serverCount; i++) { //For each server
				RakNet::RakString		serverName; //The name of the server
				unsigned char			serverID; //The ID of the server
				data.Read<RakNet::RakString>(serverName); //Read the name of the server
				data.Read<unsigned char>(serverID); //Read the ID of the server
				reinterpret_cast<worlds::worldMainMenu*>(loginServer::parentWorld)->serverSelect->addServer(serverName,serverID); //Add the server to the list
			}
		}
		

		void  loginServer::characterListResult(RakNet::Packet *packet) { //Received character List
			RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
			unsigned char		characterCount; //Number of characters
			data.Read<unsigned char>(characterCount); //Read the number of characters
			for (unsigned char i=0; i<characterCount; i++) { //For each character
				bool exists;
				data.Read<bool>(exists);
				if (exists) {
					character::characterData* cData = new character::characterData; //Create a new character
					cData->readCharacterData(data); //Read the character data
					reinterpret_cast<worlds::worldMainMenu*>(loginServer::parentWorld)->characterSelect->setSlot(i,cData); //Add the character to the character creation panel.
					delete cData;
				}
				
			}
		}

		void loginServer::gameServerSelectAck(RakNet::Packet *packet) { //Server has acknowledged that we selected a game world
			reinterpret_cast<worlds::worldMainMenu*>(loginServer::parentWorld)->serverSelectToCharSelect(); //Move to the character select screen
		}

		void loginServer::characterRemove(RakNet::Packet *packet) { //Remove a character that is on the character select screen
			RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
			unsigned short slotID;
			data.Read<unsigned short>(slotID); //Read the ID that was selected

			reinterpret_cast<worlds::worldMainMenu*>(loginServer::parentWorld)->characterSelect->setSlot(slotID,NULL); //Add the character to the character creation panel.
		}

		void loginServer::receiveGameServerConnectionInfo(RakNet::Packet *packet) {//Receive data for connecting to game server
			RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
			unsigned char ticket[8];
			for(char i=0; i<8; i++) {
				data.Read<unsigned char>(ticket[i]); //Read byte of the ticket
			}
			RakNet::RakString connectIP;
			short connectPort;
			data.Read<RakNet::RakString>(connectIP); //Read game server IP
			gameEngine::logger::logStream << "Connecting to server: " << connectIP.C_String() << endl;
			data.Read<short>(connectPort); //Read game serverPort
			//Now we need to try and connect to the game server
			networking::gameServer::parentWorld = networking::loginServer::parentWorld; //Set the parent world to the main menu world
			for(char i=0; i<8; i++) {
				networking::gameServer::ticket[i] = ticket[i]; //Set the ticket data
			}
			networking::gameServer::connect(connectIP.C_String(),connectPort); //Connect
		}


}