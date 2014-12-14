// ----------------------------------------------------------------------
// entityLoginPanel.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	The login panel on the main Menu
*/
// ------------------------------------------------------------------------

#include "gameEngine.h"
#include "textbox.h"
#include "button.h"
#include "loginServer.h"
#include "mainMenuPanelTransition.h"

#ifndef _H_ENTITY_LOGINPANEL
#define _H_ENTITY_LOGINPANEL

namespace entities
{
	namespace mainMenu
	{
		class entityLoginPanel : public gameEngine::abstractEntity
		{
		public:
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			float x,y;
			float alpha;
			mainMenuPanelTransition panelTransition;
			float cracksAlpha;


			GUI::widgets::textbox* usernameBox; //The username textbox
			GUI::widgets::textbox* passwordBox; //The password textbox

		private:
			ALLEGRO_BITMAP* panelBG;
			ALLEGRO_BITMAP* usernameText;
			ALLEGRO_BITMAP* passwordText;
			ALLEGRO_BITMAP* loginButtonBitmap;
			ALLEGRO_BITMAP* exitButton;
			ALLEGRO_BITMAP* textbox;
			ALLEGRO_BITMAP* panelBGCracks;
			ALLEGRO_BITMAP* throbberIn;
			ALLEGRO_BITMAP* throbberOut;
			ALLEGRO_BITMAP* blankLoginButton;


			ALLEGRO_FONT* textboxFont; //font used for the textboxes

			GUI::widgets::button* loginButton; //Login button
			float throbberInAngle;
			float throbberOutAngle;
			
			std::pair<float,float> usernameBoxPosition; //Username textbox position
			std::pair<float,float> passwordBoxPosition; //password textbox position
		};

	}

}

#endif