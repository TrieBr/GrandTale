// ----------------------------------------------------------------------
// loginPlayer.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Represents one connected player for the login server. Stores values and handles packets for the player
*/
// ------------------------------------------------------------------------

#include <RakPeerInterface.h>
#include <BitStream.h>
#include "packetIdentifiers.h"
#include "accountMysql.h"
#include "log.h"
#include "characterData.h"

#define CHARACTERSLOTS 3

#ifndef _H_LOGINPLAYER
#define _H_LOGINPLAYER

struct characterSlot {
	character::characterData cData;
	bool inUse; //Slot in use?
	int UID; //Unique ID for the character
};
class loginServer;
class loginPlayer
{
public:
	loginPlayer(); //Constructor
	void handlePacket(RakNet::Packet *packet); //Handle a packet
	loginServer* parentServer; //The parent login server that is managing this player
	bool				authenticated; //Is the player authenticated?
	int					userID; //Our user ID
	RakNet::RakNetGUID	guid; //Raknet GUID
	char				selectedSlot; //Selected characterSlot
	int					selectedServer; //Selected server index
private:
	characterSlot characterSlots[CHARACTERSLOTS];

	//Packet handlers
	void authenticate(RakNet::Packet *packet); //Authenticate the user
	void sendGameServerList(RakNet::Packet *packet); //Sebd game server list
	void sendCharacterList(RakNet::Packet *packet); //Send character list
	void createCharacter(RakNet::Packet *packet); //Add a new character to the account
	void selectWorld(RakNet::Packet *packet); //Select a world (game server)
	void deleteCharacter(RakNet::Packet *packet); //Delete a character
	void selectCharacter(RakNet::Packet *packet); //select a character
	void requestGameServerConnection(RakNet::Packet *packet); //request game server information

	
};


#endif