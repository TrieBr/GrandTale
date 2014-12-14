#include <equipmentConfiguration.h>
#include <equipmentTypes.h>

bool equipmentConfiguration::isDialWielding(Item& mainHand, Item& offHand) {
	if (mainHand.equipType==EQUIP_MAINHAND || mainHand.equipType==EQUIP_WEAPON) {
		if (offHand.equipType==EQUIP_OFFHAND || offHand.equipType==EQUIP_WEAPON) {
			if (offHand.weaponType!=WEAPON_SHIELD) {
				return true;
			}
		}
	}
	return false;
}

bool equipmentConfiguration::isMainHandWithShield(Item& mainHand, Item& offHand) {
	if (mainHand.equipType==EQUIP_MAINHAND || mainHand.equipType==EQUIP_WEAPON) {
		if (offHand.equipType==EQUIP_OFFHAND && offHand.weaponType==WEAPON_SHIELD) {
			return true;
		}
	}
	return false;
}

bool equipmentConfiguration::isTwoHand(Item& mainHand, Item& offHand) {
	if (mainHand.equipType==EQUIP_TWOHAND ) {
			return true;
	}
	return false;
}
