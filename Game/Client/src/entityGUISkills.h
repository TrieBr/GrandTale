
#include "gameEngine.h"
#include <string>
#include "Actions.h"
#include "button.h"
#include "abstractDraggableWindow.h"

#ifndef _H_GUI_WINDOW_SKILLS
#define _H_GUI_WINDOW_SKILLS
namespace entities
{
	namespace GameGUI
	{
		enum SkillsTabs {
			TAB_SKILLS,
			TAB_SKILLSCOUNT
		};
		class entityGUISkills: public abstractDraggableWindow
		{
		public:
			entityGUISkills();
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			void RefreshSkills();
			float alpha;
			bool fadeOut;
		private:
			ALLEGRO_BITMAP* background;
			ALLEGRO_BITMAP* closeButtonImage;
			ALLEGRO_BITMAP* tabPanels[3];
			ALLEGRO_BITMAP* skillEntryTextBackground;
			int selectedTab;
			void selectTab(int id);
			SlotArray skillSlotArray;

			GUI::widgets::button* closeButton;
			ALLEGRO_FONT* nameFont; //font used for the textboxes
			ALLEGRO_FONT* levelFont; //font used for the textboxes
		};

	}

}

#endif