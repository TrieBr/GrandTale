#include <stats.h>
#include <BitStream.h>
#include <combatEntityStats.h>
#include <packetOpCodes.h>
#include <hitData.h>
//Represents an object with health, mana, stats, etc.

#ifndef _H_COMBATENTITY
#define _H_COMBATENTITY

enum CombatEntityType {
	COMBAT_MONSTER,
	COMBAT_NPC,
	COMBAT_PLAYER
};


class gameMap;
class combatEntity : public combatEntityStats {
public:
	void setParentMap(gameMap* map);
	gameMap* getParentMap();
	void setType(CombatEntityType t);
	CombatEntityType getType();
	void setUID(int val);
	int getUID();
	void setX(float val);
	float getX();
	void setY(float val);
	float getY();
	void setCurrentHealth(int val);
	int getCurrentHealth();
	void setCurrentMana( int val);
	int getCurrentMana();
	void setLevel (unsigned char val);
	unsigned char getLevel();
	void setElement(unsigned char val);
	unsigned char getElement();
	void setSize( unsigned char val);
	unsigned char getSize();


	virtual void hit(hitData &data);
	hitData&  getLastHitData();

	virtual void update(double deltaTime) {}
	virtual void recalculateStats()  {} 

	virtual void readCombatData(RakNet::BitStream &data);
	virtual void writeCombatData(RakNet::BitStream &data);
private:
	gameMap* parentMap;
	CombatEntityType type;
	//Unique ID of the mob
	int UID;
	float x;
	float y;
	//Current health of the mob
	int currentHealth;
	//Current mana of the mob
	int currentMana;
	//Level of the mob
	unsigned char level;
	//Type of element of the mob
	unsigned char element;
	//Size of the mob
	unsigned char size;

	hitData lastHitData;

	
};

#endif