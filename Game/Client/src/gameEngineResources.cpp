// ----------------------------------------------------------------------
// gameEngineResources.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Handles the resources for the game. 
*/
// ------------------------------------------------------------------------



#include "gameEngineResources.h"
#include <string>
#include <fstream>


namespace gameEngine {

		resourceManager::managedResourcePack		resources::graphics; //The pack containing graphics
		resourceManager::managedResourcePack		resources::audio; //The pack containing audio
		resourceManager::managedResourcePack		resources::fonts; //The pack containing fonts
		resourceManager::managedResourcePack		resources::data; //The pack containing binary data (values)

		void resources::initialize() {//Initialize the resources

				graphics.load(std::string(ASSET_LOCATION)+RESOURCE_FILE_GRAPHICS); //Load the graphics package
				audio.load(std::string(ASSET_LOCATION)+RESOURCE_FILE_AUDIO); //Load the graphics package
				fonts.load(std::string(ASSET_LOCATION)+RESOURCE_FILE_FONTS); //Load the fonts package
				data.load(std::string(ASSET_LOCATION)+RESOURCE_FILE_DATA); //Load the data package

		}
}



