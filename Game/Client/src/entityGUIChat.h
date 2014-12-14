
#include "gameEngine.h"
#include <string>
#include "Actions.h"
#include "textbox.h"
namespace entities
{
	namespace GameGUI
	{

		class chatEntry{
		public:
			chatEntry() { r =  g = b = 1; }
			std::string Name;
			std::string Message;
			float r, g, b; //Color
		};

		struct formattedChatEntry {
			std::string Name;
			std::string Message;
			short nameWidth;
			float r, g, b;
		};
		class entityGUIChat: public gameEngine::abstractEntity
		{
		public:
			entityGUIChat();
			void initialize();
			void cleanup();
			void render(float oX = 0,float oY = 0);
			void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			void AddMessage(std::string name, std::string message, float r, float g, float b);
			float x,y;
			float alpha;
			bool fadeOut;
			ALLEGRO_BITMAP* chatBoxCache;
			void RenderChatBoxCache();
		private:
			short drawLines;
			short lineHeight;
			short chatWidth;
			bool resizingChatVertical;
			std::vector<chatEntry> chatLog;
			ALLEGRO_BITMAP* chatTypeBG; 
			ALLEGRO_BITMAP* chatTextBoxBG;
			GUI::widgets::textbox *textEntryBox;
			ALLEGRO_FONT* font; //font used for the textboxes

		};

	}

}

