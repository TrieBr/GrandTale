
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <mapHandler.h>



#include <vector>

class mapEditor;

#define TILEPANELWIDTH 300
enum transitionStatus {
	sFLYOUT,
	sFLYIN,
	sOUT,
	sIN
};

class tileSelector {
public:
	void initialize(); //Initialize the panel
	tileSelector(mapEditor* parentEditor);
	void update(); //Uddate the panel
	void render(); //Render the panel
	void loadTileSets(); //Load all the tile sets
	bool handleEvent(ALLEGRO_EVENT &ev); //Handle an event
	transitionStatus transition; //Transition of panel
	float panelX, panelY;
	float panelW, panelH;
	bool panning;

	//Current selected tile
	float selectedTileX, selectedTileY;
	float selectedTileW, selectedTileH;
	float selectTileW, selectTileH; //The width/height of a tile when we select one

	int currentLayer; //Current layer we are adding tiles to.

	//Stuff for selected tileSET
	std::vector<tileset*>	tileList;
	int selectedTileSet;

	mapEditor *parent; //Parent map editor
private:
	ALLEGRO_BITMAP*			tileSelectCanvas; //USed for displaying tileset/selected tile
	ALLEGRO_EVENT_QUEUE		*eventQueue;
	

	//Panning stuff for the tile selec
	float panStartX, panStartY;
	float panX, panY;
	
	
};
