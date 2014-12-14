
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <mapHandler.h>

#include "tileSelector.h"

class mapEditor {
public:
	mapEditor();
	ALLEGRO_DISPLAY *display; //Display the the map editor
	mapHandler		*mHandler; //Handler for handling the map Data and rendering
	void initialize(); 
	void loadMap(int mapID); //Load a map
	void update();
	void render();

	void loadTileSets(); //Load all the tile sets..

	void getGridSnapPositon(int *x, int *y);
	collisionLine* getNearestCollisionLine(int x, int y, int maxDist);
	void saveMap();
	void setCleanMap();

	bool panning; //Are we currently panning?
	float panStartX, panStartY;
	float viewX, viewY; //View position
	tileSelector* tSelector; //Tile Selector

	//Line Placer
	float startX, startY; //Starting position of line drawer
	bool startedLine; //Started drawing the line

	bool placingTile; //Have we clicked to place a tile? Now we need to drag it around
	tile* tileDrag; //Tile to drag around

	int gridW, gridH;
	bool gridEnabled;
	bool drawGrid;
	ALLEGRO_EVENT_QUEUE *eventQueue;
};