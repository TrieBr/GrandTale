
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "mapEditor.h"

int main() {

	al_init();
	al_init_image_addon();
	al_install_mouse();
	al_init_primitives_addon();
	 al_install_keyboard();

	mapEditor *editorWindow = new mapEditor();
	//Initialize essential resource management
	resourceManager::resourcePack::initializeAllegroInterface();
	gameEngine::resources::graphics.load("../../../../Assets/compiledAssets/Graphics.gtd"); //Load the graphics package
	gameEngine::resources::data.load("../../../../Assets/compiledAssets/Data.gtd"); //Load the graphics package
	editorWindow->initialize();
	editorWindow->setCleanMap();
	while (1) {
		editorWindow->update();
		editorWindow->render();
	}


}