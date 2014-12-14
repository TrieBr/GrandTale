

#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"

class playerEquipOperations : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		int Operation, linkID;
		data.Read<int>(Operation);
		data.Read<int>(linkID); //Container ID
		if (Operation==(int)gamePackets::EQUIP_FROM_ITEM_CONTAINER) {
			ItemContainer* container = c.itemContainerLinks.FetchLinkedContainer(linkID);
			if (container!=NULL) {
				if (container==&c.Inventory_Equip) { //Make sure is from the players equipment inventory
					int slot, equipmentSlot;
					data.Read<int>(slot);
					data.Read<int>(equipmentSlot);
					if (c.canEquipItem(container->getItem(slot),equipmentSlot)) {
						ItemContainerEntry itemEquip = container->getItem(slot);
						/*if (c.cData.equipment[equipmentSlot]!=0) {
							Item i;
							i.type=ITEM_EQUIP;
							//i.iconID = 
							//container->setItem(slot,
						}*/
					}
					//if (container1->SwapSlot(container2, slot1,slot2)) {
						//c.updateContainer(container1,slot1); //Update the client with the container data
						//c.updateContainer(container2,slot2); //Update the client with the container data
					//}
				}
			}
		}
	}

};