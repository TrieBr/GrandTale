#include "abstractDraggableWindow.h"
std::vector<abstractDraggableWindow*> abstractDraggableWindow::currentWindows;

	abstractDraggableWindow::abstractDraggableWindow(int dragHandleWidth, int dragHandleHeight) {


	}
	bool abstractDraggableWindow::dragHandleEvent(ALLEGRO_EVENT &e) {
		return true;
	}



	
	void abstractDraggableWindow::addOpenWindow(abstractDraggableWindow* window) {

	}
	void abstractDraggableWindow::closeOpenWindow(abstractDraggableWindow* window) {

	}
	void abstractDraggableWindow::setWindowFront(abstractDraggableWindow* window) {

	}