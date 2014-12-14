#include <string>
#include <stats.h>
#include <combatEntity.h>

#ifndef _H_MOB
#define _H_MOB



class mobAI;
class mob : public combatEntity {
public:
	mob();
	~mob();

	void setID(int val);
	int getID();
	void setName(std::string name);
	std::string getName();

	virtual void update(double deltaTime) {}
	void setAIController(mobAI* controller) { aiController  = controller; }
	mobAI* getAIController() { return aiController; }
	float getSpeed();
	void setSpeed( float newSpeed);
	float getKnockbackSpeed();
	void setKnockbackSpeed( float newSpeed);
	bool isFalling();
	void fall(); 
	void stopFalling();
	virtual void readCombatData(RakNet::BitStream &data);
	virtual void writeCombatData(RakNet::BitStream &data);

	virtual void stateChanged() {} 
private:

	//Static IDof the mob
	int ID;
	
	//name of the mob
	std::string name;

	float speed; //Speed of the mob, negative value for left.
	float knockbackSpeed;
	bool _isFalling; //Is the mob falling?

	mobAI* aiController;
};

#endif