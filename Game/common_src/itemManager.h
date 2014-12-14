#include <item.h>

#ifndef _ITEMMANAGER
#define _ITEMMANAGER


class itemManager {
public:
	Item GetItem(int id); 
	void SetItem(int id, Item &item);
	void allocateItems(int size);
private:
	Item* items;
	int itemCount;

};
#endif 