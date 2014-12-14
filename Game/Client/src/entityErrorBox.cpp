// ----------------------------------------------------------------------
// entityErrorPanel.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------
#include "entityErrorBox.h"
#include "worldMainMenu.h"

namespace entities
{
	namespace mainMenu
	{

			entityErrorBox::entityErrorBox(std::string errorMessage) {
				errorText = errorMessage;
				
			}
			void entityErrorBox::initialize() {
				errorBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:errorBG.png");
				x=-300;
				y=600/2;
				alpha = 1;
				fadeOut = false;
				this->setDepth(-10);
				errorFont = gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);
				
			}

			void entityErrorBox::cleanup() {
				
			
			}

			void entityErrorBox::render(float oX,float oY) {
				al_draw_tinted_bitmap(errorBG,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x-204,y,0);
				al_draw_text(errorFont,al_map_rgba(101*alpha,5*alpha,5*alpha,alpha*255),x-204+9,y+2,0,"Error!");
				al_draw_text(errorFont,al_map_rgba(101*alpha,5*alpha,5*alpha,alpha*255),x,y+24,ALLEGRO_ALIGN_CENTRE,errorText.c_str());
				ALLEGRO_MOUSE_STATE mS;
				al_get_mouse_state(&mS);
					if (gameEngine::globalFunctions::pointInRegion(mS.x,mS.y,x-204+384,y+8,x-204+384+16,y+8+16)) { //Hovering over the x button
						al_draw_text(errorFont,al_map_rgba(101*alpha,5*alpha,5*alpha,alpha*255),x-204+384,y+2,0,"X");
					}else { //Not hovering
						al_draw_text(errorFont,al_map_rgba(108*alpha,10*alpha,10*alpha,alpha*255),x-204+384,y+2,0,"X");
					}
				
			}
			void entityErrorBox::update(double _timeFactor) {
				x += (((800/2)-x)/8) * _timeFactor;

				if (fadeOut) {
					alpha -= 0.1 * _timeFactor;
					if (alpha<0) {
						this->getParentWorld<worlds::worldMainMenu>()->showingError = false; //No longer showing an error
						this->parentWorld->removeEntity(this); //Remove ourself from the world
					}
				}
				
				
			}

			bool entityErrorBox::handleEvent(ALLEGRO_EVENT &e) { 
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{//Mouse was pressed
					if (e.mouse.button==1)
					{//Left clicked
					
						if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x-204+384,y+8,x-204+384+16,y+8+16) && fadeOut ==false)
						{//Clicked on the close button
							fadeOut = true;
						}
						

					}

				}
				return true;
			}
			

	}

}