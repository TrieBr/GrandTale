// ----------------------------------------------------------------------
//entityCharDeleteBox.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------
#include "entityCharDeleteBox.h"
#include "worldMainMenu.h"

namespace entities
{
	namespace mainMenu
	{
			entityCharDeleteBox::entityCharDeleteBox(unsigned short slotID) {
				slot = slotID;
				
			}
			void entityCharDeleteBox::initialize() {
				panelBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:deleteCharPanel.png");
				textboxBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:textbox180x26.png");
				exitButton = gameEngine::resources::graphics.loadBitmap(":loadScreen:closeButton.png");
				deleteButtonImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:deleteButtonLarge.png");
				x=-300;
				y=600/2;
				alpha = 1;
				fadeOut = false;
				errorFont = gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);


				deleteText = new GUI::widgets::textbox(textboxBG,errorFont,al_map_rgb(45,17,21));
				closeButton = new GUI::widgets::button(exitButton,GUI::widgets::HOVER_HIGHLIGHT);
				deleteButton = new GUI::widgets::button(deleteButtonImage,GUI::widgets::HOVER_HIGHLIGHT);
				this->setDepth(-10,true);
				deleteText->focus();

			}

			void entityCharDeleteBox::cleanup() {
			
				delete deleteText;
				delete closeButton;
				delete deleteButton;


			}

			void entityCharDeleteBox::render(float oX,float oY) {
				al_draw_tinted_bitmap(panelBG,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x-111,y,0);


				deleteText->render(x+18-111,y+69,alpha);
				closeButton->render(x+180-111,y+19,alpha);
				deleteButton->render(x+18-111,y+103,alpha);
				
			}
			void entityCharDeleteBox::update(double _timeFactor) {
				x += (((800/2)-x)/8) * _timeFactor;

				deleteText->update();
				closeButton->update(x+180-111,y+19);
				if (closeButton->fullClicked()) {
					fadeOut = true; //Close the box
				}
				deleteButton->update(x+18-111,y+103);
				if (deleteButton->fullClicked()) {
					if (deleteText->Text=="DELETE") {//Confirm character deletion
						networking::loginServer::deleteCharacter(slot); //Delete charatcer
						fadeOut = true;
					}
				}

				


				if (fadeOut) {
					alpha -= 0.1 * _timeFactor;
					if (alpha<0) {
						this->getParentWorld<worlds::worldMainMenu>()->showingError = false; //No longer showing an error
						this->parentWorld->removeEntity(this); //Remove ourself from the world
					}
				}
				
			}

			bool entityCharDeleteBox::handleEvent(ALLEGRO_EVENT &e) { 
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