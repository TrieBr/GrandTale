
#include <WinSock2.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "mapEditor.h"
#include "equipAligner.h"
#include "animationEditor.h"

int runMapEditor() {
	mapEditor *editorWindow = new mapEditor();
	editorWindow->initialize();
	editorWindow->setCleanMap();
	while (1) {
		editorWindow->update();
		editorWindow->render();
	}
}

int runAnimationEditor() {
	

	animationEditor *editorWindow = new animationEditor();
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

int runEquipAligner() {
	equipAligner *editorWindow = new equipAligner();
	editorWindow->initialize();
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

int runAnimConfig() {
	for (;;) {
	std::cout << "Enter number of frames (0 to exit): ";
	unsigned char frames;
	int buf;
	std::cin >> buf;
	frames = buf;
	if (frames==0) return 0;
	std::cout << "Enter animation speed (frames per second): ";
	unsigned char fps;
	std::cin >> buf;
	fps = buf;

	int originX, originY;
	std::cout << "Enter Origin (x): ";
	std::cin >> originX;
	std::cout << "Enter Origin (y): ";
	std::cin >> originY;

	std::fstream out("anim.dat",std::ios::binary | std::ios::out);
		out.write((char*)&frames,sizeof(unsigned char));
		out.write((char*)&fps,sizeof(unsigned char));
		out.write((char*)&originX,sizeof(unsigned char));
		out.write((char*)&originY,sizeof(unsigned char));

	out.close();
	std::cout << "File Saved as \"anim.dat\"" << std::endl;

	}
	
	return 1;
}

int main(int argc, char* argv[]) {

	al_init();
	al_init_image_addon();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	 al_install_keyboard();
	
	//Initialize essential resource management
	resourceManager::resourcePack::initializeAllegroInterface();
	gameEngine::resources::graphics.load("../../../Assets/compiledAssets/Graphics.gtd"); //Load the graphics package
	gameEngine::resources::data.load("../../../Assets/compiledAssets/Data.gtd"); //Load the graphics package

	if (argc>=1) {
		if (std::string(argv[1])=="animation") {
			runAnimationEditor();
		}
		if (std::string(argv[1])=="map") {
			runMapEditor();
		}
		if (std::string(argv[1])=="equip") {
			runEquipAligner();
		}
		if (std::string(argv[1])=="animconfig") {
			runAnimConfig();
		}
	}else{
		std::cout << "Please specify tool to use: \n GTMod2Extreme.exe <tool> \n Tools: \n\tanimation\n\tmap\n\tequip"<< std::endl;

	}
	


}
