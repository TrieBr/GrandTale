

#include <vector>
#include <map>
#include <iostream>
#include <abstractItemContainerCallback.h>

#ifndef __ITEM_
#define __ITEM_

namespace RakNet {
class BitStream;
}

enum ITEM_TYPE {
	ITEM_USABLE = 1,
	ITEM_EQUIP = 2,
	ITEM_REGULAR = 4,
	ITEM_TYPE_COUNT = 3,
	ITEM_UNDEFINED = 0
};

class Item {
public:
	Item() {  type = ITEM_UNDEFINED; iconID = -1; weaponType=0; itemName = std::string(); }
	ITEM_TYPE type; //Type of the item
	int iconID; //ID of the icon for the item
	std::string itemName; //Name of the item
	unsigned char equipType;
	unsigned char weaponType;
	unsigned int classRestrictions;
};


class ItemContainerEntry {
public:
	ItemContainerEntry() { itemID = -1;}
	bool isCustom;
	int stackCount;
	int itemID;
	int iconID;
	int customizationID;
};

//Used for storing a bunch of items
class ItemContainer { 
public:
	ItemContainer() {
		setSize(0);
		callback=NULL;
	}
	ItemContainer(int size) {
		setSize(size);
	}
	void setSize(int size) {
		for (int i=0; i<size; i++) {
			Items.push_back(ItemContainerEntry());
		}
	}
	int getSize() {
		return Items.size();
	}
	ItemContainerEntry getItem(int ind) { return Items[ind]; }
	void setItem(int slot, ItemContainerEntry &item) {
		Items[slot] = item;
		if (callback!=NULL) {
			callback->SlotChanged(this,slot);
		}
	}
	void registerCallback(abstractItemContainerCallback* cB) { callback = cB; }

	void readContainer(RakNet::BitStream &data);
	void writeContainer(RakNet::BitStream &data);
	//Container Operations (Used on server, client must call the networking::gameServer to initiate remote container operations)
	bool SwapSlot(ItemContainer* container, int slot1, int slot2);

	//Client-Server Linkage
	int linkID; //Both the server and client must have the same linkID for the inventory, to communicate
	int itemTypes;

private:
	std::vector<ItemContainerEntry> Items;
	abstractItemContainerCallback* callback;

};

class ItemContainerLinker { //Links an item container accross the client and the server.
public:
	ItemContainerLinker() { nextID = 0; }
	int LinkContainer(ItemContainer* container){
		nextID++;
		containerLink[nextID] = container;
		container->linkID = nextID;
		return nextID;
	}
	void  LinkContainer(ItemContainer* container, int linkID){
		if (containerLink.find(linkID)!=containerLink.end()) {
			std::cout << "ItemLinker over writing link ID: " << linkID << std::endl;
		}else{
		containerLink[linkID] = container;
		}
	}
	ItemContainer* FetchLinkedContainer(int id){
		if (containerLink.find(id)!=containerLink.end()){
			return containerLink.find(id)->second;
		}else{
			std::cout << "ERROR: Fetching invalid item container link ID. (item.h ItemContainerLinker::FetchLinkedContainer("<<id<<")" << std::endl;
		}
		return NULL;
	}
	void UnlinkContainer(int id){
		containerLink.erase(id);
	}
private:
	std::map<int,ItemContainer*> containerLink;
	int nextID;
};

#endif