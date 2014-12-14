#include "iconManager.h"
#include <sstream>
std::map<int,ALLEGRO_BITMAP*> iconManager::preloadedIcons;

 ALLEGRO_BITMAP* iconManager::fetchIcon(int ind){ //Load an Icon
	 if (preloadedIcons.find(ind)==preloadedIcons.end()) {
		 std::stringstream bufferName;
		 bufferName << ":items:icons:" << ind << ".png";
		ALLEGRO_BITMAP* ret = gameEngine::resources::graphics.loadBitmap(bufferName.str());
		 preloadedIcons[ind] = ret;
		 return ret;
	 }else{
		 return preloadedIcons.find(ind)->second;
	 }
}
	
void iconManager::cleanup(){ //Clrenaup any remaining  icons

}
