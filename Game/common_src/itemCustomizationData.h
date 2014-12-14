
#include <stats.h>
#include <BitStream.h>
#include <string>

/*
Defines custom data for an item, including stats, any other effects, etc.

*/

#ifndef _H_ITEMCUSTOMDATA
#define _H_ITEMCUSTOMDATA

class itemCustomizationData {
public:
	itemCustomizationData();
	void setBaseStat(statTypes stat, short val);
	void setBonusStat(statTypes stat, short val);
	short getBaseStat(statTypes stat);
	short getBonusStat(statTypes stat);
	bool hasEquipEffect();
	bool hasActiveEffect();
	unsigned short getWeaponDamage();
	void setWeaponDamage(unsigned short dmg);
	std::string &getEquipText();
	void setEquipText(std::string text);
	std::string &getActiveText();
	void setActiveText(std::string text);
	
	void writeData(RakNet::BitStream &data);
	void readData(RakNet::BitStream &data);
private:
	short stat_base[STAT_COUNT];
	short stat_bonus[STAT_COUNT];
	std::string equipText; //Txt that describes that this item does when equipping
	std::string activeText; //Text that describes what this item does when activating
	unsigned short weaponDamage;

};

#endif