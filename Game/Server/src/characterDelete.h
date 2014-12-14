#include "packetProcessor.h"
#include "GTLoginClient.h"

class characterDelete : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		unsigned short slotID;
		data.Read<unsigned short>(slotID); //Read the ID that was selected
		c.characterSlots[slotID].inUse = false; //No longer in use..

			gameDB.query(RakNet::RakString("DELETE FROM characters WHERE id = %i",
																						c.characterSlots[slotID].dbID).C_String());

		RakNet::BitStream datas; //The bitstream
		datas.Write<RakNet::MessageID>(loginPackets::CHARACTER_DELETE); //Message ID
		datas.Write<unsigned short>(slotID); //Tell the client to delete the character 
		c.sendPacket(datas);

		//c.sendCharacterList();
		

	}

};