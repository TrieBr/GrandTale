// ----------------------------------------------------------------------
// gameServerLoginServerManager.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Used for communicating with the login server.
*/
// ------------------------------------------------------------------------



#include "gameServerLoginServerManager.h"
#include "gameServer.h"
#include "log.h"

	void gameServerLoginServerManager::initialize(std::string loginServerHost, unsigned short loginServerPort, gameServer* parentServer) { //Initialize/connect to login server
		RakNet::StartupResult						sRes;
		loginServerInterface = RakNet::RakPeerInterface::GetInstance(); //Get a new peer interface
		sRes = loginServerInterface->Startup(1,new RakNet::SocketDescriptor(), 1); //Startup the interface
		RakNet::ConnectionAttemptResult cRes = loginServerInterface->Connect(loginServerHost.c_str(),loginServerPort,0,0); //Connect to the login server server
		this->parentServer = parentServer;
	} 

	bool gameServerLoginServerManager::handle() { //Handle messaged
		RakNet::Packet *packet = loginServerInterface->Receive(); //Attempt to receive a packet
		if (packet!=NULL){ //If a packet was received
			unsigned char packetID = gameServer::GetPacketIdentifier(packet); //Get the packet ID
				switch (packetID) {
				case ID_CONNECTION_REQUEST_ACCEPTED: { 
					std::cout << "[Game Server - Login Server Connection] " << "Connected to login server." << std::endl;
					sendServerInfo();
					break;
													 }
				case GENERATE_TICKET: {
						RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
						unsigned char ticket[8];
						for (unsigned char i=0; i<8; i++) {
							data.Read<unsigned char>(ticket[i]);
						}
						transferData extraData;
						data.Read<int>(extraData.characterSelected);
						log("[Game Server] Received transfer ticket: %02X %02X %02X %02X %02X %02X %02X %02X\n",ticket[0],ticket[1],ticket[2],ticket[3],ticket[4],ticket[5],ticket[6],ticket[7]);
						transferClient* newClient = new transferClient();
						for (unsigned char i=0; i<8; i++) { //for each of the  8 bytes
							newClient->ticket[i] = ticket[i]; //Set the ticket data
						}
						newClient->extraData = extraData;
						transferClientList.push_back(newClient);
						break;
									  }
				case ID_CONNECTION_ATTEMPT_FAILED: std::cout << "[Game Server - Login Server Connection] " << "Failed to connect to login server." << std::endl; break;
					//default: playerList[playerList.GetIndexAtKey(packet->guid)]->handlePacket(packet); //Handle the packet using the player's object
				}
			loginServerInterface->DeallocatePacket(packet); //Deallocate the packet
		}
		return true; //Handle packets with login Server.
	} 

	void gameServerLoginServerManager::shutdown() { //Cleanup/shutdown
		loginServerInterface->Shutdown(500); //Shutdown the client interface 
		RakNet::RakPeerInterface::DestroyInstance(loginServerInterface); //Destroy the client interface
	}



	void gameServerLoginServerManager::sendServerInfo() { //Sends server info to login Server.
		RakNet::BitStream data;
		data.Write<RakNet::MessageID>(UPDATE_GAMESERVER_INFO); //The packet ID
		data.Write<RakNet::RakString>(RakNet::RakString(this->parentServer->serverName.c_str())); //Send the server name.
		data.Write<RakNet::RakString>(RakNet::RakString(this->parentServer->broadcastIP.c_str()));
		data.Write<short>(this->parentServer->broadcastPort);
		this->loginServerInterface->Send(&data,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,1); //Send the paacket.

	}

