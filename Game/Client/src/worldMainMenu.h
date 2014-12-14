// ----------------------------------------------------------------------
// worldMainMenu.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	The main menu that handles initial loading, connecting, login, server select, character creation, character selection, and connecting to the game.
*/
// ------------------------------------------------------------------------
#include "gameEngine.h"
#include "entityLoginPanel.h"
#include "entityServerSelect.h"
#include "entityCharacterSelect.h"
#include "entityCharacterCreation.h"

namespace worlds
{
	
	class worldMainMenu : public gameEngine::abstractWorld
	{
	public:
		void initialize();
		void render(float offsetX=0, float offsetY=0);
		void cleanup();
		void update(double _timeFactor);

		void showError(std::string errorText);

		bool showingError; //is an error message showing?

		void loginToServerSelect();
		void serverSelectToLogin();
		void serverSelectToCharSelect();
		void charSelectToServerSelect();
		void charCreateToCharSelect();
		void charSelectToCharCreate();

		entities::mainMenu::entityLoginPanel* loginPanel;
		entities::mainMenu::entityServerSelect* serverSelect;
		entities::mainMenu::entityCharacterSelect* characterSelect;
		entities::mainMenu::entityCharacterCreation* characterCreate;
	private:
		ALLEGRO_BITMAP *background;
		ALLEGRO_BITMAP *logo; //The logo
		ALLEGRO_BITMAP *cursor; //The cursor bitmap
		ALLEGRO_AUDIO_STREAM* backgroundMusic;
		ALLEGRO_VOICE* mainMenuVoice;
	};
}