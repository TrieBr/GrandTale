
#include "characterData.h"
#include "abstractClient.h"

#ifndef _GTGAMEWORLDCLIENT_
#define _GTGAMEWORLDCLIENT_

class GTGameWorldClient : public abstractClient {
public:
	GTGameWorldClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface);
	RakNet::RakString		name;
	RakNet::RakString		IP;
	short					port;
};

#endif