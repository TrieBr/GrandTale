// ----------------------------------------------------------------------
// entityErrorBox.h
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "gameEngine.h"
#include <string>
namespace entities
{
	namespace mainMenu
	{
		class entityErrorBox: public gameEngine::abstractEntity
		{
		public:
			entityErrorBox(std::string errorMessage);
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;
			float alpha;
			bool fadeOut;
		private:
			ALLEGRO_BITMAP* errorBG;

			ALLEGRO_FONT* errorFont; //font used for the textboxes
			std::string errorText; //The text to display

		};

	}

}

