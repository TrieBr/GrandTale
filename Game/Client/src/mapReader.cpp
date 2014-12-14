

#include "mapReader.h"


mapReader::mapReader(mapData *mData, int optionFlags) {
	setData(mData);
	setOptions(optionFlags);
}

void mapReader::setOptions(int optionFlags) {
	this->options = optionFlags;
}
void mapReader::setData(mapData *mData) {
	_mData = mData;
}
void mapReader::readData(ALLEGRO_FILE* fileStream){


	//Read map dimensions
	al_fread(fileStream,&this->_mData->left,sizeof(int)); //Read start of line
	al_fread(fileStream,&this->_mData->top,sizeof(int)); //Read start of line
	al_fread(fileStream,&this->_mData->right,sizeof(int)); //Read start of line
	al_fread(fileStream,&this->_mData->bottom,sizeof(int)); //Read start of line

	
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
				if (!(options & SKIPTILES)) {
					newLayout->tilesetData = tilesetManager::loadTileSet(tileSetID); //Load the tileset
				}
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
			if (!(options & SKIPTILES)) {
				_mData->tileLayers.push_back(newLayer);
			}else{
				delete newLayer;
			}
	}

	int collisionLineList;
	al_fread(fileStream,&collisionLineList,sizeof(int));
	for (unsigned int i=0; i<collisionLineList; i++) {
		collisionLine* newCLine = new collisionLine();

		int buffer;
		al_fread(fileStream,&buffer,sizeof(int)); //Read start of line
		newCLine->p1.x = buffer;
		al_fread(fileStream,&buffer,sizeof(int)); //Read start of line
		newCLine->p1.y = buffer;
		al_fread(fileStream,&buffer,sizeof(int)); //Read end of line
		newCLine->p2.x = buffer;
		al_fread(fileStream,&buffer,sizeof(int)); //Read end of line
		newCLine->p2.y = buffer;
		al_fread(fileStream,&newCLine->jumpthrough,sizeof(bool)); //jumpthrough platform?
		_mData->addCollisionLine(newCLine);

	}

	
	//Backgrounds
	int backgroundLayers;
	al_fread(fileStream,&backgroundLayers,sizeof(int));
	for (unsigned int i=0; i<backgroundLayers; i++) {
		mapBackground* newBg = new mapBackground;
		int BGID;
		al_fread(fileStream,&BGID,sizeof(int)); //Read end of line
		al_fread(fileStream,&newBg->xPos,sizeof(int)); //Read end of line
		al_fread(fileStream,&newBg->yPos,sizeof(int)); //Read end of line
		if (!(options & SKIPBACKGROUNDS)) {
			newBg->bgHandle = backgroundManager::loadBackground(BGID);
		}
		if (!(options & SKIPBACKGROUNDS)) {
			_mData->backgroundLayers.push_back(newBg);
		}else{
			delete newBg;
		}
	}
	
	
}



	/*
	INT: Number of layers
	 (Number of layers) {
		INT: Number of layouts
		(Number of layouts) {
			INT:  ID of Tileset
			INT: Number of tiles on this layout
			(Number of tiles on this layout) {
				INT: X position on map
				INT: Y Position on map
				SHORT: x positin on tileset
				SHORT: y position on tileset
			}
		}

	 }



	*/