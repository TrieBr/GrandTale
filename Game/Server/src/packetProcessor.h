#include "GTLoginClient.h"
#include "GTGameClient.h"
#include "GTGameWorldClient.h"
#include "GTLoginServerClient.h"
#include <packetOpCodes.h>


#ifndef _PACKETPROCESSOR_
#define _PACKETPROCESSOR_

class packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {}
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {}
	virtual void handle(RakNet::BitStream &data, GTGameWorldClient &c) {}
	virtual void handle(RakNet::BitStream &data, GTLoginServerClient &c) {}
private:
};

#endif