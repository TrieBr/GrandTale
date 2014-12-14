

#include "backgroundManager.h"
#include <sstream>

std::map<int,background*> backgroundManager::preloadedBackgrounds; //Map of preloaded backgrounds



background* backgroundManager::loadBackground(int ind) { //Load specified background

	if (preloadedBackgrounds.find(ind)==preloadedBackgrounds.end()) { //Background was not previously loaded
		background* newBG = new background(); 
			newBG->id = ind;
			std::stringstream bufferPNG;
			bufferPNG << ":bg:" << ind << ".png";
			newBG->bitmap = al_load_bitmap_f(gameEngine::resources::graphics.openSubFile(bufferPNG.str()),".png"); //Load the background Image

			preloadedBackgrounds[ind] = newBG;
			return newBG;
	}else{
		return preloadedBackgrounds[ind]; //Return preloaded background
	}

}

void backgroundManager::cleanup() {
	for (std::map<int, background*>::iterator i = preloadedBackgrounds.begin(); i!=preloadedBackgrounds.end(); i++) {
			delete i->second;
		}
		preloadedBackgrounds.clear(); //Clear the map
}