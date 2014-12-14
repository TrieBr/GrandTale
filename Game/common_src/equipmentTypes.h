#ifndef _EQUIPTYPE_H_
#define _EQUIPTYPE_H_
enum equipType {
	EQUIP_BELT, 
	EQUIP_GLOVE, 
	EQUIP_HELMET, 
	EQUIP_PANTS, 
	EQUIP_SHIRT, 
	EQUIP_SHOE, 
	EQUIP_SHOULDER, 
	EQUIP_OFFHAND, //Can only be equipped offhand
	EQUIP_RANGED, 
	EQUIP_RING, 
	EQUIP_RING2, 
	EQUIP_MAINHAND, //Can only be equipped main hand
	EQUIP_TRINKET,
	EQUIP_WEAPON, //Can be equipped in main hand OR offhand
	EQUIP_TWOHAND, //Two handed weapon. Takes both offhand and mainhand slots.
	EQUIP_HEAD_LOWER,
	EQUIP_TYPE_COUNT 
};

enum weaponType {
	WEAPON_NONE,
	WEAPON_DAGGER,
	WEAPON_SWORD,
	WEAPON_AXE,
	WEAPON_PROJECTILE,
	WEAPON_FIST,
	WEAPON_MACE,
	WEAPON_BOW,
	WEAPON_STAFF,
	WEAPON_WAND,
	WEAPON_SPEAR,
	WEAPON_SHIELD
};

#endif