

#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"

class itemCustomizationFetch : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		int customizationID;
		int fetchID;
		data.Read<int>(customizationID);
		data.Read<int>(fetchID);
		RakNet::BitStream dataN;
		dataN.Write<RakNet::MessageID>(gamePackets::ITEM_CUSTOMIZATION_FETCH);
		itemCustomizationData temp;
		queries::downloadItemCustomizationData(gameDB,customizationID,&temp);
		dataN.Write<int>(fetchID);
		temp.writeData(dataN);
		c.sendPacket(dataN);
		
	}

};