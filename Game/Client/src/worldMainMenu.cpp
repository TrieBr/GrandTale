// ----------------------------------------------------------------------
// worldMainMenu.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	The main menu that handles initial loading, connecting, login, server select, character creation, character selection, and connecting to the game.
*/
// ------------------------------------------------------------------------


#include "worldMainMenu.h"
#include "entityLoginPanel.h"
#include "entityErrorBox.h"
#include "loginServer.h"
#include "gameServer.h"
#include "mainMenuPanelTransition.h"
namespace worlds {

	void worldMainMenu::initialize() {
		this->::gameEngine::abstractWorld::initialize();
		showingError = false;
		al_hide_mouse_cursor(gameEngine::core::getDisplay()); //Hide the system mouse
		al_register_event_source(this->eventQueue,al_get_mouse_event_source()); //Register the mouse events

		background = gameEngine::resources::graphics.loadBitmap(":loadScreen:bg1.png"); //Load the main background bitmap
		logo =  gameEngine::resources::graphics.loadBitmap(":loadScreen:logo.png"); //Load the logo bitmap
		cursor = gameEngine::resources::graphics.loadBitmap(":cursor.png"); //Load the logo bitmap

		/*al_restore_default_mixer(); //Load the default mixer that allegro provides
		backgroundMusic = al_load_audio_stream_f(gameEngine::resources::audio.openSubFile(":mainMenu:BGMusic.ogg", false),".ogg",200,20); //Load the main menu background music
		al_set_audio_stream_playmode(backgroundMusic,ALLEGRO_PLAYMODE_LOOP); //set the audio to LOOP
		al_attach_audio_stream_to_mixer(backgroundMusic,al_get_default_mixer()); //Attatch the audio to the default mixer
		*/
		
		
		

		networking::loginServer::connect(SERVERIP,SERVERPORT); //Connect to the login server
		networking::loginServer::parentWorld = this; //Set the parent world to this world
		
		loginPanel = new entities::mainMenu::entityLoginPanel();
		serverSelect = NULL;
		characterSelect = NULL;
		characterCreate = NULL;
		this->addEntity(loginPanel); //Add the login panel
	}

	void worldMainMenu::update(double _timeFactor) {
		this->::gameEngine::abstractWorld::update(_timeFactor); 
		networking::loginServer::handle(); //Handle a step for the loginServer handler
		if (networking::gameServer::parentWorld==this) {
			networking::gameServer::handle(); //Handle game server if it's parent is set to us
		}
		
	}

	void worldMainMenu::cleanup() {
		networking::loginServer::disconnect(); //Disconnect from the login server

		//al_destroy_audio_stream(backgroundMusic);
		al_hide_mouse_cursor(gameEngine::core::getDisplay()); //Show the mouse again
		this->::gameEngine::abstractWorld::cleanup();
	}
	void worldMainMenu::render(float offsetX, float offsetY) { //Render the world
		al_draw_bitmap(background,0,0,0);
		

		this->::gameEngine::abstractWorld::render();

		al_draw_bitmap(logo,217,0,0);

		ALLEGRO_MOUSE_STATE mState; //Mouse state
		al_get_mouse_state(&mState); //Get the state of the mouse
		al_draw_bitmap(cursor,mState.x,mState.y,0);

	}



	//TODO: Make the panels destroy when they are transitioned off, and create them when they are transitioned on

	void worldMainMenu::showError(std::string errorText) { //Show an error using the custom error box
		if (showingError==false) { //If an error is not already showing
			entities::mainMenu::entityErrorBox *newErrorBox = new entities::mainMenu::entityErrorBox(errorText); //Create the error box entity
			addEntity(newErrorBox); //Add the entity to our list
			showingError = true; //We are now displaying an error
		}
	}

		void worldMainMenu::loginToServerSelect() {
			this->loginPanel->panelTransition.flyOut(this->loginPanel->x,this->loginPanel->x-1000);
			loginPanel->usernameBox->focus(false);
			loginPanel->passwordBox->focus(false);
			if (serverSelect==NULL) { //If the server select hasnt been created yet..
				serverSelect = new entities::mainMenu::entityServerSelect();
				addEntity(serverSelect);
			}
			serverSelect->panelTransition.flyOut(1000,277);
		}

		void worldMainMenu::serverSelectToLogin() {
			this->loginPanel->panelTransition.flyOut(this->loginPanel->x,277);
		serverSelect->panelTransition.flyOut(serverSelect->x,serverSelect->x+1000);
		}

		void worldMainMenu::serverSelectToCharSelect() {
			this->serverSelect->panelTransition.flyOut(this->serverSelect->x,this->serverSelect->x-1000);
			if (characterSelect==NULL) { //If the server select hasnt been created yet..
				characterSelect = new entities::mainMenu::entityCharacterSelect();
				addEntity(characterSelect);
			}
			characterSelect->zeroSlots();
			characterSelect->panelTransition.flyOut(1000,107);
		}

		void worldMainMenu::charSelectToServerSelect() {
			this->serverSelect->panelTransition.flyOut(this->serverSelect->x,277);
			characterSelect->panelTransition.flyOut(characterSelect->x,characterSelect->x+1000);
		}

		void worldMainMenu::charCreateToCharSelect() {
			this->characterSelect->panelTransition.flyOut(this->characterSelect->x,107);
			characterSelect->zeroSlots();
			characterCreate->panelTransition.flyOut(characterCreate->x,characterCreate->x+1000);
			characterCreate->characterNameTextBox->focus(false);
		}
		void worldMainMenu::charSelectToCharCreate() {
			this->characterSelect->panelTransition.flyOut(this->characterSelect->x,this->characterSelect->x-1000);
				
			if (characterCreate==NULL) { //If the server select hasnt been created yet..
				characterCreate = new entities::mainMenu::entityCharacterCreation();
				addEntity(characterCreate);
			}
			characterCreate->panelTransition.flyOut(1000,107);
		}

}