

#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"

class statCommand : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		RakNet::MessageID subID;
		data.Read<RakNet::MessageID>(subID);
		if (subID==gamePackets::STAT_COMMAND_INCREASE_STAT) {
			statTypes stat;
			unsigned short s;
			data.Read<unsigned short>(s);
			stat = (statTypes)s;
			unsigned short numIncreases;
			data.Read<unsigned short>(numIncreases);
			if (c.miscData.getRemainingStatPoints()>=1) {
			c.setBaseStat(stat,c.getBaseStat(stat)+1);
			
			c.miscData.setRemainingStatPoints(c.miscData.getRemainingStatPoints()-1);

			c.recalculateStats();
			RakNet::BitStream dataN;
			dataN.Write<RakNet::MessageID>(gamePackets::STAT_COMMAND);
			dataN.Write<RakNet::MessageID>(gamePackets::STAT_UPDATE);
			c.writeData(dataN);
			c.sendPacket(dataN);

			

			RakNet::BitStream dataN2;
			dataN2.Write<RakNet::MessageID>(gamePackets::MISC_DATA_UPDATE);
			c.miscData.writeData(dataN2, MISC_DATA_REMAINING_STAT_POINTS);
			c.sendPacket(dataN2);

			}

		}
		
		
	}

};