// ----------------------------------------------------------------------
// loginServerGameServerManager.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	This is used for controling all the game servers connected to a login server.
*/
// ------------------------------------------------------------------------

#include "loginServerGameServerManager.h"
#include "loginServer.h"

	void loginServerGameServerManager::initialize(unsigned short portListen) { //Initialize and begin listening on the specified port.
		RakNet::StartupResult			sRes;
		this->gameServerInterface = RakNet::RakPeerInterface::GetInstance(); //Get a new peer interface
		sRes =  this->gameServerInterface->Startup(255,new RakNet::SocketDescriptor(portListen,0),1); //Startup the interface
		if (sRes==RakNet::RAKNET_STARTED) { //If started sucessfully
		 this->gameServerInterface->SetMaximumIncomingConnections(255); //Set the max number of connections
		 std::cout<< "[Login Server - GameServer Manager] " << " Started."<<std::endl;
		}
	}

	bool loginServerGameServerManager::handle() { //Handle packets
		RakNet::Packet *packet = this->gameServerInterface->Receive(); //Attempt to receive a packet
		if (packet!=NULL){ //If a packet was received
			unsigned char packetID = loginServer::GetPacketIdentifier(packet); //Get the packet ID
				switch (packetID) {
					case ID_NEW_INCOMING_CONNECTION: { //A new game server has connected
						std::cout<< "[Login Server - GameServer Manager] " << "New game server connected..."<<std::endl;
						gameServerClient* newGameServer = new gameServerClient(); //Create a new login player
						newGameServer->guid = packet->guid; //Set the new player's guid
						newGameServer->parentManager = this; //Set the parent manager to this manager
						this->peerList.SetNew(packet->guid,newGameServer); //Add the player to the map
						break;
							}
					default: peerList[peerList.GetIndexAtKey(packet->guid)]->handlePacket(packet); //Handle the packet using the player's object
				}
			this->gameServerInterface->DeallocatePacket(packet); //Deallocate the packet
		}
		return true;
	}

	void loginServerGameServerManager::shutdown() { //Cleanup 
		this->gameServerInterface->Shutdown(500); //Shutdown the client interface 
		RakNet::RakPeerInterface::DestroyInstance(this->gameServerInterface); //Destroy the client interface
	}


void gameServerClient::handlePacket(RakNet::Packet *packet) { //Handle a packet for a connected game server
	unsigned char packetID = loginServer::GetPacketIdentifier(packet); //Get the packet ID
			switch (packetID) {
			case UPDATE_GAMESERVER_INFO: receiveServerInfo(packet); break; //Authenticate the user
			default: { //Login server did not handle the packet, so pass it on to it's player object to handle
					std::cout << "[Login Server - GameServer Manager - Game Server Client] " << "Message was unhandled: " << (int)packetID << std::endl;
				}

			}
}


void gameServerClient::receiveServerInfo(RakNet::Packet *packet) {
	RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
	data.Read<RakNet::RakString>(serverName); //Read the server's name
	data.Read<RakNet::RakString>(broadcastIP); //Read the server's broadcasting I
	data.Read<short>(broadcastPort);

	std::cout << "Received server info: " << serverName.C_String()  << ", " << broadcastIP << ", " << broadcastPort << std::endl;
}

void gameServerClient::prepareTicket(unsigned char ticket[8],transferData &extraData) {
	RakNet::BitStream data;
	data.Write<RakNet::MessageID>(GENERATE_TICKET); 
	//Write the secure ticket
	for (unsigned char i=0; i<8; i++) {
		data.Write<unsigned char>(ticket[i]); //Write a byte
	}
	data.Write<int>(extraData.characterSelected); //Write the character selected
	this->parentManager->gameServerInterface->Send(&data,LOW_PRIORITY,RELIABLE,0,this->guid,false);
}
