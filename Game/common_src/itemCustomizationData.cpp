#include "itemCustomizationData.h"



itemCustomizationData::itemCustomizationData() {
	for (unsigned char i= 0; i<STAT_COUNT; i++) {

		setBaseStat((statTypes)(int)i,0);
		setBonusStat((statTypes)(int)i,0);
	}
}

void itemCustomizationData::setBaseStat(statTypes stat, short val) {
	stat_base[(int)stat] = val;
}
void itemCustomizationData::setBonusStat(statTypes stat, short val) {
	stat_bonus[(int)stat] = val;
}
short itemCustomizationData::getBaseStat(statTypes stat) {
	return stat_base[(int)stat];
}
short itemCustomizationData::getBonusStat(statTypes stat) {
	return stat_bonus[(int)stat];
}

bool itemCustomizationData::hasEquipEffect() {
	return getEquipText().length()!=0;
}
bool itemCustomizationData::hasActiveEffect() {
	return getActiveText().length()!=0;
}

unsigned short itemCustomizationData::getWeaponDamage() {
	return weaponDamage;
}
void itemCustomizationData::setWeaponDamage(unsigned short dmg) {
	weaponDamage = dmg;
}

std::string &itemCustomizationData::getEquipText() {
	return equipText;
}
void itemCustomizationData::setEquipText(std::string text) {
	equipText = text;
}
std::string &itemCustomizationData::getActiveText() {
	return activeText;
}
void itemCustomizationData::setActiveText(std::string text) {
	activeText = text;
}

void itemCustomizationData::writeData(RakNet::BitStream &data) {
	for (unsigned char i= 0; i<STAT_COUNT; i++) {
		data.Write<short>(getBaseStat((statTypes)(int)i));
		data.Write<short>(getBonusStat((statTypes)(int)i));
	}
	data.Write<RakNet::RakString>(RakNet::RakString(getEquipText().c_str()));
	data.Write<RakNet::RakString>(RakNet::RakString(getActiveText().c_str()));
	data.Write<unsigned short>(getWeaponDamage());

}
void itemCustomizationData::readData(RakNet::BitStream &data) {
	for (unsigned char i= 0; i<STAT_COUNT; i++) {
		short buf;
		data.Read<short>(buf);
		setBaseStat((statTypes)(int)i,buf);
		data.Read<short>(buf);
		setBonusStat((statTypes)(int)i,buf);
	}
	RakNet::RakString buf;
	data.Read<RakNet::RakString>(buf);
	setEquipText(std::string(buf.C_StringUnsafe()));
	data.Read<RakNet::RakString>(buf);
	setActiveText(std::string(buf.C_StringUnsafe()));
	data.Read<unsigned short>(weaponDamage);

}
