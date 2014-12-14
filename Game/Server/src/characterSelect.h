#include "packetProcessor.h"
#include "GTLoginClient.h"

class characterSelect : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		data.Read<char>(c.selectedCharacterSlot); //Read the ID that was selected
	}

};