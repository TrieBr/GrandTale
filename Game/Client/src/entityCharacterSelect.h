// ----------------------------------------------------------------------
// entityCharacterSelect.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Where the user selects their character
*/
// ------------------------------------------------------------------------



#include "gameEngine.h"
#include "textbox.h"
#include "button.h"
#include "loginServer.h"
#include "mainMenuPanelTransition.h"
#include "characterRenderer.h"
#include "characterData.h"
#include "entityCharDeleteBox.h"
#include <vector>

#define CHARACTERSLOTS 3

#ifndef _H_ENTITYCHARSELECT_
#define _H_ENTITYCHARSELECT_


struct characterSlot {
bool slotInUse; //Does this slot contain a character?
GUI::widgets::button* mainButton; //Button that shows "Select" or "Create"
character::characterRenderer* renderer; //Renderer for the character
GUI::widgets::button* deleteButton; //Button to delete character
character::characterData charData;
};

namespace entities
{
	namespace mainMenu
	{
		
		class entityCharacterSelect : public gameEngine::abstractEntity
		{
		public:
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;

			mainMenuPanelTransition panelTransition; //For the transition between menus
			float cracksAlpha; //Alpha for the cracks behind
			GUI::widgets::button* backButton; //Button to go back
			void zeroSlots(bool initialize = false); //Clean/Zero out slots





			void setSlot(int slotInd, character::characterData *cData); //Set a character slot
			characterSlot characterSlots[CHARACTERSLOTS];

			// TODO Clean up the whole "slot" system. Possibly combine into one vector to make it more managable
			std::vector<character::characterData*> characterList; //List of characters that can be selected.
			std::vector<GUI::widgets::button*> characterListButtons; //The buttons to select/create a character.
			std::vector<character::characterRenderer*>  characterRenderers; //Character renderers
			std::vector<GUI::widgets::button*>	deleteButtons; //Buttons to delete characters


		private:
			ALLEGRO_BITMAP* panelBG;
			ALLEGRO_BITMAP* panelBGCracks;
			ALLEGRO_BITMAP* backButtonImage;
			ALLEGRO_BITMAP *buttonCreateCharacterImage;
			ALLEGRO_BITMAP* buttonSelectCharacterImage;
			ALLEGRO_BITMAP* buttonDeleteImage;

			entityCharDeleteBox* deleteBox; //Box to delete a character

			ALLEGRO_FONT* mainFont; //font used for the textboxes
		};

	}

}

#endif