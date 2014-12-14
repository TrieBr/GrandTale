



#include "gameEngineResources.h"
#include <map>

#ifndef _H_ICONMANAGER
#define _H_ICONMANAGER


class iconManager {
public:
	static ALLEGRO_BITMAP* fetchIcon(int ind); //Load an Icon
	static std::map<int,ALLEGRO_BITMAP*> preloadedIcons;
	static void cleanup(); //Clrenaup any remaining  icons
};

#endif