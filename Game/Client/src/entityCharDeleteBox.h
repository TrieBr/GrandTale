// ----------------------------------------------------------------------
// entityCharDeleteBox.h
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "gameEngine.h"
#include <string>
#include "textbox.h"
#include "button.h"

#ifndef _H_ENTITYCHARDELETEBOX
#define _H_ENTITYCHARDELETEBOX

namespace entities
{
	namespace mainMenu
	{
		class entityCharDeleteBox: public gameEngine::abstractEntity
		{
		public:
			entityCharDeleteBox(unsigned short slotID);
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;
			float alpha;
			bool fadeOut;
		private:
			unsigned short slot; //Slot to delete
			ALLEGRO_BITMAP* panelBG;
			ALLEGRO_BITMAP*	textboxBG;
			ALLEGRO_BITMAP* exitButton;
			ALLEGRO_BITMAP* deleteButtonImage;
			GUI::widgets::textbox *deleteText;
			GUI::widgets::button  *closeButton;
			GUI::widgets::button	*deleteButton;
			ALLEGRO_FONT* errorFont; //font used for the textboxes
		};

	}

}

#endif

