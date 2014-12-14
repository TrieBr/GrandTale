// ----------------------------------------------------------------------
// entityCharacterCreation.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	The panel used for creating a character
*/
// ------------------------------------------------------------------------


#include "gameEngine.h"
#include "textbox.h"
#include "button.h"
#include "loginServer.h"
#include "mainMenuPanelTransition.h"
#include "characterRenderer.h"
#include <vector>

#ifndef _H_ENTITYCHARCREATE_
#define _H_ENTITYCHARCREATE_
namespace entities
{
	namespace mainMenu
	{
		class entityCharacterCreation : public gameEngine::abstractEntity
		{
		public:
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;

			mainMenuPanelTransition panelTransition; //Used for the main menu transition..
			float cracksAlpha; //The alpha for the cracks behind the panel
			GUI::widgets::button* backButton; //Button to go back

			//All the buttons D:
			GUI::widgets::button* hairStyleLeft;
			GUI::widgets::button* hairStyleRight;
			GUI::widgets::button* facialFeatureLeft;
			GUI::widgets::button* facialFeatureRight;
			GUI::widgets::button* hairColorLeft;
			GUI::widgets::button* hairColorRight;
			GUI::widgets::button* skinColorLeft;
			GUI::widgets::button* skinColorRight;
			GUI::widgets::button* genderLeft;
			GUI::widgets::button* genderRight;
			GUI::widgets::button* createButton;
			GUI::widgets::button* raceHuman;
			GUI::widgets::button* class1;

			GUI::widgets::button* raceElder;
			GUI::widgets::button* raceNorelf;
			GUI::widgets::button* raceOorka;
			GUI::widgets::button* raceUndead;

			GUI::widgets::textbox* characterNameTextBox; //Textbox for the name entry
			
		private:
			ALLEGRO_BITMAP* panelBG;
			ALLEGRO_BITMAP* panelBGCracks;
			ALLEGRO_BITMAP* backButtonImage;
			ALLEGRO_BITMAP* buttonLeftImage;
			ALLEGRO_BITMAP* buttonRightImage;
			ALLEGRO_BITMAP* createCharacterImage;
			ALLEGRO_BITMAP* textboxBackground;

			ALLEGRO_BITMAP* raceElderImage;
			ALLEGRO_BITMAP* raceNorelfImage;
			ALLEGRO_BITMAP* raceOorkaImage;
			ALLEGRO_BITMAP* raceUndeadImage;

			character::characterCustomization* customization;
			character::characterRenderer* characterRenderer;

			std::vector<int> selectableHairStylesMale;
			std::vector<int> selectableHairStylesFemale;
			std::vector<int> selectableFacialFeatureMale;
			std::vector<int> selectableFacialFeatureFemale;
			std::vector<int> selectableHairColor;
			std::vector<int> selectableskinColor;

			int selectedHairMale;
			int selectedHairFemale;
			int selectedFacialFeatureMale;
			int selectedFacialFeatureFemale;
			int selectedSkinColor;
			int selectedHairColor;
			int selectedGender;
			int selectedRace;
			int selectedEyes; //User cant select this, is set when race is set.
			int selectedMouth; //User cant select this, is set when race is set.

			void refreshCustomization(); //Refresh the customization for rendering

			ALLEGRO_FONT* mainFont; //font used for the textboxes
		};

	}

}

#endif