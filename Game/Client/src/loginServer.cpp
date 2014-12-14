// ----------------------------------------------------------------------
// loginServer.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Connection with the login server. This handles things like authentication, server selection, character selection/creation and then eventually transferring to the game world.
*/
// ------------------------------------------------------------------------

#include "loginServer.h"
#include <iostream>

namespace networking {
		RakNet::RakPeerInterface*		loginServer::serverPeer; //The peer for the connection with the server
		gameEngine::abstractWorld*		loginServer::parentWorld; //The world controlling the loginServer
		bool							loginServer::connected = false; //Are we connected..?

		void loginServer::handle() { //Handle packets
			RakNet::Packet *packet = loginServer::serverPeer->Receive(); //Attempt to receive a packet
			if (packet!=NULL) { //If a packet has been received
				unsigned char packetID = GetPacketIdentifier(packet); //Get the packet id
                std::cout << (int)packetID << std::endl;
				switch (packetID) { //Do actions based on the packet ID
				case ID_CONNECTION_REQUEST_ACCEPTED: connected = true; break; //We are now connected.. 
				case loginPackets::CLIENT_AUTHENTICATE: authenticateResult(packet); break;
				case loginPackets::REQUEST_WORLDLIST: serverListResult(packet); break; //Server list was sent to us.
				case loginPackets::REQUEST_CHARACTERLIST : characterListResult(packet); break; //Receive character List.
				case loginPackets::WORLDLIST_SELECT : gameServerSelectAck(packet); break; //Server has acknowledged that we selected a game world/server
				case loginPackets::CHARACTER_DELETE: characterRemove(packet); break; //Remove character
				case loginPackets::GAMEWORLD_CONNECT: receiveGameServerConnectionInfo(packet); break;

				default: { std::cout << "Unhandled message ID: " << (int)packetID << std::endl; break; }
				}
				loginServer::serverPeer->DeallocatePacket(packet); //Deallocate the packet
			}
		}

		

		unsigned char loginServer::GetPacketIdentifier(RakNet::Packet *p) { //Get a packet identifier
			if ((unsigned char)p->data[0] == ID_TIMESTAMP)
			return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
			else
			return (unsigned char) p->data[0];
		}

		void loginServer::connect(std::string ip, unsigned short port) {
			serverPeer = RakNet::RakPeerInterface::GetInstance(); //Create a new interface
			serverPeer->Startup(1, new RakNet::SocketDescriptor(), 1); //Start up the interface
			RakNet::ConnectionAttemptResult cRes = serverPeer->Connect(ip.c_str(),port,0,0); //Connect to the server
			//assert(cRes!=RakNet::CONNECTION_ATTEMPT_STARTED); //Assert if we were unable to connect
		}

		void loginServer::disconnect() { //Disconnects and cleans up
			serverPeer->Shutdown(500); //Shutdown the peer interface
			RakNet::RakPeerInterface::DestroyInstance(serverPeer); //destroy the peer interface
		}

		void loginServer::authenticate(std::string username, std::string password) { //Authenticate a username and password
			RakNet::BitStream data; //The data buffer
			data.Write<RakNet::MessageID>(loginPackets::CLIENT_AUTHENTICATE); //Write the packet id: Authentication packet
			data.Write<RakNet::RakString>(RakNet::RakString(username.c_str())); //write the username
			data.Write<RakNet::RakString>(RakNet::RakString(password.c_str())); //write the password
			loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}

		void loginServer::requestGameServerList() { 
			RakNet::BitStream data;
				data.Write<RakNet::MessageID>(loginPackets::REQUEST_WORLDLIST); //Message ID
				loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}
		void loginServer::requestCharacterList() { //Request list of characters
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(loginPackets::REQUEST_CHARACTERLIST); //Message ID
			loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}

		void loginServer::createCharacter(character::characterCustomization* customization, std::string charName) { 
			RakNet::BitStream data;
				data.Write<RakNet::MessageID>(loginPackets::CHARACTER_CREATE); //Message ID
				data.Write<RakNet::RakString>(RakNet::RakString(charName.c_str())); //Character String
				customization->writeCharacterCustomization(data); //Write the customization data
				loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}

		 void loginServer::selectServer(int serverInd) { //Select a server
			 RakNet::BitStream data;
			data.Write<RakNet::MessageID>(loginPackets::WORLDLIST_SELECT); //Message ID
			data.Write<unsigned short>(serverInd); //server ID
			loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		 }

		  void loginServer::deleteCharacter(int ID) { //Delete the specified character ID
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(loginPackets::CHARACTER_DELETE); //Message ID
			data.Write<unsigned short>(ID); //character ID
			loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server

		  }

		  void loginServer::selectCharacter(short slotID) { //Select a character from a slot
			  RakNet::BitStream data;
			data.Write<RakNet::MessageID>(loginPackets::CHARACTER_SELECT); //Message ID
			data.Write<unsigned char>(slotID); //character ID
			loginServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server

			 RakNet::BitStream data2;
			data2.Write<RakNet::MessageID>(loginPackets::GAMEWORLD_CONNECT); //Message ID
			loginServer::serverPeer->Send(&data2,LOW_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server

		  }
}
