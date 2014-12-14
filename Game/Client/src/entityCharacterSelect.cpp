// ----------------------------------------------------------------------
// entityCharacterSelect.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "entityCharacterSelect.h"
#include "worldMainMenu.h"
#include "loginServer.h"
#include "characterAnimationSequenceManager.h"
namespace entities
{
	namespace mainMenu
	{
			void entityCharacterSelect::initialize() {
				//Load the images.
				panelBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBGLarge.png");
				panelBGCracks = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBGCracks.png");
				buttonCreateCharacterImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonCreateCharacter.png");
				buttonSelectCharacterImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonSelectCharacter.png");
				backButtonImage  = gameEngine::resources::graphics.loadBitmap(":loadScreen:backButton.png");
				buttonDeleteImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:deleteButton.png");
				zeroSlots(true);
				


				mainFont = gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);

				x = 107;
				y= 279;

				backButton  = new GUI::widgets::button(backButtonImage,GUI::widgets::HOVER_HIGHLIGHT); //Create the back button

				//Request our character list from the server
				networking::loginServer::requestCharacterList();
				

			


			}
			void entityCharacterSelect::cleanup() {

			
				delete backButton;
				//Delete all the characters
				for (unsigned char i=0; i<characterList.size(); i++) {
					delete characterList[i];
				}
				//Delete the buttons for selecting/creating characters
				for (unsigned char i=0; i<characterListButtons.size(); i++) {
					delete characterListButtons[i];
				}
				//Delete the character renderers
				for (unsigned char i=0; i<characterRenderers.size(); i++) {
					delete characterRenderers[i];

				}
				characterListButtons.clear();
			}
			void entityCharacterSelect::render(float oX,float oY) {
				//al_draw_tinted_bitmap(panelBGCracks,al_map_rgba_f(1*cracksAlpha,1*cracksAlpha,1*cracksAlpha,cracksAlpha),x-56,y-48,0);
				al_draw_bitmap(panelBG,x,y,0);
				backButton->render(x+554,y+19,1);

				float xx = 0;

				for (int i=0; i<CHARACTERSLOTS; i++) {
					if (characterSlots[i].slotInUse) {
						al_draw_text(mainFont,al_map_rgb(45,17,21),x+109+xx,y+190,ALLEGRO_ALIGN_CENTRE,characterSlots[i].charData.getCharacterName().c_str()); //Draw the characters name
						characterSlots[i].mainButton->render(x+16+xx,y+224,1); //Render the button
						characterSlots[i].renderer->render(x+109+xx,y+150); //Render the character
						characterSlots[i].deleteButton->render(x+134+xx,y+155,1);
					}else{
						characterSlots[i].mainButton->render(x+16+xx,y+224,1); //Render the button
					}
					xx+= 188;
				}


			}

			void entityCharacterSelect::update(double _timeFactor) {

				if (this->panelTransition.isTransitioning) { //If we are currently transitioning panels..
					this->panelTransition.update(&x,&cracksAlpha, _timeFactor); //Update position based on transition
				}

				backButton ->update(x+554,y+19); //Update the back button
				if (backButton->fullClicked()) { //If the back button was pressed..
					this->getParentWorld<worlds::worldMainMenu>()->charSelectToServerSelect(); //Go back to server select
				}

				float xx = 0;
				for (int i=0; i<CHARACTERSLOTS; i++) {
					if (characterSlots[i].slotInUse) {
						characterSlots[i].mainButton->update(x+16+xx,y+224); //Render the button
							if (characterSlots[i].mainButton->fullClicked()) {
								//Login to this character
								networking::loginServer::selectCharacter(i);
							}
						characterSlots[i].renderer->animationPlayer.stepAnimation(_timeFactor);
						characterSlots[i].deleteButton->update(x+134+xx,y+155);
						if (characterSlots[i].deleteButton->fullClicked()) {
							deleteBox = new entityCharDeleteBox(i);
							getParentWorld<worlds::worldMainMenu>()->addEntity(deleteBox);
						}
						
					}else{
						characterSlots[i].mainButton->update(x+16+xx,y+224); //Render the button
						if (characterSlots[i].mainButton->fullClicked()) { //Button was clicked
							this->getParentWorld<worlds::worldMainMenu>()->charSelectToCharCreate();
						}
					}
					xx+= 188;
				}		
			}

			bool entityCharacterSelect::handleEvent(ALLEGRO_EVENT &e) { 
				return true;
			}


			void entityCharacterSelect::setSlot(int slotInd, character::characterData *cData) {

				if (cData==NULL) { //If the data is null, this slot needs to be emptied
					characterSlots[slotInd].slotInUse = false;
					characterSlots[slotInd].mainButton->setImage(buttonCreateCharacterImage); //Set the image to "Select"
					if (characterSlots[slotInd].renderer!=NULL) {
						delete characterSlots[slotInd].renderer;
						characterSlots[slotInd].renderer = NULL;
					}
					if (characterSlots[slotInd].deleteButton!=NULL) {
						delete characterSlots[slotInd].deleteButton;
						characterSlots[slotInd].deleteButton = NULL;
					}
				}else{
					characterSlots[slotInd].slotInUse = true;
					characterSlots[slotInd].mainButton->setImage(buttonSelectCharacterImage); //Set the image to "Select"
					characterSlots[slotInd].charData = *cData;
					characterSlots[slotInd].renderer = new character::characterRenderer(&characterSlots[slotInd].charData); //Set the renderer
					characterSlots[slotInd].renderer->setAnimation(character::characterAnimationSequenceManager::getSequence(0),character::ANIMATION_LOOP); //Set the animation
					characterSlots[slotInd].deleteButton = new GUI::widgets::button(buttonDeleteImage,GUI::widgets::HOVER_HIGHLIGHT);
				}
			}

		void entityCharacterSelect::zeroSlots(bool initialize) {
			if (initialize) { //If initializing..
				for (int i=0; i<CHARACTERSLOTS; i++) {
					characterSlots[i].slotInUse = false;
					characterSlots[i].mainButton = new GUI::widgets::button(buttonCreateCharacterImage,GUI::widgets::HOVER_HIGHLIGHT);
					characterSlots[i].renderer = NULL;
					characterSlots[i].deleteButton = NULL;
				}
			}else{
				for (int i=0; i<CHARACTERSLOTS; i++) {
					characterSlots[i].slotInUse = false;
					characterSlots[i].mainButton->setImage(buttonCreateCharacterImage); //Set the image to "Select"
					if (characterSlots[i].renderer!=NULL) {
						delete characterSlots[i].renderer;
						characterSlots[i].renderer = NULL;
					}
					if (characterSlots[i].deleteButton!=NULL) {
						delete characterSlots[i].deleteButton;
						characterSlots[i].deleteButton = NULL;
					}
				}
			}
		}
	}



}