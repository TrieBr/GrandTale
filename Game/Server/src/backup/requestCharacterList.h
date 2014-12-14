#include "packetProcessor.h"
#include "GTLoginClient.h"

class requestCharacterList : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		c.sendCharacterList();
		
	}

};