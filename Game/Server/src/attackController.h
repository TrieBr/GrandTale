#include <combatEntity.h>

#ifndef _H_ATTACKCONTROLLER
#define _H_ATTACKCONTROLLER

class attackController {
public:
	static void entityDamage(combatEntity* src, combatEntity* dest, hitData &data);

};

#endif