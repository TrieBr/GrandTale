// ----------------------------------------------------------------------
// loginServer.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	Connection with the login server. This handles things like authentication, server selection, character selection/creation and then eventually transferring to the game world.
*/
// ------------------------------------------------------------------------

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <string>
#include "abstractWorld.h"
#include "packetIdentifiers.h"
#include <packetOpCodes.h>
#include "characterCustomization.h"
#include "settings.h"

#ifndef _H_LOGINSERVER
#define _H_LOGINSERVER


namespace networking {

	class loginServer {
	public:
		static void connect(std::string ip, unsigned short port); //Initializes and connects
		static void disconnect(); //Disconnects and cleans up
		static void handle(); //Handle packets
		static bool connected; //Are we connected..?
		static unsigned char GetPacketIdentifier(RakNet::Packet *p); //Get a packet identifier

		//Packets
		static void authenticate(std::string username, std::string password); //Authenticate a username and password
		static void requestGameServerList(); //Request list of servers..
		static void requestCharacterList(); //Request list of characters
		static void createCharacter(character::characterCustomization* customization, std::string charName);
		static void selectServer(int serverInd); //Select a server
		static void deleteCharacter(int ID); //Delete the specified character ID
		static void selectCharacter(short slotID); //Select a character from a slot
		static gameEngine::abstractWorld* parentWorld; //The world controlling the loginServer

	private:
		static RakNet::RakPeerInterface*		serverPeer; //The peer for the connection with the server

		static void authenticateResult(RakNet::Packet *packet); //Received authentication results from server
		static void serverListResult(RakNet::Packet *packet); //Received the server list.
		static void characterListResult(RakNet::Packet *packet); //Received character List
		static void gameServerSelectAck(RakNet::Packet *packet); //Server has acknowledged that we selected a game world
		static void characterRemove(RakNet::Packet *packet); //Remove a character that is on the character select screen
		static void receiveGameServerConnectionInfo(RakNet::Packet *packet); //Receive data for connecting to game server
	};
}

#endif