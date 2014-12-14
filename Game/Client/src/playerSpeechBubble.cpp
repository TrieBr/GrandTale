#include "playerSpeechBubble.h"
#include "gameEngineResources.h"
#include <allegro5/allegro_primitives.h>
#include "globalFunctions.h"

	playerSpeechBubble::playerSpeechBubble() { //Initializaton
		bubbleSliceNW = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceNW.png");
		bubbleSliceN = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceN.png");
		bubbleSliceNE = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceNE.png");
		bubbleSliceE = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceE.png");
		bubbleSliceSE = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceSE.png");
		bubbleSliceS = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceS.png");
		bubbleSliceSW = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceSW.png");
		bubbleSliceW = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:sliceW.png");
		speechPoint = gameEngine::resources::graphics.loadBitmap(":speechBubbles:0:speechPoint.png");
		textFont =   gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);
		rectangleWidth = 200;
		rectangleHeight = 100;
		scale = 0;
		alpha = 0;
		bubbleBitmap  = NULL;
	}
	playerSpeechBubble::~playerSpeechBubble() {

	}
	void playerSpeechBubble::displayText(std::string textToDisplay, bool animate) {
		
		surfaceWidth = 200;
		surfaceHeight = 130;
		bubbleBitmap = al_create_bitmap(surfaceWidth,surfaceHeight);
		rectangleWidth = 200;
		rectangleHeight = max(32,gameEngine::globalFunctions::drawTextWrapped(textFont,0,200-16,6,200,al_map_rgb(0,0,0),0,textToDisplay)+16);
		renderBubble(0,0,textToDisplay);
		scale = 0;
		alpha = 1;
		animationProgress = 0; //Scaling up
		timeStarted = al_get_time();
	}
	void playerSpeechBubble::update(double _timeFactor) { //Update the speech bubble

		if (animationProgress==0) { //Scaling up
			if (scale<1.3) {
				scale += 0.2*_timeFactor;
			}else{
				animationProgress=1;
			}

		}
		else if (animationProgress==1) { //Scaling back down
			if (scale>1) {
				scale -= 0.1*_timeFactor;
			}else{
				if (scale>1) {
					scale = 1;
				}
				animationProgress=2; //Done
			}
		}
		else if (animationProgress==2) { //fading out
			if ((al_get_time()-timeStarted)>3.0) {
				animationProgress = 3;
			}
		}
		else if (animationProgress==3) { //fading out
			if (alpha>0) {
				alpha -= 0.2*_timeFactor;
			}else{
				animationProgress = 4;
			}
		}

		
		
	}

	void playerSpeechBubble::renderBubble(float X, float Y,std::string stringDisplay) {
		ALLEGRO_BITMAP* oldSurface = al_get_target_bitmap();
		al_set_target_bitmap(bubbleBitmap);
		al_draw_filled_rectangle(0,0,surfaceWidth,surfaceHeight,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(bubbleBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta
		static unsigned char sliceWidth = 16;
		static unsigned char sliceHeight = 16;
		static unsigned char pointWidth = 26;
		static unsigned char pointHeight = 23;
		al_draw_bitmap(bubbleSliceSW,X, Y+rectangleHeight-sliceHeight,0); // SW
		al_draw_bitmap(bubbleSliceNW,X, Y,0); // NW
		al_draw_bitmap(bubbleSliceSE,X+rectangleWidth-sliceWidth, Y+rectangleHeight-sliceHeight,0); //SE

		al_draw_bitmap(bubbleSliceNE,X+rectangleWidth-sliceWidth, Y,0); //NE

		for (int i=sliceWidth; i<rectangleWidth-sliceWidth; i+=sliceWidth) {
			al_draw_bitmap(bubbleSliceN,X+i, Y,0); // N
			al_draw_bitmap(bubbleSliceS,X+i, Y+rectangleHeight-sliceHeight,0); // S
		}

		for (int i=sliceHeight; i<rectangleHeight-sliceHeight; i+=sliceHeight) {
			al_draw_bitmap(bubbleSliceW,X, Y+ i,0); // W
			al_draw_bitmap(bubbleSliceE,X+rectangleWidth-sliceWidth, Y+i,0); // E
		}

		al_draw_bitmap(speechPoint,X+(rectangleWidth/2),(Y+rectangleHeight)-2,0); //Draw the point
		al_draw_filled_rectangle(sliceWidth,sliceHeight,rectangleWidth-(sliceWidth),rectangleHeight-(sliceHeight),al_map_rgb(255,255,255));
		gameEngine::globalFunctions::drawTextWrapped(textFont,200/2,200,6,200-16,al_map_rgb(0,0,0),ALLEGRO_ALIGN_CENTRE,stringDisplay);

		al_set_target_bitmap(oldSurface);


	}
	void playerSpeechBubble::render(float X, float Y) { //Render the speech bubble at specified position?
		
		if (bubbleBitmap!=NULL) {
			al_draw_tinted_scaled_rotated_bitmap(bubbleBitmap,al_map_rgba_f(alpha,alpha,alpha,alpha),rectangleWidth/2,rectangleHeight+23,X,Y,scale,scale,0,0);
		}

	
	}
