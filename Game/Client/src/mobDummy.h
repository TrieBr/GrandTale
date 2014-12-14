#include <mob.h>
#include "abstractEntity.h"


#ifndef _H_MOBDUMMY
#define _H_MOBDUMMY


namespace worlds {
	class worldGameMap;
};

class mobDummy : public mob, public gameEngine::abstractEntity {
public:
    mobDummy() : mob() {}
    ~mobDummy() {}
    virtual void update(double deltaTime) {}
	worlds::worldGameMap* getParentMap() { return parentMap; }
	void setParentMap(worlds::worldGameMap* map) { parentMap = map; }


private:
	worlds::worldGameMap* parentMap;


};

#endif