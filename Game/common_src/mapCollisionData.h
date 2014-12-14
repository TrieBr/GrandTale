/*
Contains data for a map (eg. Tile Locations, Barricades, spawn points, portals, etc..

*/

#include <geometry.h>
#include <vector>
#include <allegro5/allegro.h>

#ifndef _H_MAPCOLLISIONDATA
#define _H_MAPCOLLISIONDATA


class collisionLine : public lineSeg {
public:
	collisionLine() { jumpthrough = false; }
	bool jumpthrough;

};

struct collisionLineListNode {
	collisionLine* line;
	collisionLineListNode* prev;
	collisionLineListNode* next;
};

class mapCollisionData {
private:
	
public:
	~mapCollisionData();
	mapCollisionData();
	void loadMapData(ALLEGRO_FILE* fileStream); //Load all the tiles, blocks, etc

	collisionLineListNode* rootNode; //The root node. (prev points to last node on circular chain)


	int getCollisionLineCount();
	collisionLineListNode* getRootCollisionLine();
	void addCollisionLine(collisionLine* newLine); //Adds a collision line
	void removeCollisionLine(collisionLine* line); //Removes a collision line
	int getWidth() { return right-left; }
	int getHeight() { return bottom-top; }
	int left, top, right, bottom; //Bounds of the map
};

#endif