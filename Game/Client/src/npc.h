
#include "mobDummy.h"
#include "characterRenderer.h"
#include <mapCollisionData.h>
#include "gameEngine.h"
#ifndef _H_NPC
#define _H_NPC

class npc : public mobDummy {
public:
	npc();
	~npc();
	void loadRenderer();
	virtual void stateChanged();
	virtual void initialize();
	virtual void cleanup();
	virtual void update(double _timeFactor);
	virtual void render(float offsetX =0, float offsetY =0);
	void setPlatform(collisionLine* line) { platform = line; }
	virtual void readCombatData(RakNet::BitStream &data);
	virtual void writeCombatData(RakNet::BitStream &data);
private:
	character::characterRenderer* cRenderer;
	character::characterCustomization customization;
	bool lastDirectionRight;
	collisionLine* platform;
	ALLEGRO_FONT* namePlateFont;
};

#endif