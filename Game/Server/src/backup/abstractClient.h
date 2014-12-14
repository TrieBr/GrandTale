
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <BitStream.h>
#include <RakPeer.h>

#ifndef _ABSTRACTCLIENT_
#define _ABSTRACTCLIENT_

class abstractServer;
class abstractClient {
public:
	abstractClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface);
	void sendPacket(RakNet::BitStream &data, PacketPriority priority = MEDIUM_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, int orderingChannel = 0);
	abstractServer &parentServer();
	RakNet::RakPeerInterface& clientInterface() { return *_clientInterface; }
private:
	RakNet::RakNetGUID guid;
	abstractServer* _parentServer;
	RakNet::RakPeerInterface*		_clientInterface;
};

#endif