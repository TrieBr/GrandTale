// ----------------------------------------------------------------------
// gameServerLoginServerManager.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Used for communicating with the login server.
*/
// ------------------------------------------------------------------------



#include <RakPeerInterface.h>
#include <string>
#include <vector>
#include "gameServerLoginServer_InterfaceData.h"
#ifndef _H_GAMESERVERLOGINSERVERMANAGER_
#define _H_GAMESERVERLOGINSERVERMANAGER_

struct transferClient {
unsigned char ticket[8]; //Ticket the user must verify with...
double expireTime; //When this transfer will expire..
transferData extraData;
//Other data that can be transfered..
};

class gameServer;
class gameServerLoginServerManager {
public:
	void initialize(std::string loginServerHost, unsigned short loginServerPort, gameServer* parentServer); //Initialize/connect to login server
	bool handle(); //Handle messaged
	void shutdown(); //Cleanup/shutdown

	//Packets
	void sendServerInfo(); //Sends server info to login Server.

	gameServer* parentServer; //Server controlling this
	std::vector<transferClient*> transferClientList; //List of clients waiting to transfer..
private:
	RakNet::RakPeerInterface* loginServerInterface; //The connection with the login server



};


#endif