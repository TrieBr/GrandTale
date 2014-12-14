#include <combatEntity.h>

void combatEntity::setParentMap(gameMap* map) {
	parentMap = map;
}
gameMap* combatEntity::getParentMap() {
	return parentMap;
}


void combatEntity::setType(CombatEntityType t) {
	type = t;
}
CombatEntityType combatEntity::getType() {
	return type;
}
void combatEntity::setUID(int val) {
	UID = val;
}
int combatEntity::getUID() {
	return UID;
}

void combatEntity::setX(float val) {
	x = val;
}
float combatEntity::getX() {
	return x;
}
void combatEntity::setY(float val) {
	y = val;
}
float combatEntity::getY() {
	return y;
}



void combatEntity::setCurrentHealth(int val) {
	currentHealth = val;
}
int combatEntity::getCurrentHealth() {
	return currentHealth;
}


void combatEntity::setCurrentMana( int val) {
	currentMana = val;
}
int combatEntity::getCurrentMana() {
	return currentMana;
}
void combatEntity::setLevel (unsigned char val) {
	level = val;
}
unsigned char combatEntity::getLevel() {
	return level;
}
void combatEntity::setElement(unsigned char val) {
	element = val;
}
unsigned char combatEntity::getElement() {
	return element;
}
void combatEntity::setSize( unsigned char val) {
	size = val;
}
unsigned char combatEntity::getSize() {
	return size;
}

void combatEntity::hit(hitData & data) {
	this->setCurrentHealth(this->getCurrentHealth()-data.damage);
	if (getCurrentHealth()<0) setCurrentHealth(0);
	lastHitData = data;


}

hitData& combatEntity::getLastHitData() {
	return lastHitData;
}

void combatEntity::writeCombatData(RakNet::BitStream &data) {
	data.Write<float>(getX());
	data.Write<float>(getY());
	data.Write<int>(getCurrentHealth());
	data.Write<int>(getCurrentMana());
	data.Write<unsigned char>(getLevel());
	data.Write<unsigned char>(getElement());
	data.Write<unsigned char>(getSize());
	writeData(data); //Write stats data


}
	void combatEntity::readCombatData(RakNet::BitStream &data) {
		data.Read<float>(x);
		data.Read<float>(y);
		data.Read<int>(currentHealth);
		data.Read<int>(currentMana);
		data.Read<unsigned char>(level);
		data.Read<unsigned char>(element);
		data.Read<unsigned char>(size);
		readData(data); //Read stats data

	}