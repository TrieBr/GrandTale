// ----------------------------------------------------------------------
// gameEngineFramerate.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Handles the framerate calculation of the game, as well as delta time information
*/


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#ifndef _H_GAMEENGINEFRAMERATE_
#define _H_GAMEENGINEFRAMERATE_


namespace gameEngine {

	class framerate
	{
	public:
		static double targetFramerate; //The target framerate that the logic should use
		static double FPS; //The framerate in frames per second (FPS)
		static int slowFPS; //The framerate in frames per second, but only updated once per second so it can be read easier
		static double deltaTime; //Delta time factor
		static ALLEGRO_USTR* FPSText; //The text that has the FPS
		static void calculateFramerate(); //Calculate the framerate. This should be called every step of the game loop


		static ALLEGRO_FONT* FPSRenderFont; //Font used for rendering the fps
		static void initializeFPSRenderer(); //Initializes the font renderer
		static void renderFPS(); //Renders the FPS
		static void cleanupFPSRenderer(); //Clean up the renderer

	private:
		static double lastFrameTime; //Used for calculating framerate; contains the time the last frame was rendered
		static double lastSlowFPSUpdate; //Last time the slowFPS variable was updated
	};

}
#endif