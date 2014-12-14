#include "monsterRenderer.h"


monsterRenderer::monsterRenderer() {
	currentFrame = 0;
	currentType = MONSTER_ANIM_IDLE;
	finishedAnimation = true;
	frameTimeAccumulator = 0;
}
monsterRenderer::~monsterRenderer() {
	animationSet->referenceCount--;
	monsterImageManager::garbageCollect();
}
void monsterRenderer::load(int monsterID) {
	animationSet = monsterImageManager::getAnimationSet(monsterID);
}
void monsterRenderer::playAnimation(MonsterAnimationType type, bool loop) {
	finishedAnimation = false;
	this->loop = loop;
	currentFrame=0;
	currentType = type;
	frameTimeAccumulator = 0;
}
void monsterRenderer::updateAnimation(double deltaTime) {
	if (finishedAnimation) return;

	frameTimeAccumulator += ((double)1/(60))*deltaTime;
	if (frameTimeAccumulator>=animationSet->animatedImages[currentType]->frameTime) {
		currentFrame++;
		frameTimeAccumulator = 0;
	}
	if (currentFrame==animationSet->animatedImages[currentType]->frames.size()) {
		if (loop) { currentFrame = 0; return; }
		finishedAnimation = true;
	}
}

void monsterRenderer::render(float X, float Y, bool flip) {

	monsterAnimatedImageFrame *frame = animationSet->animatedImages[currentType]->frames[currentFrame];
	al_draw_bitmap(frame->frameImage,X-frame->originX ,Y-frame->originY,flip ? ALLEGRO_FLIP_HORIZONTAL : 0);
}