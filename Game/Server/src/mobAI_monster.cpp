#include "mobAI_monster.h"
#include "gameMap.h"

mobAI_monster::mobAI_monster() {
	timeSinceLastAction = 0;
	platform = NULL;
}

void mobAI_monster::update(mob* m, double deltaTime) {

	m->setX(m->getX()+(double)m->getSpeed()*deltaTime);

	if (m->getX()>platform->p2.x) { m->setX(platform->p2.x); }
	if (m->getX()<platform->p1.x) { m->setX(platform->p1.x); }
	if (m->isFalling()) {
		
		if (m->getY()>platform->p1.y) {
			m->stopFalling();
			m->getParentMap()->broadcastCombatEntityChanges(m);
		}
		m->setY(m->getY()+2*deltaTime);
	}


	timeSinceLastAction += ((double)1/(double)60)*deltaTime;

	if (timeSinceLastAction>1) {
		timeSinceLastAction = 0;
		int action = rand() % 3;
		if (action==0) {
			m->setSpeed(0);
			m->getParentMap()->broadcastCombatEntityChanges(m);
		}

		if (action==1 && m->getSpeed()==0) {
			m->setSpeed(1);
			m->getParentMap()->broadcastCombatEntityChanges(m);
		}

		if (action==2 && m->getSpeed()==0) {
			m->setSpeed(-1);
			m->getParentMap()->broadcastCombatEntityChanges(m);
		}
	}
}