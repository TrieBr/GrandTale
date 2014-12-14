// ----------------------------------------------------------------------
// button.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	Represents a button that is hoverable, clickable, etc.
*/
// ------------------------------------------------------------------------


#ifdef _WIN32
#include <winsock2.h>
#endif 
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>

#ifndef _H_GUIWIDGETBUTTON_
#define _H_GUIWIDGETBUTTON_

namespace GUI {
	namespace widgets {
		enum buttonFlags {
			HOVER_HIGHLIGHT = 1 //Renders the button as slightly highlighted when hovered
		};

		class button {
		public:
			button(ALLEGRO_BITMAP *buttonImage, buttonFlags flags);
			~button();
			void setImage(ALLEGRO_BITMAP* newImage);
			void render(float x, float y, float alpha); //Render the button at a specific location
			void update(float x, float y); //Update based on the location..
			bool isHovered(); //mouse hovered over button?
			bool isClicked(); //Is the button being pressed down
			bool fullClicked(); //Was the button fully clicked?
			ALLEGRO_EVENT_QUEUE* mouseEvents; //Capture mouse events for handling button input

			int width; //Button width
			int height; //Button height
		private:
			bool _isHovered; //Is the button being hovered over?
			bool _isClicked; //is the button down?
			bool _fullClick; //Was the button pressed and released?
			ALLEGRO_BITMAP* buttonImage; //The buttons image;
			buttonFlags flags;
		};

	}


}


#endif