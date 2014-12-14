#include "mapEditor.h"
#include "mapSaver.h"

mapEditor::mapEditor() {
	panning = false;
	viewX = 0.0f;
	viewY = 0.0f;
	placingTile = false;

	gridW =  gridH = 64;
	gridEnabled = true;
	drawGrid = true;
	startedLine = false;
}

void mapEditor::initialize() {
	this->display  = al_create_display(1000,800);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_mouse_event_source());
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
}

void mapEditor::getGridSnapPositon(int *x, int *y) {
	ALLEGRO_MOUSE_STATE mS;
	al_get_mouse_state(&mS);

	if (!gridEnabled) {
	*x = mS.x+viewX;// (ev.mouse.x - viewX)
	*y = mS.y+viewY;
	}else{
	*x = floor((mS.x+viewX) / gridW) * gridW;// (ev.mouse.x - viewX)
	*y  = floor((mS.y+viewY) / gridH) * gridH;
	}
}


void mapEditor::update() {
	ALLEGRO_MOUSE_STATE mS;
	al_get_mouse_state(&mS);
	
		if (tSelector->transition ==transitionStatus::sIN && panning==false) {
			if (mS.x < 32) {
				tSelector->transition = transitionStatus::sFLYOUT;
			}
		}
		if (tSelector->transition ==transitionStatus::sOUT && !tSelector->panning) {
			if (mS.x > tSelector->panelW) {
				tSelector->transition = transitionStatus::sFLYIN;
			}
		}
	int placeX, placeY;
	getGridSnapPositon(&placeX, &placeY);


	ALLEGRO_KEYBOARD_STATE kS;
	al_get_keyboard_state(&kS);

	ALLEGRO_EVENT ev;
	if (al_get_next_event(eventQueue,&ev)) {
		if (tSelector->handleEvent(ev)==false) {

			switch (ev.type) {

			case ALLEGRO_EVENT_KEY_UP: {

						if (ev.keyboard.keycode==ALLEGRO_KEY_LEFT) {
							this->mHandler->mData->left -= 64;
						}
						if (ev.keyboard.keycode==ALLEGRO_KEY_RIGHT) {
							this->mHandler->mData->right += 64;
						}

						if (ev.keyboard.keycode==ALLEGRO_KEY_UP) {
							this->mHandler->mData->top -= 64;
						}
						if (ev.keyboard.keycode==ALLEGRO_KEY_DOWN) {
							this->mHandler->mData->bottom += 64;
						}

						if (ev.keyboard.keycode==ALLEGRO_KEY_S) {
							if (al_key_down(&kS,ALLEGRO_KEY_LCTRL)) {
								this->saveMap();
							}
						}
						if (ev.keyboard.keycode==ALLEGRO_KEY_O) {
							if (al_key_down(&kS,ALLEGRO_KEY_LCTRL)) {
								this->loadMap(0);
							}
						}

						if (ev.keyboard.keycode==ALLEGRO_KEY_B) {
							if (al_key_down(&kS,ALLEGRO_KEY_LCTRL)) {
								//mapBackground* nBG = new mapBackground();
								//nBG->xPos = 0;
								//nBG->yPos = 0;
								//nBG->bgHandle = backgroundManager::loadBackground(3);
								
								//mapBackground* buf = this->mHandler->mData->backgroundLayers[1];
								this->mHandler->mData->backgroundLayers[3]->yPos = 0;
								//this->mHandler->mData->backgroundLayers[2] = buf;
								//this->mHandler->mData->backgroundLayers.insert(this->mHandler->mData->backgroundLayers.begin(),nBG);
							}
						}
				break;
									   }

				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
						if (ev.mouse.button==3) {
							panning = true;
							panStartX = viewX+ev.mouse.x;
							panStartY = viewY+ev.mouse.y;
						}
						if (ev.mouse.button==2) { //Right click

							if (al_key_down(&kS,ALLEGRO_KEY_SPACE)) { //If we are in "collision line edit mode" (eg. space being held)
								collisionLine* closest = getNearestCollisionLine(ev.mouse.x+viewX,ev.mouse.y+viewY,8);
										this->mHandler->mData->removeCollisionLine(closest); //Remove the collision line
							}else{
								for (unsigned int i=0; i<this->mHandler->mData->tileLayers[tSelector->currentLayer]->layouts.size(); i++) { //ITerate all layouts on current layer
									tileLayout *currentLayout = this->mHandler->mData->tileLayers[tSelector->currentLayer]->layouts[i];
									bool doBreak = false;
									for(unsigned int ti=currentLayout->tilePositions.size()-1; ti>0; ti--) { //For each tile
										tile* tFound = currentLayout->tilePositions[ti];
										if (ev.mouse.x>tFound->mapX-viewX && ev.mouse.x<tFound->mapX+currentLayout->tilesetData->tileWidth-viewX  && ev.mouse.y>tFound->mapY-viewY && ev.mouse.y<tFound->mapY+currentLayout->tilesetData->tileHeight-viewY) {
											currentLayout->tilePositions.erase(currentLayout->tilePositions.begin()+ti);
											 doBreak = true;
											break;
										}

									}
									if ( doBreak) {
										break;
									}
								}

							}
						}
						if (ev.mouse.button==1) { //Left Click
							if (al_key_down(&kS,ALLEGRO_KEY_SPACE)) { //If we are placing a collision line
								if (startedLine==false) {
									startX = placeX;
									startY = placeY;
									startedLine = true;
								}
							}else{
								placingTile = true;

								bool foundLayout = false;
								for (unsigned int i=0; i<this->mHandler->mData->tileLayers[tSelector->currentLayer]->layouts.size(); i++) {
									if (this->mHandler->mData->tileLayers[tSelector->currentLayer]->layouts[i]->tilesetData->tilesetID == tSelector->tileList[tSelector->selectedTileSet]->tilesetID)
									{
									
										tile* newTile = new tile();
										newTile->mapX = placeX;
										newTile->mapY = placeY;
										newTile->tileSetX = tSelector->selectedTileX/tSelector->selectTileW;
										newTile->tileSetY = tSelector->selectedTileY/tSelector->selectTileH;
										tileDrag = newTile;
										this->mHandler->mData->tileLayers[tSelector->currentLayer]->layouts[i]->tilePositions.push_back(newTile);
										foundLayout = true;

										break;
									}
								}
								if (!foundLayout) {
									tileLayout* newLayout = new tileLayout();
									newLayout->tilesetData = tSelector->tileList[tSelector->selectedTileSet];
									tile* newTile = new tile();
									newTile->mapX = placeX;
									newTile->mapY = placeY;
									newTile->tileSetX = tSelector->selectedTileX/tSelector->selectTileW;
									newTile->tileSetY = tSelector->selectedTileY/tSelector->selectTileH;
									tileDrag = newTile;
									newLayout->tilePositions.push_back(newTile);
									this->mHandler->mData->tileLayers[tSelector->currentLayer]->layouts.push_back(newLayout);
								}
							}
						}
					break;
													  }
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
						if (ev.mouse.button==3) {
							panning = false;
						}
						if (ev.mouse.button==1) { //LEft click
							if (al_key_down(&kS,ALLEGRO_KEY_SPACE)) { //If we are placing a collision line
								if (startedLine==true) {
									collisionLine* newLine = new collisionLine();
									newLine->p1.x = this->startX;
									newLine->p1.y = this->startY;
									newLine->p2.x = placeX;
									newLine->p2.y = placeY;
									if (al_key_down(&kS,ALLEGRO_KEY_ALT)) {
										newLine->jumpthrough = false;
									}else{
										newLine->jumpthrough = true;
									}

									if (!(newLine->p1==newLine->p2))
									{
										this->mHandler->mData->addCollisionLine(newLine);
									}else{
										delete newLine;
									}
									startedLine = false;
								}
							}else{

							placingTile = false;
							}
						}
					break;
													  }
			}

		}
	}

	if (panning) {
		
		viewX = panStartX-mS.x;
		viewY = panStartY-mS.y;
	}

	if (placingTile) {
		tileDrag->mapX = placeX;
		tileDrag->mapY = placeY;
	}
	tSelector->update();
}
void mapEditor::render() {
	ALLEGRO_MOUSE_STATE mS;
	al_get_mouse_state(&mS);
	al_clear_to_color(al_map_rgb(68,255,68));
	al_draw_filled_rectangle(mHandler->mData->left-viewX, mHandler->mData->top-viewY, -viewX+mHandler->mData->right,-viewY+ mHandler->mData->bottom,al_map_rgb(68,68,68));
	this->mHandler->render(-viewX,-viewY,1000,1000);

	collisionLine* closest = getNearestCollisionLine(mS.x+viewX,mS.y+viewY,8);


	for (collisionLineListNode* i = this->mHandler->mData->getRootCollisionLine(); i!=NULL; i=i->next) { //Iterate through all the lines
		collisionLine* line = i->line;

		ALLEGRO_COLOR drawColor = al_map_rgb(255,255,255);
		
		if (!line->jumpthrough) {
			drawColor = al_map_rgb(255,255,128);
		}
		if (line==closest) {
			drawColor = al_map_rgb(255,0,0);
		}
			al_draw_line(line->p1.x-viewX,line->p1.y-viewY,line->p2.x-viewX,line->p2.y-viewY,drawColor,2);

	}
	
	int placeX, placeY;
	getGridSnapPositon(&placeX, &placeY);
	if (startedLine) {
		al_draw_line(startX-viewX,startY-viewY,placeX-viewX,placeY-viewY,al_map_rgb(255,255,255),2);
	}

	tSelector->render();
	al_flip_display();


}

void mapEditor::loadMap(int mapID) {
	this->mHandler = new mapHandler();
	mHandler->loadMap(mapID);
		tSelector = new tileSelector(this);
	tSelector->initialize();
}

void mapEditor::setCleanMap() {
	this->mHandler = new mapHandler();
	mHandler->mData = new mapData();
		tSelector = new tileSelector(this);
	tSelector->initialize();
}

void mapEditor::saveMap() {
	ALLEGRO_FILECHOOSER* fC = al_create_native_file_dialog(al_create_path(""),"Select Location..","*.map",ALLEGRO_FILECHOOSER_SAVE);
	al_show_native_file_dialog(this->display,fC);
	const ALLEGRO_PATH* savePath = al_get_native_file_dialog_path(fC,0);
	const char* pathName = al_path_cstr(savePath, ALLEGRO_NATIVE_PATH_SEP);
	ALLEGRO_FILE* fHandle = al_fopen(pathName,"wb");
	mapSaver* newSaver = new mapSaver(*this->mHandler->mData);
	newSaver->writeData(fHandle);
	al_fclose(fHandle);
}


collisionLine* mapEditor::getNearestCollisionLine(int x, int y, int maxDist) {
	float x0,y0,x1,y1,x2,y2,x3,y3,dx,dy,t,segment;
	collisionLine* closestLine = NULL;
	int currentDist = maxDist;
	x3 = x;
	y3 = y;
	for (collisionLineListNode* i = this->mHandler->mData->getRootCollisionLine(); i!=NULL; i=i->next) {
		collisionLine* cLine = i->line;
		x1 = cLine->p1.x;
		y1 = cLine->p1.y;
		x2 = cLine->p2.x;
		y2 = cLine->p2.y;
		dx = x2 - x1;
		dy = y2 - y1;
		if ((dx == 0) && (dy == 0)) {
			x0 = x1;
			y0 = y1;
		}else{
			t = ((x3 - x1) * dx + (y3 - y1) * dy) / (dx * dx + dy * dy);
			t = min(max(0,t),1);
			x0 = x1 + t * dx;
			y0 = y1 + t * dy;
		}
		float dist =  sqrt((x0-x3)*(x0-x3)+(y0-y3)*(y0-y3));
		if (dist<currentDist) {
			closestLine = cLine;
			currentDist = dist;
		}

	}

	return closestLine;

}
