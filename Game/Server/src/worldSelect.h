#include "packetProcessor.h"
#include "GTLoginClient.h"

class worldSelect : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		data.Read<unsigned short>(c.selectedWorld);
		RakNet::BitStream datas; //The bitstream
		datas.Write<RakNet::MessageID>(loginPackets::WORLDLIST_SELECT); //Message ID
		c.sendPacket(datas);

		//Populate character list

		if (gameDB.query(RakNet::RakString("SELECT * FROM characters WHERE userid = %i",c.dbID).C_String())) {
			if (gameDB.result().num_rows()>0) {
				for (int i=0; i<gameDB.result().num_rows() && i<CHARACTERSLOTS; i++) {
					c.characterSlots[i].cData = queries::getCharacterData(gameDB, gameDB.result()[i][0]);

					
					c.characterSlots[i].inUse = true;
					c.characterSlots[i].dbID = gameDB.result()[i][0];
				}
			}
		}

	}

};