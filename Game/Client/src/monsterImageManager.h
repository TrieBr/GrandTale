#include "gameEngine.h"
#include <map>
#include <vector>


#ifndef _H_MONSTERIMAGEMANAGER
#define _H_MONSTERIMAGEMANAGER

enum MonsterAnimationType {
	MONSTER_ANIM_ATTACK,
	MONSTER_ANIM_DEAD,
	MONSTER_ANIM_DYING,
	MONSTER_ANIM_HIT,
	MONSTER_ANIM_IDLE,
	MONSTER_ANIM_RUN,
	MONSTER_ANIM_COUNT
};

struct monsterAnimatedImageFrame {
	ALLEGRO_BITMAP* frameImage;
	int originX;
	int originY;
};

struct monsterAnimatedImage {
	std::vector<monsterAnimatedImageFrame*> frames;
	int animationFPS; //Frames per second
	double frameTime; //Length per frame
};

struct monsterAnimationSet {
	std::vector<monsterAnimatedImage*> animatedImages;
	int referenceCount;
};


class monsterImageManager {
public:
	static monsterAnimationSet* getAnimationSet(int monsterID);
	static monsterAnimatedImage* getAnimatedImage(int monsterID, MonsterAnimationType type);
	static void garbageCollect();
private:
	static std::map<int,monsterAnimationSet*> imageCache;


};

#endif