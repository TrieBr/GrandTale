#include "packetProcessor.h"
#include "GTGameWorldClient.h"

class gameWorldSendData : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameWorldClient &c) {
		data.Read<RakNet::RakString>(c.name);
		data.Read<RakNet::RakString>(c.IP);
		data.Read<short>(c.port);
		std::cout << "[" << c.parentServer().getIdentifier() << "]" << "World Data received: " << c.name.C_String() << "," <<  c.IP.C_String() << "," << c.port << std::endl;
	}

};