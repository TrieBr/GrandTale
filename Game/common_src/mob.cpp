#include <mob.h>

mob::mob() {
	speed = 0;
	aiController = NULL;
}
mob::~mob() {
	if (aiController) delete aiController;
}


void  mob::setID(int val) {
	ID = val;
}
int  mob::getID() {
	return ID;
}

void mob::setName(std::string name) {
	this->name = name;
}
std::string mob::getName() {
	return name;
}

void mob::setSpeed(float newSpeed) {
	speed = newSpeed;
}

float mob::getSpeed() {
	return speed;
}

float mob::getKnockbackSpeed() {
	return knockbackSpeed;
}
	void mob::setKnockbackSpeed( float newSpeed) {
		knockbackSpeed = newSpeed;
	}

bool mob::isFalling() {
	return _isFalling;
}
void mob::fall() {
	_isFalling = true;

}
void mob::stopFalling() {
	_isFalling = false;
}

void mob::readCombatData(RakNet::BitStream &data) {
	this->::combatEntity::readCombatData(data);
	int bufi;
	data.Read<int>(bufi);
	this->setID(bufi);
	RakNet::RakString buf;
	data.Read<RakNet::RakString>(buf);
	setName(buf.C_String());
	data.Read<float>(speed);
	data.Read<bool>(_isFalling);
}

void mob::writeCombatData(RakNet::BitStream &data) {
	this->::combatEntity::writeCombatData(data);

	data.Write<int>(this->getID());
	data.Write<RakNet::RakString>(RakNet::RakString(getName().c_str()));
	data.Write<float>(speed);
	data.Write<bool>(_isFalling);
}

