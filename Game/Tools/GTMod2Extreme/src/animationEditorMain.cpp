#ifdef ANIMEDIT
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "animationEditor.h"
#include <resourcePack.h>
#include <gameEngineResources.h>

int main() {

	al_init();
	al_init_image_addon();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	 al_install_keyboard();

	animationEditor *editorWindow = new animationEditor();
	//Initialize essential resource management
	resourceManager::resourcePack::initializeAllegroInterface();
	gameEngine::resources::graphics.load("../../../Assets/compiledAssets/Graphics.gtd"); //Load the graphics package
	gameEngine::resources::data.load("../../../Assets/compiledAssets/Data.gtd"); //Load the graphics package
	editorWindow->initialize();
	editorWindow->createRenderer();
	float timeLastFrame = al_get_time();

	while (1) {
		double delta = 60/(1/(al_get_time()-timeLastFrame));
		timeLastFrame = al_get_time();

			static double accumulatedTime = 0;
				accumulatedTime += delta;
				const double fixedFrameTime = (double)1/(double)60;
				while( accumulatedTime > fixedFrameTime )
				{
				  accumulatedTime -= fixedFrameTime;
				 editorWindow->update(fixedFrameTime); //update the world
				}

		editorWindow->render();
		al_rest(0.0);
	}


}

#endif