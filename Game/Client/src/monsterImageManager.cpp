#include "monsterImageManager.h"

std::map<int,monsterAnimationSet*> monsterImageManager::imageCache;

monsterAnimationSet* monsterImageManager::getAnimationSet(int monsterID) {
		std::map<int,monsterAnimationSet*>::iterator i = imageCache.find(monsterID);
		if (i==imageCache.end()) {
			monsterAnimationSet* newSet = new monsterAnimationSet;
			newSet->referenceCount = 1;
			for (int j=0; j<MONSTER_ANIM_COUNT; j++) {
				newSet->animatedImages.push_back(getAnimatedImage(monsterID,(MonsterAnimationType)j));
			}
			return newSet;
		}
		i->second->referenceCount++;
		return i->second;
}

monsterAnimatedImage* monsterImageManager::getAnimatedImage(int monsterID, MonsterAnimationType type) {
	monsterAnimatedImage* newAnimatedImage = new monsterAnimatedImage();

			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
				n= sprintf(buffer,":monsters:%i:%i:anim.dat",monsterID,type);
				dataPath = std::string(buffer,n);
				ALLEGRO_FILE* dataFile = gameEngine::resources::graphics.openSubFile(dataPath);
				unsigned char frameCount, FPS, originX, originY;
				al_fread(dataFile,&frameCount,sizeof(unsigned char));
				al_fread(dataFile,&FPS,sizeof(unsigned char));
				al_fread(dataFile,&originX,sizeof(unsigned char));
				al_fread(dataFile,&originY,sizeof(unsigned char));
				al_fclose(dataFile);
				newAnimatedImage->animationFPS = FPS;
				newAnimatedImage->frameTime = (double)1/(double)FPS;
				for (unsigned char i=0; i<frameCount; i++) {
					monsterAnimatedImageFrame* newFrame = new monsterAnimatedImageFrame();
					n= sprintf(buffer,":monsters:%i:%i:%i.png",monsterID,type,i);
					graphicPath = std::string(buffer,n);
					newFrame->frameImage = al_load_bitmap_f(gameEngine::resources::graphics.openSubFile(graphicPath),".png");
					newFrame->originX = originX;
					newFrame->originY = originY;
					newAnimatedImage->frames.push_back(newFrame);
				}
		return newAnimatedImage;
}

void monsterImageManager::garbageCollect() {
	for(std::map<int,monsterAnimationSet*>::iterator i= imageCache.begin(); i!=imageCache.end(); i++) {
		if (i->second->referenceCount==0) {
			for (unsigned int j = 0; j< i->second->animatedImages.size(); j++) {
				for(unsigned int k = 0; k<i->second->animatedImages[j]->frames.size(); k++) {
					al_destroy_bitmap(i->second->animatedImages[j]->frames[k]->frameImage);
					delete i->second->animatedImages[j]->frames[k];
				}
				delete i->second->animatedImages[j];
			}
			delete i->second;
		}
	}

}