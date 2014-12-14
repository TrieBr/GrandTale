#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <string>
#include <BitStream.h>
#include <characterCustomization.h>
#include <item.h>

bool ItemContainer::SwapSlot(ItemContainer* container, int slot1, int slot2) {
	ItemContainerEntry buffer = container->Items[slot2];
	container->setItem(slot2,Items[slot1]);
	setItem(slot1,buffer);
	return true;
}

void ItemContainer::readContainer(RakNet::BitStream &data) {
		//Inventories
		int inventorySize;
		data.Read<int>(linkID);
		data.Read<int>(inventorySize);
		setSize(inventorySize);
		for (int i=0; i<inventorySize; i++) {
			ItemContainerEntry iRead;
			data.Read<ItemContainerEntry>(iRead);
			setItem(i,iRead);
		}
	}
void ItemContainer::writeContainer(RakNet::BitStream &data){
	//Inventories
	data.Write<int>(linkID);
	int ii = getSize();
	data.Write<int>(getSize());
	for(int i=0; i<getSize(); i++) {
		data.Write<ItemContainerEntry>(getItem(i));
	}
}