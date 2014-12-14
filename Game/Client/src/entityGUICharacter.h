
#include "gameEngine.h"
#include <string>
#include "Actions.h"
#include "button.h"
#include <map>
#include "abstractDraggableWindow.h"

#ifndef _H_GUI_WINDOW_CHARACTER
#define _H_GUI_WINDOW_CHARACTER
namespace entities
{
	namespace GameGUI
	{
		enum CharacterTabs {
			TAB_EQUIP,
			TAB_STATS,
		};
		class entityGUICharacter: public abstractDraggableWindow
		{
		public:
			entityGUICharacter();
			virtual ~entityGUICharacter() {} 
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float alpha;
			bool fadeOut;
		private:
			ALLEGRO_BITMAP* background;
			ALLEGRO_BITMAP* closeButtonImage;
			ALLEGRO_BITMAP* tabPanels[2];
			std::map<RACE,ALLEGRO_BITMAP*> raceBackgrounds;
			int selectedTab;
			void selectTab(int id);
			SlotArray leftColumn; //Left side of window
			SlotArray bottomRow; //Bottom part of window
			SlotArray rightColumn; //right part of window
			character::characterRenderer previewRenderer;

			ALLEGRO_BITMAP* leftButton;
			ALLEGRO_BITMAP* rightButton;
			GUI::widgets::button * button_str_left;
			GUI::widgets::button * button_str_right;
			GUI::widgets::button * button_int_left;
			GUI::widgets::button * button_int_right;
			GUI::widgets::button * button_dex_left;
			GUI::widgets::button * button_dex_right;
			GUI::widgets::button * button_agi_left;
			GUI::widgets::button * button_agi_right;
			GUI::widgets::button * button_vit_left;
			GUI::widgets::button * button_vit_right;
			GUI::widgets::button * button_luk_left;
			GUI::widgets::button * button_luk_right;


			GUI::widgets::button* closeButton;
			ALLEGRO_FONT* nameFont; //font used for the textboxes
			ALLEGRO_FONT* statFont; //Dont used for the stat numbers

		};

	}

}

#endif