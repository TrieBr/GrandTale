// ----------------------------------------------------------------------
// main.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
		Main entry point for the application. This portion shouldn't contain much code, as it should primarily initialize the gameEngine.
*/
// ------------------------------------------------------------------------
#include <allegro5/allegro.h>
#include <allegro5/allegro_android.h>
#include "gameEngine.h"
#include "worldMainMenu.h"
#include <characterClass.h>

#ifdef _WIN32

int YourAllocHook( int allocType, void *userData, size_t size, int blockType, long requestNumber, const unsigned char *filename, int lineNumber);
#endif
extern "C" {
int main(int argc, char **argv) {
    #ifdef _WIN32
	_CrtSetAllocHook(YourAllocHook);
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif
	defaultClassEquipment::InitializeDefaultIDs();
	if (gameEngine::core::initialize()) { //Engine initialized sucessfully
		gameEngine::core::setCurrentWorld(reinterpret_cast<gameEngine::abstractWorld*>(new worlds::worldMainMenu())); //Set the world to the main menu
		gameEngine::core::loop(); //Loop the main game engine.
	}
    return 0;
}

}















#ifdef _WIN32


int YourAllocHook( int allocType, void *userData, size_t size, int blockType, long requestNumber, const unsigned char *filename, int lineNumber) {
	if (allocType==_HOOK_ALLOC)
	{
		if (size==8 && requestNumber>3000)
		{
		return TRUE;
		}
	}

	if (allocType==_HOOK_FREE)
	{
		if (size==208)
		{
			return TRUE;
		}
	}

	return TRUE;
}

#endif