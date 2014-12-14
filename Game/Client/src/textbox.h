// ----------------------------------------------------------------------
// textbox.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	A textbox that allows text entry into it.
*/
// ------------------------------------------------------------------------


#ifdef _WIN32
#include <winsock2.h>
#endif
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>

#ifndef _H_GUIWIDGETTEXTBOX_
#define _H_GUIWIDGETTEXTBOX_

namespace GUI {
	namespace widgets {

		class textbox
		{
		public:
		textbox(ALLEGRO_BITMAP* background, ALLEGRO_FONT *textFont, ALLEGRO_COLOR fontColor); //Constructor
		~textbox(); //Destructor
		void initialize(); //Initialize ("creation event")
		void shutdown(); //Clean up
		void update(); //Update the Entity
		void render(float x, float y, float alpha = 1); //Render the entity.
		void focus(bool focus = true); //Focus the text box
		bool isFocused(); //Is the textbox focused?
		short getWidth() { return al_get_bitmap_width(backgroundImage); };
		short getHeight() { return al_get_bitmap_height(backgroundImage); };
		ALLEGRO_BITMAP*				backgroundImage; //The background of the textbox
		ALLEGRO_FONT*			textFont; //The font used to display the input
		ALLEGRO_COLOR				fontColor;

		void setReplacement(char replace = 0); //Set character Replacements (eg '*' for passwords) use 0 to reset to no replacement
		public:
			std::string				Text;  //Text of the textbox
		private:
			bool focused; //Is the textbox focused?
			ALLEGRO_BITMAP* textDrawBitmap; //A bitmap used for rendering/caching the text on
			void renderCache(); //Renders all the text to the surface..

			int						textBoxWidth; //boxwidth
			unsigned char			leftPadding; //Padding for the text in the box
			unsigned char			rightPadding; //Padding for the text in the box
			unsigned char			topPadding; //Padding for the text in the box
			unsigned char			bottomPadding; //Padding for the text in the box

			//Cursor
			bool					cursor; //cursor showing?
			double					lastBlink; //Last time cursor blinked (switched on or off)
			ALLEGRO_EVENT_QUEUE*	eQueue; //Event queue for capruting input
			char					charReplacement; //Replacements for all characters (eg. '*' for passwords)
		};


	}

}
#endif