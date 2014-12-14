#include "abstractServer.h"
#include "GTGameClient.h"
#include "GTLoginServerClient.h"
#include "database.h"
#include "mapHandler.h"
#include <iostream>

#ifndef _GAMESERVER_
#define _GAMESERVER_

struct transferTicket {
	unsigned char ticketData[8];
	int userDBID;
	int charDBID;
};

class GTGameServer : public abstractServer {
public:
	GTGameServer(std::string serverName, short listenPort, std::string broadcastIP);
	virtual void initialize();
	virtual void handle();
	virtual void shutdown();

	mapHandler& getMapHandler() { return _mHandler; }
	short getListeningPort() { return listeningPort; }
	std::string& getBroadcastIP() { return broadcastIP; }

	std::vector<transferTicket> ticketList;
private:
	clientManager<GTGameClient> publicAcceptor;
	clientManager<GTLoginServerClient> loginServerConnection;
	short listeningPort;
	std::string broadcastIP;
	mapHandler _mHandler;
};

#endif