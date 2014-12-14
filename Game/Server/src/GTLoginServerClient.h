
#include "characterData.h"
#include "abstractClient.h"

#ifndef _GTLOGINSERVERCLIENT_
#define _GTLOGINSERVERCLIENT_



class GTLoginServerClient : public abstractClient {
public:
	GTLoginServerClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface);

};

#endif