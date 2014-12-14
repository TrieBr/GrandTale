#include "mapSaver.h"


	mapSaver::mapSaver (mapData &mData) {
		setData(mData);
	}
	void mapSaver::setData(mapData &mData) {
		_mData = mData;
	}
	void mapSaver::writeData(ALLEGRO_FILE* fileStream) {

		unsigned int offset_settings = 0;
		unsigned int offset_collision = 0;
		unsigned int offset_tile = 0;
		unsigned int offset_background = 0;

		//Reserve room for the header
		for (unsigned int i=0; i<4*sizeof(unsigned int); i++) {
			al_fputc(fileStream,0);
		}


		offset_settings = al_ftell(fileStream);
		//Write map dimensions
		al_fwrite(fileStream,&_mData.left,sizeof(int)); //Write position on map
		al_fwrite(fileStream,&_mData.top,sizeof(int)); //Write position on map
		al_fwrite(fileStream,&_mData.right,sizeof(int)); //Write position on map
		al_fwrite(fileStream,&_mData.bottom,sizeof(int)); //Write position on map


		offset_collision = al_ftell(fileStream);
		int collisionLineList = _mData.getCollisionLineCount();
		al_fwrite(fileStream,&collisionLineList, sizeof(int)); //Write number of collision lines
		for (collisionLineListNode* i = _mData.getRootCollisionLine(); i!=NULL; i=i->next) { //Iterate through all the lines
			int buffer;
			buffer = i->line->p1.x;
			al_fwrite(fileStream,&buffer,sizeof(int)); //Line beginning
			buffer = i->line->p1.y;
			al_fwrite(fileStream,&buffer,sizeof(int)); //Line beginning
			buffer = i->line->p2.x;
			al_fwrite(fileStream,&buffer,sizeof(int)); //Line end
			buffer = i->line->p2.y;
			al_fwrite(fileStream,&buffer,sizeof(int)); //line end
			al_fwrite(fileStream,&i->line->jumpthrough,sizeof(bool)); //jumpthrough?
		}

		offset_tile = al_ftell(fileStream);
		int layerList = _mData.tileLayers.size();
		al_fwrite(fileStream,&layerList, sizeof(int)); //Write number of tile Layers
		for (unsigned int i=0; i<_mData.tileLayers.size(); i++) {
			int layoutList = _mData.tileLayers[i]->layouts.size();

			al_fwrite(fileStream, &layoutList, sizeof(int)); //Write number of layouts.
			for (unsigned int j=0; j<layoutList; j++) {
				int tileList = _mData.tileLayers[i]->layouts[j]->tilePositions.size();
				al_fwrite(fileStream,&_mData.tileLayers[i]->layouts[j]->tilesetData->tilesetID, sizeof(short)); //Write ID of tileset
				al_fwrite(fileStream,&tileList, sizeof(int)); //Number of tiles
				for (unsigned int c=0; c<tileList; c++) {
					al_fwrite(fileStream,&_mData.tileLayers[i]->layouts[j]->tilePositions[c]->mapX,sizeof(int)); //Write position on map
					al_fwrite(fileStream,&_mData.tileLayers[i]->layouts[j]->tilePositions[c]->mapY,sizeof(int)); //Write position on map
					al_fwrite(fileStream,&_mData.tileLayers[i]->layouts[j]->tilePositions[c]->tileSetX,sizeof(short)); //Write position on tileset (pos*width)
					al_fwrite(fileStream,&_mData.tileLayers[i]->layouts[j]->tilePositions[c]->tileSetY,sizeof(short)); //Write position on tileset (pos*height)
				}
			}
		}

		offset_background = al_ftell(fileStream);
		//Background layers
		int LayerCount = _mData.backgroundLayers.size();
		al_fwrite(fileStream,&LayerCount, sizeof(int)); //Write number of background layers
		for (int i=0; i<_mData.backgroundLayers.size(); i++) {
			int buffer;
			buffer = _mData.backgroundLayers[i]->bgHandle->id;
			al_fwrite(fileStream,&buffer,sizeof(int)); //BG ID
			buffer = _mData.backgroundLayers[i]->xPos;
			al_fwrite(fileStream,&buffer,sizeof(int)); //x position
			buffer = _mData.backgroundLayers[i]->yPos;
			al_fwrite(fileStream,&buffer,sizeof(int)); //Y position
		}
		al_fseek(fileStream,0,ALLEGRO_SEEK_SET);

		al_fwrite(fileStream,&offset_settings,sizeof(int)); //Write position on map
		al_fwrite(fileStream,&offset_collision,sizeof(int)); //Write position on map
		al_fwrite(fileStream,&offset_tile,sizeof(int)); //Write position on map
		al_fwrite(fileStream,&offset_background,sizeof(int)); //Write position on map
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