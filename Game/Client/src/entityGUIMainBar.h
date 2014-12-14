
#include "gameEngine.h"
#include <string>
#include "Actions.h"
#include "characterIconRenderer.h"
namespace entities
{
	namespace GameGUI
	{
		
		class entityGUIMainBar: public gameEngine::abstractEntity
		{
		public:
			entityGUIMainBar();
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;
			float alpha;
			bool fadeOut;
		private:
			std::vector<SlotArray> ActionBars;

			character::characterIconRenderer* characterIcon;

			ALLEGRO_BITMAP* expBackground;
			ALLEGRO_BITMAP* expBar;
			ALLEGRO_BITMAP* actionBarBackground;
			ALLEGRO_BITMAP*	actionBarSlotBackground;
			ALLEGRO_BITMAP* actionBarSlotBorderRed; //Game actiom bars like "character, inventory, etc"
			ALLEGRO_BITMAP* actionBarSlotBorderBrown;
			ALLEGRO_BITMAP* latencyGreen, *latencyYellow, *latencyRed;
			ALLEGRO_FONT* font; //font used for the textboxes

		};

	}

}

