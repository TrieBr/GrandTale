#include "gameEngine.h"

#ifndef _H_ABSTRACTDRAGGABLEWINDOW
#define _H_ABSTRACTDRAGGABLEWINDOW
class abstractDraggableWindow: public gameEngine::abstractEntity {
public:
	abstractDraggableWindow(int dragHandleWidth, int dragHandleHeight);
	bool dragHandleEvent(ALLEGRO_EVENT &e);
	float x;
	float y;

	//Used for managing all the abstractDraggableWindows on the screen
	static std::vector<abstractDraggableWindow*> currentWindows;
	static void addOpenWindow(abstractDraggableWindow* window);
	static void closeOpenWindow(abstractDraggableWindow* window);
	static void setWindowFront(abstractDraggableWindow* window);

private:
	bool isDragging;
	
	float relativeDragX;
	float relativeDragY;
	int handleWidth;
	int handleHeight;


	//Used for managing all the abstractDraggableWindows on the screen
	static int frontDepth;
	static int backDepth;

};

#endif