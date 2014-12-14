#include "mapData.h"
#include "collisionCheck.h"


mapData::mapData()  : mapCollisionData()  {

}

mapData::~mapData(){ //Clean up tiles..

for (unsigned int i=0; i<this->tileLayers.size(); i++) { //For each layer
		for (unsigned int j=0; j<this->tileLayers[i]->layouts.size(); j++) { //For each layout
			for (unsigned int t=0; t<this->tileLayers[i]->layouts[j]->tilePositions.size(); t++) { //For each tile
				delete this->tileLayers[i]->layouts[j]->tilePositions[t]; //Delete tile data
			}
			delete this->tileLayers[i]->layouts[j]; //Delete layout data
		}
		delete this->tileLayers[i]; //Delete layer
	}



}


void mapData::loadMapData(ALLEGRO_FILE* fileStream) { //Load all the tiles, blocks, etc
		
		unsigned int offset_tile = 0;
		unsigned int offset_background = 0;
		al_fseek(fileStream,2*sizeof(int),ALLEGRO_SEEK_SET);
		al_fread(fileStream,&offset_tile,sizeof(int));
		al_fread(fileStream,&offset_background,sizeof(int));

		al_fseek(fileStream,offset_tile,ALLEGRO_SEEK_SET);
		int layerList;
		al_fread(fileStream,&layerList,sizeof(int)); //Read number of layers
		for (unsigned int i=0; i<layerList; i++) {
			tileLayer* newLayer = new tileLayer(); //Create the layer
			int layoutList;
				al_fread(fileStream,&layoutList,sizeof(int)); //Read number of layouts
				for (unsigned int j=0; j <layoutList; j++) {
					tileLayout* newLayout = new tileLayout();
					short tileSetID;
					al_fread(fileStream,&tileSetID,sizeof(short)); //Read ID of tileset
						newLayout->tilesetData = tilesetManager::loadTileSet(tileSetID); //Load the tileset
					int tileList;
					al_fread(fileStream,&tileList,sizeof(int)); //Read number of tiles
					for (unsigned int c=0; c<tileList; c++) {
						tile* newTile = new tile();
						al_fread(fileStream,&newTile->mapX,sizeof(int));
						al_fread(fileStream,&newTile->mapY,sizeof(int));
						al_fread(fileStream,&newTile->tileSetX,sizeof(short));
						al_fread(fileStream,&newTile->tileSetY,sizeof(short));
							newLayout->tilePositions.push_back(newTile);
					}
						newLayer->layouts.push_back(newLayout);
				}

					tileLayers.push_back(newLayer);
		}

		al_fseek(fileStream,offset_background,ALLEGRO_SEEK_SET);

		//Backgrounds
		int backgroundLayerCount = 0;
		al_fread(fileStream,&backgroundLayerCount,sizeof(int));
		for (unsigned int i=0; i<backgroundLayerCount; i++) {
			mapBackground* newBg = new mapBackground;
			int BGID;
			al_fread(fileStream,&BGID,sizeof(int)); //Read end of line
			al_fread(fileStream,&newBg->xPos,sizeof(int)); //Read end of line
			al_fread(fileStream,&newBg->yPos,sizeof(int)); //Read end of line
				newBg->bgHandle = backgroundManager::loadBackground(BGID);
				backgroundLayers.push_back(newBg);
		}

	this->::mapCollisionData::loadMapData(fileStream);

}
