

#include "gameEngineResources.h"
#include <map>

#ifndef _H_BACKGROUNDMANAGER
#define _H_BACKGROUNDMANAGER

class background {
public:
	ALLEGRO_BITMAP *bitmap; //The bitmap for the background
	int id;
	~background() {
		al_destroy_bitmap(bitmap); //Destroy the bitmap
	}
};

class backgroundManager {
public:
	static background* loadBackground(int ind); //Load specified background
	static std::map<int,background*> preloadedBackgrounds; //Preloaded backgrounds
	static void cleanup(); //Clrenaup any remaining backgrounds

};

#endif