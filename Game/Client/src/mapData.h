/*
Contains data for a map (eg. Tile Locations, Barricades, spawn points, portals, etc..

*/

#include "tilesetManager.h"
#include "backgroundManager.h"
#include "geometry.h"
#include <mapCollisionData.h>

#ifndef _H_MAPDATA
#define _H_MAPDATA

struct tile { //one "tile" placed on the map.
	short tileSetX; //X position of tile in tileset (not exact, but based on width eg. 64x2)
	short tileSetY;	//Y position of tile in tileset (not exact, but based on width eg. 64x2)
	int mapX; //Exact position in map
	int mapY; //Exact position in map
};

struct tileLayout { //A "layout" is one tileset ID that is being used at multiple points
	tileset* tilesetData;
	std::vector<tile*> tilePositions;
};

struct tileLayer { //One layer.. Can consist of multiple tile layouts
	std::vector<tileLayout*> layouts;
};

struct mapBackground {
	background* bgHandle;
	int xPos;
	int yPos;
};



class mapData : public mapCollisionData {
private:
	
public:
	~mapData();
	mapData();
	void loadMapData(ALLEGRO_FILE* fileStream); //Load all the tiles, blocks, etc
	std::vector<tileLayer*>		tileLayers; //List of tile layers.
	std::vector<mapBackground*> backgroundLayers; //List of background layers

};

#endif