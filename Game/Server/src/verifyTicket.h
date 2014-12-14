#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"

class verifyTicket : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		unsigned char ticket[8];
	for (char i =0; i<8; i++) { //For each of the 8 bytes
		data.Read<unsigned char>(ticket[i]);
	}

	for (unsigned int i=0; i<((GTGameServer*)&c.parentServer())->ticketList.size(); i++) { //For each client waiting for transfer
		bool match = true; //Is this waiting client a match for the requested ticket?
		int ticketMatch = 0;
		for (char t =0; t<8; t++) { //For each of the 8 bytes
			if (ticket[t]!=((GTGameServer*)&c.parentServer())->ticketList[i].ticketData[t]) {
				ticketMatch = i;
				match = false;
				break;
			}
		}

		if (match) { //Waiting client matches
			std::cout << "[" << c.parentServer().getIdentifier() << "]" << "Client has matched ticket sucessfully." << std::endl;
			c.userDBID = ((GTGameServer*)&c.parentServer())->ticketList[i].userDBID;
			c.charDBID = ((GTGameServer*)&c.parentServer())->ticketList[i].charDBID;
			c.UID = rand() % 10000; //TODO: make this generate an actual unique ID thats no the same as other clients
			c.cData = queries::getCharacterData(gameDB,c.charDBID); //Get the players character from the database
			queries::downloadPlayerCombatData(gameDB,&c,c.charDBID);
			queries::downloadPlayerMiscData(gameDB,c.charDBID,&c.miscData);
			int cIE,cIU, cIR, e; //The container ID's
			queries::getCharacterContainers(gameDB,c.charDBID,&cIE,&cIU,&cIR,&e);
			queries::populateContainer(gameDB,c.Inventory_Usable,cIU);
			queries::populateContainer(gameDB,c.Inventory_Equip,cIE);
			queries::populateContainer(gameDB,c.Inventory_Regular,cIR);
			queries::populateContainer(gameDB,c.equipmentContainer,e);
			queries::downloadCharacterSkills(gameDB,c.charDBID,&c); //Get the characters skills
			//Link up the main inventories..
			c.itemContainerLinks.LinkContainer(&c.Inventory_Usable);
			c.itemContainerLinks.LinkContainer(&c.Inventory_Equip);
			c.itemContainerLinks.LinkContainer(&c.Inventory_Regular);
			c.itemContainerLinks.LinkContainer(&c.equipmentContainer);
			c.sendInitialData();
			c.mapGoto(((GTGameServer*)&c.parentServer())->getMapHandler().getDefaultMap(c.cData.getMapID()));
			return;
			break;
		}
	}

	std::cout << "[" << c.parentServer().getIdentifier() << "]" << "Client has failed ticket verification" << std::endl;
	//Tell the client their ticket is invalid..
	RakNet::BitStream dataW; //The bitstream
	dataW.Write<RakNet::MessageID>(gamePackets::TICKET_VERIFY); //Message ID
	dataW.Write<unsigned short>(1); //Invalid ticket
	c.sendPacket(dataW);

	}

};