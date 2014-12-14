

#include "tilesetManager.h"
#include <sstream>

	std::map<int, tileset*> tilesetManager::preloadedTilesets; //List of preloaded tilesets


	//TODO: Tiles are not cleaned up when they are not needed anymore. Add a method to clean up tiles


	tileset* tilesetManager::loadTileSet(int ind) { //Load the specified tileset ID

		if (preloadedTilesets.find(ind)==preloadedTilesets.end()) { //If the tileset was not already preloaded..
			tileset* newTileset = new tileset();

			std::stringstream bufferPNG;
			bufferPNG << ":tileset:" << ind << ".png";
			newTileset->bitmap = al_load_bitmap_f(gameEngine::resources::graphics.openSubFile(bufferPNG.str()),".png"); //Load the tileset Image

			std::stringstream bufferData;
			bufferData << ":tileset:" << ind << ".tile";
			ALLEGRO_FILE *tileProperties = gameEngine::resources::graphics.openSubFile(bufferPNG.str(),false); //Open the file that contains the properties
			al_fread(tileProperties,&newTileset->tileWidth,sizeof(short)); //Read the width of the tiles
			al_fread(tileProperties,&newTileset->tileHeight,sizeof(short)); //Read the height of the tiles
			al_fclose(tileProperties); //Close the properties file

			newTileset->tileWidth = 64;
			newTileset->tileHeight = 64;
			newTileset->tilesetID = ind;

			preloadedTilesets[ind] = newTileset; //Add the tileset to the list of preloaded tilesets
			return newTileset; //Return the tileset
		}else{
			return preloadedTilesets[ind]; //Return the preloaded tileset
		}
	}

	
	void tilesetManager::cleanup() { //Cleanup/unload any tilesets that have been loaded
		for (std::map<int, tileset*>::iterator i = preloadedTilesets.begin(); i!=preloadedTilesets.end(); i++) {
			delete i->second;
		}
		preloadedTilesets.clear(); //Clear the map
	}
