#include "packetProcessor.h"
#include "GTLoginClient.h"

class requestWorldList : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		RakNet::BitStream datas; //The bitstream
		datas.Write<RakNet::MessageID>(loginPackets::REQUEST_WORLDLIST); //Message ID
		datas.Write<unsigned char>((unsigned char)(((GTLoginServer*)&c.parentServer())->gameWorldAcceptor.getClientCount())); //Number of servers.
		for (unsigned int i=0; i<((GTLoginServer*)&c.parentServer())->gameWorldAcceptor.getClientCount(); i++) {

			datas.Write<RakNet::RakString>(((GTLoginServer*)&c.parentServer())->gameWorldAcceptor.getClient(i)->name); //The server name
			datas.Write<unsigned char>(i); //The ID of the server (currently just the number in the map...) TODO: Possibly make a safer way to identify game servers.
		}
		c.sendPacket(datas);
	}

};