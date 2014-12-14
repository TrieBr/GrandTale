#include "GTLoginClient.h"
#include "packetOpCodes.h"


GTLoginClient::GTLoginClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface) : abstractClient(guid,parentServer,clientInterface) {
	authenticated = false; //Not authenticated yet
	characterSlots.resize(CHARACTERSLOTS); //Reserve slots for characters
	for(unsigned int i=0; i<characterSlots.size(); i++) {
		characterSlots[i].inUse = false;
	}
}

void GTLoginClient::sendCharacterList() {
	RakNet::BitStream datas; //The bitstream
		datas.Write<RakNet::MessageID>(loginPackets::REQUEST_CHARACTERLIST); //Message ID
		datas.Write<unsigned char>(CHARACTERSLOTS); //Number of characters
		for (int i=0; i<CHARACTERSLOTS; i++) {
			datas.Write<bool>(characterSlots[i].inUse);
			if (characterSlots[i].inUse) {
				characterSlots[i].cData.writeCharacterData(datas);
			}
		}
		sendPacket(datas);
}