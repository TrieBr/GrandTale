// ----------------------------------------------------------------------
// main.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Main application entry point
*/
// ------------------------------------------------------------------------

/*
#include "loginServer.h"
#include "gameServer.h"
#include <allegro5/allegro.h>
#include "gameEngineResources.h"

int main(int argc, char* argv[]) {

	al_init();

	resourceManager::resourcePack::initializeAllegroInterface();
	gameEngine::resources::data.load("Data.gtd"); //Load the graphics package

	loginServer mainLoginServer; //Create the main login server
	mainLoginServer.initialize(1337, 1338); //Initialize the login server
	gameServer mainGameServer;
	mainGameServer.initialize(1339,"127.0.0.1",1338,"Azurai_Beta"); //Start up the game server, and connect to the login server
	
	gameServer mainGameServer2;
	mainGameServer2.initialize(1340,"127.0.0.1",1338,"Azurai_Beta2"); //Start up the game server, and connect to the login server


	while (1)
	{
		if (mainLoginServer.handle()==false) {
			break; //Break the loop
		}
		if (mainGameServer.handle()==false) {
			break; //Break the loop
		}
		if (mainGameServer2.handle()==false) {
			break; //Break the loop
		}
	}

	mainLoginServer.shutdown(); //Shutdown the login server
    return 0;
}
 */

