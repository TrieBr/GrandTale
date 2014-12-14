// ----------------------------------------------------------------------
// gameServer.h
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#ifndef _H_GAMESERVER
#define _H_GAMESERVER
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <string>
#include "abstractWorld.h"
#include <packetOpCodes.h>
#include "characterCustomization.h"
#include "entityPlayer.h"
#include "itemCustomizationDataFetch.h"
#define userCommandSendRate 30 //Number of packets per second to send containing input state...


namespace worlds {
	class worldGameMap;
}
namespace networking {

	class gameServer {
	public:
		static void connect(std::string ip, unsigned short port); //Initializes and connects
		static void disconnect(); //Disconnects and cleans up
		static void handle(); //Handle packets
		static bool connected; //Are we connected..?
		static unsigned char GetPacketIdentifier(RakNet::Packet *p); //Get a packet identifier
		static unsigned char			ticket[8]; //Secure ticket

		//Outgoing packets
		static void verifyTicket(unsigned char ticket[8]);
		static void sendPositionUpdate(const positionUpdate &newPosition);
		static void sendChatMessage(std::string message);
		static void itemContainer_SwapSlots(ItemContainer* container,ItemContainer* container2, int slot1, int slot2);
		static void equipment_EquipFromItemContainer(ItemContainer* container, int slotInd, int equipmentSlot);
		static void skill_execute(int skillUID);
		static void item_fetchCustomizationData(int customizationID, itemCustomizationFetchHandle* handle);
		static void stat_increase(statTypes stat, unsigned short numIncreases);

		static gameEngine::abstractWorld* parentWorld; //The world controlling the loginServer
		static worlds::worldGameMap*		currentGameMap; //Current game map controller
		static int							getLatency(); //Get latency with server
		static bool							initialized;
		static RakNet::SystemAddress		serverAddress; //RakNet ID for server
	private:
		static RakNet::RakPeerInterface*		serverPeer; //The peer for the connection with the server

		//Incoming packets
		static void receiveInitialInfo(RakNet::Packet *packet); //Received authentication results from server
		static void mapGoto(RakNet::Packet *packet); //Server is telling us to switch maps
		static void mapAddPlayer(RakNet::Packet *packet); //Adding another player to the map
		static void playerPositionUpdate(RakNet::Packet *packet); //A remote player has executed a movement action
		static void playerChatMessage(RakNet::Packet *packet); //A remote player sent a chat message
		static void itemContainer_Operation(RakNet::Packet *packet); //Server is sending an item container operation
		static void updateCharacterCustomization(RakNet::Packet *packet); //Player is updating their character Customization
		static void skillHandlerAction(RakNet::Packet *packet); //A Skill handler action was executed
		static void combatEntity(RakNet::Packet *packet); //A Skill handler action was executed
		static void item_fetchCustomizationData_received(RakNet::Packet *packet); //Item custom data fetch was received
		static void statCommandReceived(RakNet::Packet *packet); //Command for stats
		static void miscDataUpdateReceived(RakNet::Packet *packet); //Command for misc Data


	};
}

#endif