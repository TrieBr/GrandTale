#include "itemManager.h"

void itemManager::allocateItems(int size) {
	items = new Item[size];
	itemCount = size;
}

Item itemManager::GetItem(int id){
	if (id==-1)
		return items[0];
	if (id<itemCount)
	return items[id];
	return items[0];
}
void itemManager::SetItem(int id, Item &item){
	items[id] = item;
}
