

#include "gameEngineResources.h"
#include <map>

#ifndef _H_TILESETMANAGER
#define _H_TILESETMANAGER

class tileset {
public:
	ALLEGRO_BITMAP *bitmap;
	short tileWidth;
	short tileHeight;
	short tilesetID; //ID for the tileset

	~tileset() { //Destructor
		al_destroy_bitmap(bitmap); //Destroy/cleanup the tileset bitmap
	}

};

class tilesetManager {
public:
	static tileset* loadTileSet(int ind); //Load the specified tileset ID
	static std::map<int, tileset*> preloadedTilesets; //List of preloaded tilesets
	static void cleanup(); //Cleanup/unload any tilesets that have been loaded
};

#endif