

#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"

class playerItemContainerOperation : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		int Operation, linkID1, linkID2;
		data.Read<int>(Operation);
		data.Read<int>(linkID1); //Container 1
		data.Read<int>(linkID2); //Container 2
		if (Operation==(int)gamePackets::ITEM_CONTAINER_SWAP_SLOTS) {
			ItemContainer* container1 = c.itemContainerLinks.FetchLinkedContainer(linkID1);
			ItemContainer* container2= c.itemContainerLinks.FetchLinkedContainer(linkID2);
			if (container1!=NULL && container2!=NULL) {
				int slot1, slot2;
				data.Read<int>(slot1);
				data.Read<int>(slot2);

				if (container1==&c.equipmentContainer) { //Something is being dragged into equip container
					if (!c.canEquipItem(container2->getItem(slot2),slot1)) {
						return;
					}
				}

				if (container1->SwapSlot(container2, slot1,slot2)) {
					c.updateContainer(container1,slot1); //Update the client with the container data
					c.updateContainer(container2,slot2); //Update the client with the container data
				}
			}
		}
	}

};