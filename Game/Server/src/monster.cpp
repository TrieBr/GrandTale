#include "monster.h"

#include <mob.h>
#include "gameMap.h"

void monster::update(double deltaTime) {
	int performAction = rand() % 4;
	if (performAction<2) {

		int action = rand() % 100;
		if (action<20) {
			setSpeed(0);
			this->getParentMap()->broadcastCombatEntityChanges(this);
		}

		if (action<40 && action >20) {
			setSpeed(1);
			this->getParentMap()->broadcastCombatEntityChanges(this);
		}

		if (action<60 && action >40) {
			setSpeed(-1);
			this->getParentMap()->broadcastCombatEntityChanges(this);
		}
	}
}

