
#include "gameEngine.h"
#include <string>

#ifndef _GUI_NAMEPLATE
#define _GUI_NAMEPLATE

namespace entities
{
	namespace GameGUI
	{
		class entityGUINamePlate: public gameEngine::abstractEntity
		{
		public:
			entityGUINamePlate();
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;
			float alpha;
			bool fadeOut;
		private:
			ALLEGRO_BITMAP* background;
			ALLEGRO_BITMAP* levelBackground;
			ALLEGRO_BITMAP* barBackground;
			ALLEGRO_BITMAP* healthBar;
			ALLEGRO_BITMAP* manaBar;
			ALLEGRO_FONT* nameFont; //font used for the textboxes

		};

	}

}

#endif

