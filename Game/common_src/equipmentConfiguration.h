#include <item.h>

#ifndef _H_EQUIPCONFIG
#define  _H_EQUIPCONFIG

class equipmentConfiguration {
public:
	static bool isDialWielding(Item& mainHand, Item& offHand);
	static bool isMainHandWithShield(Item& mainHand, Item& offHand);
	static bool isTwoHand(Item& mainHand, Item& offHand);
};

#endif