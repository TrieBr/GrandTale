/*
Handles a map. Has a handle to the data, and also handles rendering, etc.

*/

#include "mapData.h"
#ifndef _H_MAPHANDLER
#define _H_MAPHANDLER

class mapHandler {

public:
	mapHandler();
	~mapHandler();
	void loadMap(int mapID);
	void render(float x, float y, float w = 800, float h = 600);
	mapData *mData; //Map data

private:
	


};

#endif