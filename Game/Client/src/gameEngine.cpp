// ----------------------------------------------------------------------
// gameEngine.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
		Primary backbone of the game. Contains global functions used throughout the game as well has crutial functions for controlling and managing the game.
*/
// ------------------------------------------------------------------------

#include "gameEngine.h"
#include "gameServer.h"
#include "globalData.h"

namespace gameEngine {

	ALLEGRO_EVENT_QUEUE*	core::eventQueue;  //The generic event queue for the engine core.
	ALLEGRO_DISPLAY*		core::display; //The main window/display
	bool					core::shutdownFlag; //Flag saying that we need to shutdown at the end of the current loop
	abstractWorld*			core::currentWorld; //The current active game world
	float					core::mouseX, core::mouseY;
	bool core::initialize() {//Initialize the game Engine. Returns true on success, or false on failure.
		shutdownFlag = false; //set the shutdown flag to false
		currentWorld = NULL; //Set the current world to NULL
		resourceManager::resourcePack::initializeAllegroInterface(); //Initialize the allegro interface for the resourcePack
		gameEngine::resources::initialize(); //Initialize the resource Packs
		gameEngine::logger::initialize(); //Initialize the Logger
		if (gameEngine::core::allegroInit()) { //If allegro sucessfully initialized
			gameEngine::core::eventQueue =  al_create_event_queue(); //Create a new event queue
			al_register_event_source(gameEngine::core::eventQueue,al_get_display_event_source(core::display)); //Register the main display as an event source for the general queue.
		}
		gameEngine::framerate::initializeFPSRenderer(); //Initialize the FPS renderer
		globalData::initializeItemManager(); //Initialize items
		globalData::initializeSkillManager(); //Initialize skills
		return true; //Sucessful initializtion

	}

	void core::loop() { // The game loop. This is the backbone of the game, as it is the main game loop that handles updating and rendering.
		while (1){
			gameEngine::framerate::calculateFramerate(); //Calculate the framerate
			gameEngine::core::handleEvents(); //Handle generic events such as closing the display
			if (shutdownFlag) { //If the engine is shutting down
				cleanUp(); //Clean up/collect garbage
				break; //Break out the the game loop
			}
			al_clear_to_color(al_map_rgb(33,33,33)); //Clear the color

			ALLEGRO_MOUSE_STATE mState; //Mouse state
			al_get_mouse_state(&mState); //Get the state of the mouse
			mouseX = mState.x;
			mouseY = mState.y;

			if (currentWorld!=NULL) { //If the current world is not NULL
				//currentWorld->update(gameEngine::framerate::deltaTime); //update the world
				
				static double accumulatedTime = 0;
				accumulatedTime += gameEngine::framerate::deltaTime;
				const double fixedFrameTime = 1/framerate::targetFramerate;
				while( accumulatedTime > fixedFrameTime )
				{
				  accumulatedTime -= fixedFrameTime;
				 currentWorld->update(fixedFrameTime); //update the world
				}


			}

			if (currentWorld!=NULL) { //If the current world is not NULL
				currentWorld->render(0,0); //Render the world
			}
			gameEngine::framerate::renderFPS(); //Render the framerate
			al_flip_display(); //Flip the display
			//al_rest(0.0005);
		}
	}

	void core::handleEvents() { //Handle generic allegro events from the core engine
		ALLEGRO_EVENT ev; //Event buffer
		if (al_get_next_event(gameEngine::core::eventQueue, &ev)) { //If an event was on the queue
			if (ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE) { //If the display was closed
				gameEngine::logger::logStream << "Game display closed via close button." << endl;
				shutdown();
			}
		}
	}

	bool core::allegroInit() {
		if (!al_init()){//The allegro initialization failed.
			return false; //Initialization failed.
		}
		logger::logStream << "Initialized Allegro Version " << ALLEGRO_VERSION << "." << ALLEGRO_SUB_VERSION << "." << ALLEGRO_WIP_VERSION << endl;

                al_set_new_display_flags(ALLEGRO_OPENGL_3_0);
		core::display = al_create_display(800,600); //Create the main display
		
		if (core::display==NULL){ //Display failed to initialize
			return false;
		}
		al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_VIDEO_BITMAP);
		if (!al_init_image_addon()){ //Initialize image i/o addon
			return false;
		}
		/*if (!al_install_audio()){ //Initialize sound subsystem
			return false;
		}
		if (!al_init_acodec_addon()){ //Initialize audio codec
			return false;
		}
         */
		al_init_font_addon();
		if (!al_init_ttf_addon()) { //Initialize ttf addon
			return false;
		}
		if (!al_init_primitives_addon()) { //Initialize primitives
			return false;
		}
		if (!al_install_keyboard()) { //Initialize keyboard
			return false;
		}
		if (!al_install_mouse()) { //Install the mouse
			return false;
		}
		return true;
	}

	void core::shutdown() { //Shutdown the game engine.
		shutdownFlag = true; // Set the shutdown flag so we shutdown at the end of the current loop.
	}

	void core::cleanUp() { //Cleans up/deinitializes the engine. This should be used back-end only.
		if (currentWorld!=NULL) {//If a current world is active
			currentWorld->cleanup(); //Cleanup the current world
			delete currentWorld; //Delete the current world
		}
		globalData::cleanupItemManager(); //cleanup items
		globalData::cleanupSkillManager(); //cleanup skills

		networking::gameServer::disconnect();

		gameEngine::framerate::cleanupFPSRenderer(); //Clean up the fps renderer

		gameEngine::resources::audio.cleanUp();
		gameEngine::resources::data.cleanUp();
		gameEngine::resources::fonts.cleanUp();
		gameEngine::resources::graphics.cleanUp();

	
		al_uninstall_mouse();
		al_uninstall_keyboard();
		al_shutdown_primitives_addon();
		al_shutdown_ttf_addon();
		al_shutdown_font_addon();

		//al_uninstall_audio();
		al_shutdown_image_addon();
		al_destroy_display(core::display);
		al_uninstall_system();
		


	}

	void core::setCurrentWorld(abstractWorld *newWorld) {
		if (currentWorld!=NULL) {//If the current world is not NULL, clean it up and delete it
			currentWorld->cleanup(); //Cleanup the current world
			delete currentWorld; //Delete the current world
		}
		currentWorld = newWorld; //Set the new world
		currentWorld->initialize(); //Initialize the new world
	}

	ALLEGRO_DISPLAY* core::getDisplay() { //Get the main display
		return gameEngine::core::display; //Return the display
	}



}





