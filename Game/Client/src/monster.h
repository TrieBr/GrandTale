
#include "mobDummy.h"
#include "monsterRenderer.h"
#include <mapCollisionData.h>
#ifndef _H_MONSTER
#define _H_MONSTER

class monster : public mobDummy {
public:
	monster();
	~monster();
	void loadRenderer();
	virtual void stateChanged();
	virtual void initialize();
	virtual void cleanup();
	virtual void update(double _timeFactor);
	virtual void render(float offsetX =0, float offsetY =0);
	void setPlatform(collisionLine* line) { platform = line; }
	virtual void hit(hitData &data);
private:
	monsterRenderer* mRenderer;
	bool lastDirectionRight;
	collisionLine* platform;
	ALLEGRO_FONT* namePlateFont;
	bool beingHit;
	float hitAnimationTimer;
	
	
};

#endif