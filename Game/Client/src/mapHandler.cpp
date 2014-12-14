#include "mapHandler.h"
#include "mapData.h"
#include <sstream>
#include <cmath>
mapHandler::mapHandler() {
	mData = NULL;
}

mapHandler::~mapHandler() {
	if (mData!=NULL) {
		delete mData;
	}
}
void mapHandler::loadMap(int mapID) {
	this->mData = new mapData(); //Create map Data
	std::stringstream mapFormat;
	mapFormat << ":map:" << mapID << ".map";


	ALLEGRO_FILE* mapFileData = gameEngine::resources::data.openSubFile(mapFormat.str().c_str(),false);
	this->mData->loadMapData(mapFileData);


	al_fclose(mapFileData);

}


void mapHandler::render(float x, float y, float w, float h) { //Render the map.
	al_hold_bitmap_drawing(true);
	float hPercent = x/(this->mData->getWidth()-w);
	float vPercent = y/(this->mData->getHeight()-h);
	float Expansion = 50;
	float speed = 20;
	for (unsigned int i=0; i<this->mData->backgroundLayers.size(); i++) {
		al_draw_scaled_bitmap(this->mData->backgroundLayers[i]->bgHandle->bitmap,0,0,
			al_get_bitmap_width(this->mData->backgroundLayers[i]->bgHandle->bitmap),
			al_get_bitmap_height(this->mData->backgroundLayers[i]->bgHandle->bitmap), 
			this->mData->backgroundLayers[i]->xPos-(Expansion/2)+((Expansion/2)*hPercent),
			this->mData->backgroundLayers[i]->yPos-(Expansion/2)+((Expansion/2)*vPercent),
			al_get_bitmap_width(this->mData->backgroundLayers[i]->bgHandle->bitmap)+Expansion,al_get_bitmap_height(this->mData->backgroundLayers[i]->bgHandle->bitmap)+Expansion,0);
		Expansion += 20;
		speed -= 2;
	}


	
	tileLayer* currentLayer;
		tileLayout * currentLayout;
		tile *currentTile;
		for (unsigned int i=0; i<this->mData->tileLayers.size(); i++) { //For each layer
			currentLayer  = this->mData->tileLayers[i];
			for (unsigned int j=0; j<this->mData->tileLayers[i]->layouts.size(); j++) { //For each layout
				currentLayout = this->mData->tileLayers[i]->layouts[j];
				for (unsigned int t=0; t<currentLayout->tilePositions.size(); t++) { //For each tile
					currentTile = currentLayout->tilePositions[t];
					if (currentTile->mapX+x+currentLayout->tilesetData->tileWidth>0 && currentTile->mapX+x-currentLayout->tilesetData->tileWidth<w && currentTile->mapY+y+currentLayout->tilesetData->tileHeight>0 && currentTile->mapY+y-currentLayout->tilesetData->tileHeight<h) {
					al_draw_bitmap_region(currentLayout->tilesetData->bitmap,
						currentTile->tileSetX*currentLayout->tilesetData->tileWidth,
						currentTile->tileSetY*currentLayout->tilesetData->tileHeight,
						currentLayout->tilesetData->tileWidth,
						currentLayout->tilesetData->tileHeight,
						floor(currentTile->mapX+x),
						floor(currentTile->mapY+y),
						0);
					}
				}

			}

		}
		
		al_hold_bitmap_drawing(false);
}