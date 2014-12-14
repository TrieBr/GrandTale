#include "abstractSkillHandler.h"
#include "gameMap.h"
#ifndef _H_SKILLH_1
#define _H_SKILLH_1

class skillHandler_1 : public abstractSkillHandler{
public:
	skillHandler_1() {
		this->setLevel(1);
		this->setCooldown(120);
		this->skillState = 0;
	}
	virtual bool canExecuteSkill() { return true; }
	virtual void executeSkill() {
		std::vector<combatEntity*> hit = this->getCaster()->getParentMap()->getCombatEntitiesInArea(this->getCaster()->getX(),this->getCaster()->getY(),200);
		hitData h;
		h.damage = 10;
		
		for (unsigned int i=0; i<hit.size(); i++) {
			if (hit[i]->getX()>this->getCaster()->getX())
					h.direction = HIT_DIRECTION_FROM_LEFT;
			else
				h.direction = HIT_DIRECTION_FROM_RIGHT;
			attackController::entityDamage(this->getCaster(),hit[i],h);
		}
	}

};

#endif