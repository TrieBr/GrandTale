

#include "mapEditor.h"

tileSelector::tileSelector(mapEditor* parentEditor) {
	selectedTileSet = 0;
	panX = 0;
	panY = 0;
	panning = false;


	panelW = TILEPANELWIDTH;
	panelH = 800;
	panelX = 0 - panelW + 32;
	panelY = 0;
	transition = sIN;

	selectedTileX = selectedTileY = 0;
	selectedTileW = selectedTileH = 64;
	selectTileW = selectTileH = 64; //The width/height of a tile when we select one

	this->parent = parentEditor;
	this->tileSelectCanvas =	al_create_bitmap(panelW,panelH/2);
}


void tileSelector::initialize() {
	loadTileSets();
		currentLayer = 0;
	if (this->parent->mHandler->mData->tileLayers.size()<1) { //If there are no layers.. create one..
		this->parent->mHandler->mData->tileLayers.push_back(new tileLayer());
	}


};


bool tileSelector::handleEvent(ALLEGRO_EVENT &ev) {
			switch (ev.type) {
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
					if (ev.mouse.x > panelX && ev.mouse.x < panelX + panelW && ev.mouse.y > panelY && ev.mouse.y < panelY+panelH) {
						if (ev.mouse.button==3) {
							panning = true;
							panStartX = panX+ev.mouse.x;
							panStartY = panY+ev.mouse.y;
							return true;
						}

						if (ev.mouse.button==1) {

							selectedTileX = floor(((ev.mouse.x)-(panelX-panX)) / selectTileW ) * selectTileW ;
							selectedTileY= floor(((ev.mouse.y)-(panelY+(panelH/2)-panY)) / selectTileH ) * selectTileH ;
							
							return true;
						}
					}
					break;								  }
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
						if (ev.mouse.button==3) {
							panning = false;
						}
					break;
			}

		}

			return false;
}

void tileSelector::update() {
	ALLEGRO_EVENT ev;
	if (transition==transitionStatus::sFLYOUT) {
		panelX += (0-panelX/12);
		if (panelX>-10) {
			panelX = 0;
			transition = transitionStatus::sOUT;
		}
	}
	if (transition==transitionStatus::sFLYIN) {
		panelX += ((panelX-0 - panelW + 32)/12);
		if (panelX<=0 - panelW + 32) {
			panelX = 0 - panelW + 32;
			transition = transitionStatus::sIN;
		}
	}

	if (panning) {
		ALLEGRO_MOUSE_STATE mS;
		al_get_mouse_state(&mS);
		panX = panStartX-mS.x;
		panY = panStartY-mS.y;
	}
}

void tileSelector::render() {

	al_draw_filled_rectangle(panelX,panelY,panelX+panelW,panelY+panelH,al_map_rgba(0,0,0,127));
	al_draw_rectangle(panelX,panelY,panelX+panelW,panelY+panelH,al_map_rgba(255,255,255,127),1);

	static int thumbWidth = 200;
	static int thumbHeight = 100;
	al_draw_filled_rectangle(panelX+(panelW/2)-(thumbWidth/2),panelY+16,panelX+(panelW/2)-(thumbWidth/2)+thumbWidth,panelY+(panelW/2)-16+thumbHeight,al_map_rgba(140,140,140,140));
	al_draw_scaled_bitmap(tileList[selectedTileSet]->bitmap,0,0,al_get_bitmap_width(tileList[selectedTileSet]->bitmap),al_get_bitmap_height(tileList[selectedTileSet]->bitmap),panelX+(panelW/2)-(thumbWidth/2),panelY+16,thumbWidth,thumbHeight,0);
	al_draw_rectangle(panelX+(panelW/2)-(thumbWidth/2),panelY+16,panelX+(panelW/2)-(thumbWidth/2)+thumbWidth,panelY+(panelW/2)-16+thumbHeight,al_map_rgb(0,0,0),1);

	al_set_target_bitmap(tileSelectCanvas);
	al_clear_to_color(al_map_rgba(68,68,68,68));
	//al_draw_filled_rectangle(panelX,panelY+(panelH/2),panelX+panelW,panelH,al_map_rgba(68,68,68,68));
	al_draw_bitmap(tileList[selectedTileSet]->bitmap,-panX,-panY,0);
	al_draw_rectangle(selectedTileX-panX,selectedTileY-panY,selectedTileX+selectedTileW-panX,selectedTileY+selectedTileH-panY,al_map_rgb(0,0,0),2);
	al_set_target_backbuffer(parent->display);

	al_draw_bitmap(tileSelectCanvas,panelX,panelY+(panelH/2),0);
	
}


void tileSelector::loadTileSets() { //Load all the tile sets..

	tileList.push_back(tilesetManager::loadTileSet(0));
	selectedTileSet = 0;
}