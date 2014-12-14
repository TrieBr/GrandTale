// ----------------------------------------------------------------------
// gameServer.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Connection with the login server. This handles things like authentication, server selection, character selection/creation and then eventually transferring to the game world.
*/
// ------------------------------------------------------------------------

#include "gameServer.h"
#include <iostream>
#include "packetOpCodes.h"


namespace networking {
		RakNet::RakPeerInterface*		gameServer::serverPeer; //The peer for the connection with the server
		gameEngine::abstractWorld*		gameServer::parentWorld; //The world controlling the gameServer
		bool							gameServer::initialized = false;
		RakNet::SystemAddress			gameServer::serverAddress; //RakNet ID for serve
		worlds::worldGameMap*			gameServer::currentGameMap; //Current game map controller
		bool							gameServer::connected = false; //Are we connected..?
		unsigned char					gameServer::ticket[8]; //Secure ticket
		void gameServer::handle() { //Handle packets
			RakNet::Packet *packet = gameServer::serverPeer->Receive(); //Attempt to receive a packet
			if (packet!=NULL) { //If a packet has been received
				unsigned char packetID = GetPacketIdentifier(packet); //Get the packet id
				switch (packetID) { //Do actions based on the packet ID
				case ID_CONNECTION_REQUEST_ACCEPTED:  { connected = true; 
														serverAddress = packet->systemAddress;
															gameServer::serverPeer->SetOccasionalPing(true);	
														gameServer::verifyTicket(gameServer::ticket);
														break;
													  }//We are now connected.. 
				case gamePackets::INITIAL_INFOLOAD: receiveInitialInfo(packet); break;
				case gamePackets::MAP_GOTO: mapGoto(packet); break;
				case gamePackets::PLAYER_CHARACTER_DATA: mapAddPlayer(packet); break; //Server is sending us a player to add to the map
				case gamePackets::PLAYER_POSITIONUPDATE: playerPositionUpdate(packet); break; //A remote player has executed a movement action
				case gamePackets::PLAYER_CHAT: playerChatMessage(packet); break; //A remote player has chatted
				case gamePackets::ITEM_CONTAINER_ACTION: itemContainer_Operation(packet); break;
				case gamePackets::PLAYER_UPDATE_CUSTOMIZATION: 	updateCharacterCustomization(packet); break;
				case gamePackets::SKILLHANDLER_ACTION: 	skillHandlerAction(packet); break;
				case gamePackets::COMBAT_ENTITY: 	combatEntity(packet); break;
				case gamePackets::ITEM_CUSTOMIZATION_FETCH: item_fetchCustomizationData_received(packet); break;
				case gamePackets::STAT_COMMAND: statCommandReceived(packet); break;
				case gamePackets::MISC_DATA_UPDATE: miscDataUpdateReceived(packet); break;

				default: { std::cout << "[Game Server] Unhandled message ID: " << (int)packetID << std::endl; break; }
				}
				gameServer::serverPeer->DeallocatePacket(packet); //Deallocate the packet
			}
		}

		unsigned char gameServer::GetPacketIdentifier(RakNet::Packet *p) { //Get a packet identifier
			if ((unsigned char)p->data[0] == ID_TIMESTAMP)
			return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
			else
			return (unsigned char) p->data[0];
		}

		void gameServer::connect(std::string ip, unsigned short port) {
			serverPeer = RakNet::RakPeerInterface::GetInstance(); //Create a new interface
           
			serverPeer->Startup(1, new RakNet::SocketDescriptor(), 1); //Start up the interface
			RakNet::ConnectionAttemptResult cRes = serverPeer->Connect(ip.c_str(),port,0,0); //Connect to the server
			//assert(cRes!=RakNet::CONNECTION_ATTEMPT_STARTED); //Assert if we were unable to connect
			//serverPeer->ApplyNetworkSimulator(0, 800,  30);
			initialized = true;
		}
		int gameServer::getLatency() { //Get latency with server
			if (initialized) {
				return gameServer::serverPeer->GetAveragePing(serverAddress);
			}else{
				return -2;
			}
		}
		void gameServer::disconnect() { //Disconnects and cleans up
			if (initialized) {

				serverPeer->Shutdown(500,0,HIGH_PRIORITY); //Shutdown the peer interface
				
				RakNet::RakPeerInterface::DestroyInstance(serverPeer); //destroy the peer interface
			}
		}


		//============== Outgoing packets =============
		void gameServer::verifyTicket(unsigned char ticket[8]) {
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::TICKET_VERIFY);
			for(char i=0; i<8; i++) {
				data.Write<unsigned char>(ticket[i]); //Write ticket bytes
			}
			gameServer::serverPeer->Send(&data,LOW_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}

		void gameServer::sendPositionUpdate(const positionUpdate &newPosition) { //Send position update
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::PLAYER_POSITIONUPDATE);
			data.Write<positionUpdate>(newPosition);
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,UNRELIABLE_SEQUENCED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}
		void gameServer::sendChatMessage(std::string message){
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::PLAYER_CHAT);
			data.Write<RakNet::RakString>((RakNet::RakString)message.c_str());
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}
		void gameServer::itemContainer_SwapSlots(ItemContainer* container1, ItemContainer* container2, int slot1, int slot2){
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::ITEM_CONTAINER_ACTION);
			data.Write<int>(gamePackets::ITEM_CONTAINER_SWAP_SLOTS); //Action for the item container
			data.Write<int>(container1->linkID); //The link ID so the server knows what container we are talking about..
			data.Write<int>(container2->linkID); //The link ID so the server knows what container we are talking about..
			data.Write<int>(slot1);
			data.Write<int>(slot2);
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}
		void gameServer::equipment_EquipFromItemContainer(ItemContainer* container, int slotInd, int equipmentSlot){
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::EQUIPMENT_ACTION);
			data.Write<int>(gamePackets::EQUIP_FROM_ITEM_CONTAINER); //Action for equipment
			data.Write<int>(container->linkID); //The link ID so the server knows what container we are talking about..
			data.Write<int>(slotInd);
			data.Write<int>(equipmentSlot);
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		}
		 void gameServer::skill_execute(int skillUID) {
			 RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::SKILLHANDLER_ACTION);
			data.Write<int>(gamePackets::SKILL_EXECUTED);
			data.Write<int>(skillUID); //The UID of this skill
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server

		}
		 void gameServer::item_fetchCustomizationData(int customizationID, itemCustomizationFetchHandle* handle) {
			 RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::ITEM_CUSTOMIZATION_FETCH);
			data.Write<int>(customizationID);
			data.Write<int>(handle->getFetchID()); //The fetch ID
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		 }
		 void gameServer::stat_increase(statTypes stat, unsigned short numIncreases) {
			RakNet::BitStream data;
			data.Write<RakNet::MessageID>(gamePackets::STAT_COMMAND);
			data.Write<RakNet::MessageID>(gamePackets::STAT_COMMAND_INCREASE_STAT);
			data.Write<unsigned short>((unsigned short)stat);
			data.Write<unsigned short>(numIncreases); //Number of times to increase
			gameServer::serverPeer->Send(&data,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true); //Send to the server
		 }
}
