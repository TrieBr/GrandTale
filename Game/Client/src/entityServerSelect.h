// ----------------------------------------------------------------------
// entityServerSelect.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	The panel where the user selects the server to play on...
*/
// ------------------------------------------------------------------------

#include "gameEngine.h"
#include "textbox.h"
#include "button.h"
#include "loginServer.h"
#include "mainMenuPanelTransition.h"
#include <vector>

#ifndef _H_ENTITYSERVERSELECT_
#define _H_ENTITYSERVERSELECT_
namespace entities
{
	namespace mainMenu
	{

		struct serverEntry
		{
			std::string serverName;
			GUI::widgets::button* goButton;
			int serverID;
		};
		class entityServerSelect : public gameEngine::abstractEntity
		{
		public:
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			void addServer(RakNet::RakString serverName, int id);

			float x,y;
			mainMenuPanelTransition panelTransition;
			float cracksAlpha;
			std::vector<serverEntry*> serverList;

		private:
			ALLEGRO_BITMAP* panelBG;
			ALLEGRO_BITMAP* panelBGCracks;
			ALLEGRO_BITMAP* serverSelectText;
			ALLEGRO_BITMAP* backButton;
			ALLEGRO_BITMAP* scrollBarPlaceholder;
			ALLEGRO_BITMAP* serverTitle;
			ALLEGRO_BITMAP* serverButtonGo;

			ALLEGRO_FONT* mainFont; //font used for the textboxes

		};

	}

}

#endif