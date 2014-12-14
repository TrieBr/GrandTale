// ----------------------------------------------------------------------
// mainMenuPanelTransition.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	This nifty little class it sort of an abstracted trasnsition so the panels can fly in and out
*/
// ------------------------------------------------------------------------


#include "gameEngineFramerate.h"

#ifndef _H_MAINMENUPANELTRANSITION
#define _H_MAINMENUPANELTRANSITION

class mainMenuPanelTransition
{
public:
	mainMenuPanelTransition(){
		isTransitioning = false;
	}

			int flyStage;
			float cracksAlpha;
			float firstXDest;
			float secondXDest;
			bool isTransitioning;
			float x;

			void flyOut(float origX, float destX ) {
				flyStage = 0;
				cracksAlpha = 1.0;
				if (destX<origX) { //If we are going left..
					firstXDest = origX + 100;
					secondXDest = destX;
				}
				if (destX>origX) { //If we are going right
					firstXDest = origX - 100;
					secondXDest = destX;
				}
				x = origX;
				isTransitioning = true;
			}
			void update(float *updateX , float* updateAlphaCracks, double _timeFactor) {
				if (flyStage==0) {
					cracksAlpha -= 0.1 * _timeFactor; //Fade..
					if (cracksAlpha<=0){
						cracksAlpha = 0; //Set the alpha to 0
						flyStage = 1; //Go to the next stage of the transition
					}
				}
				if (flyStage==1) {
					if (firstXDest>x) { //Going right
						x += ((firstXDest-x)/4) * _timeFactor;
						if (firstXDest-x<10) {
							flyStage = 2;
						}
					}

					if (firstXDest<x) { //Going left
						x += ((firstXDest-x)/4) * _timeFactor;
						if (x-firstXDest<10) {
							flyStage = 2;
						}
					}
				}

				if (flyStage==2) {
					if (secondXDest<x) { //Going lefr
						x += ((secondXDest-x)/4) * _timeFactor;
						if (x-secondXDest<10) {
							flyStage = 3;
						}
					}
					if (secondXDest>x) { //Going right
						x += ((secondXDest-x)/4) * _timeFactor;
						if (secondXDest-x<10) {
							flyStage = 3;
						}
					}
				}

				if (flyStage==3) {
					cracksAlpha += 0.1 * _timeFactor; //Fade..
					if (cracksAlpha>=1){
						cracksAlpha = 1; //Set the alpha to 0
						isTransitioning=false;
					}
				}



				(*updateX) = x;
				(*updateAlphaCracks) = cracksAlpha;
			}
};

#endif