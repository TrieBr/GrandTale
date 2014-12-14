// ----------------------------------------------------------------------
// gameEngineResources.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Handles the resources for the game. 
*/
// ------------------------------------------------------------------------



#include <allegro5/allegro.h>
#include "gameEngineLogger.h"
#include "resourcePack.h"
#include "settings.h"


#ifndef _H_GAMEENGINERESOURCES_
#define _H_GAMEENGINERESOURCES_

namespace gameEngine {
	class resources
	{
	public:
		static void initialize(); //Initialize the resources
		static resourceManager::managedResourcePack graphics; //The pack containing graphics
		static resourceManager::managedResourcePack audio; //The pack containing audio
		static resourceManager::managedResourcePack fonts; //The pack containing fonts
		static resourceManager::managedResourcePack data; //The pack containing binary data (values)
	private:

	};
}



#endif