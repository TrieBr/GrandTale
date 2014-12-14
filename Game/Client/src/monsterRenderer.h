#include "monsterImageManager.h"

#ifndef _H_MONSTERRENDERER
#define _H_MONSTERRENDERER


class monsterRenderer {
public:
	monsterRenderer();
	~monsterRenderer();
	void load(int monsterID);
	void playAnimation(MonsterAnimationType type, bool loop = false);
	bool isFinishedAnimation() { return finishedAnimation; }
	void updateAnimation(double deltaTime);
	void render(float X, float Y, bool flip = false);
private:
	int currentFrame;
	bool finishedAnimation;
	MonsterAnimationType currentType;
	monsterAnimationSet* animationSet;
	bool loop;
	double frameTimeAccumulator;
	
};

#endif