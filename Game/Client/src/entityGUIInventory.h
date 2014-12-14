
#include "gameEngine.h"
#include <string>
#include "Actions.h"
#include "button.h"
#include "abstractDraggableWindow.h"

#ifndef _H_GUI_WINDOW_INVENTORY
#define _H_GUI_WINDOW_INVENTORY
namespace entities
{
	namespace GameGUI
	{
		enum InventoryTabs {
			TAB_USABLE,
			TAB_GEAR,
			TAB_ITEMS,
			TAB_COUNT
		};
		class entityGUIInventory: public abstractDraggableWindow
		{
		public:
			entityGUIInventory();
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			void RefreshInventory();
			float alpha;
			bool fadeOut;
		private:
			SlotArray UsableItems;

			ALLEGRO_BITMAP* background;
			ALLEGRO_BITMAP* closeButtonImage;
			ALLEGRO_BITMAP* tabPanels[3];
			int selectedTab;
			void selectTab(int id);

			GUI::widgets::button* closeButton;
			ALLEGRO_FONT* nameFont; //font used for the textboxes

		};

	}

}

#endif