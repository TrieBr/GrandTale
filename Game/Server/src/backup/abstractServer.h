
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <DS_Map.h>
#include <vector>
#include <string>
#include "PacketProcessor.h"
#include "clientManager.h"

#ifndef _ABSTRACTSERVER_
#define _ABSTRACTSERVER_

class abstractServer {
public:
	abstractServer();
	void setIdentifier(std::string str) { serverIdentifier = str;}
	std::string& getIdentifier() { return serverIdentifier; }
	virtual ~abstractServer();
	virtual void initialize(); //Initialize the server
	virtual void handle(); //handle the server
	virtual void shutdown(); //shutdown the server
	
	virtual void broadcastPacket(RakNet::BitStream &data, PacketPriority priority = MEDIUM_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, int orderingChannel = 0) {}
	

private:
	std::string serverIdentifier;
};

#endif