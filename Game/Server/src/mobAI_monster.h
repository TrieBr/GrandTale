#include <mob.h>
#include "mobAI.h"
#include <mapCollisionData.h>
#include "collisionCheck.h"

class mobAI_monster : public mobAI {
public:
	mobAI_monster();
	void update(mob* m, double deltaTime);

	void setPlatform(collisionLine* line) { platform = line; }

private:
	double timeSinceLastAction;
	collisionLine* platform;
};