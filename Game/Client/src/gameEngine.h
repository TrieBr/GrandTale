// ----------------------------------------------------------------------
// gameEngine.h
//     Copyright � Brad Triebwasser 2010
/* Description:
		Primary backbone of the game. Contains global functions used throughout the game as well has crutial functions for controlling and managing the game.
*/
// ------------------------------------------------------------------------
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "gameEngineLogger.h"
#include "resourcePack.h"
#include "abstractWorld.h"
#include "gameEngineResources.h"
#include "gameEngineFramerate.h"
#include "globalFunctions.h"
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#ifndef _H_GAMEENGINE_
#define _H_GAMEENGINE_

#ifdef _DEBUG

   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG


namespace gameEngine {
	class core
	{
	private:
		static ALLEGRO_EVENT_QUEUE* eventQueue; //Event queue for the engine core (Handles generic events such as closing the display)
		static ALLEGRO_DISPLAY*		display; //The main window/display
		static bool					shutdownFlag; //Is the game engine shutting down?
		static bool allegroInit(); //Initializes the allegro system and drivers.
		static void handleEvents(); //Handle generic allegro events from the core engine
		static void cleanUp(); //Cleans up/deinitializes the engine. This should be used back-end only.
	public:
		static float				mouseX, mouseY;
		static abstractWorld*	currentWorld;
		static bool initialize(); //Initialize the game Engine. Returns true on success, or false on failure.
		static void loop(); // The game loop. This is the backbone of the game, as it is the main game loop that handles updating and rendering.
		static void shutdown(); //Shutdown the game engine.
		static void setCurrentWorld(abstractWorld *newWorld); //Set the current active world
		static ALLEGRO_DISPLAY* getDisplay(); //Get the main display
		template <class T>
		static T* getCurrentWorld() { //Returns the current active gameWorld
			return reinterpret_cast<T*>(currentWorld); //Return the current world
		}
	};
}


#endif