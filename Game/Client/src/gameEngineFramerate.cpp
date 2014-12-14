// ----------------------------------------------------------------------
// gameEngineFramerate.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------


#include "gameEngine.h"
#include "gameServer.h"


namespace gameEngine {

			double				framerate::targetFramerate = 60; //The target framerate that the logic should use
			double				framerate::FPS ; //The framerate in frames per second (FPS)
			int					framerate::slowFPS; //The framerate in frames per second, but only updated once per second so it can be read easier
			double				framerate::deltaTime; //Delta time factor
			ALLEGRO_FONT*		framerate::FPSRenderFont; //Font used for rendering the fps
			ALLEGRO_USTR*		framerate::FPSText; //The text that has the FPS

			double				framerate::lastFrameTime; //Used for calculating framerate; contains the time the last frame was rendered
			double				framerate::lastSlowFPSUpdate; //Last time the slowFPS variable was updated

			void framerate::calculateFramerate() { //Calculate the framerate. This should be called every step of the game loop
				FPS = 1/((al_get_time()-lastFrameTime)); //Calculate the FPS
				if (al_get_time()-lastSlowFPSUpdate>1)
				{
					slowFPS = FPS;
					al_ustr_free(FPSText);
					FPSText = al_ustr_newf("%i",slowFPS);
					lastSlowFPSUpdate = al_get_time();
				}
			
				deltaTime = ((double)(targetFramerate/FPS));

				lastFrameTime = al_get_time();

			}

			void framerate::initializeFPSRenderer() { //Initializes the font renderer
				FPSRenderFont = gameEngine::resources::fonts.loadFont(":debug:arial.ttf",-10,ALLEGRO_TTF_MONOCHROME);
				FPSText = al_ustr_newf("%i",slowFPS);
			}

			void framerate::renderFPS() { //Renders the FPS
				al_draw_filled_rectangle(0,0,32,16,al_map_rgba_f(0,0,0,0.5));
				al_draw_rectangle(1,1,31,15,al_map_rgba_f(1,1,1,0.7),1);
				al_draw_ustr(FPSRenderFont,al_map_rgb(255,255,255),6,2,0,FPSText);
				ALLEGRO_USTR* nS = al_ustr_newf("%i",networking::gameServer::getLatency());
				al_draw_ustr(FPSRenderFont,al_map_rgb(255,255,255),6,16,0,nS);
				al_ustr_free(nS);
			}

			void framerate::cleanupFPSRenderer() { //Clean up the renderer
				al_ustr_free(FPSText);
			}
}