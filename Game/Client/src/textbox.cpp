#include "textbox.h"
#include "gameEngine.h"

#ifndef _WIN32
#define max(x,y) ((x)>(y) ?  (x) : (y))
#endif

namespace GUI {
	namespace widgets {

			textbox::textbox(ALLEGRO_BITMAP* background, ALLEGRO_FONT *textFont, ALLEGRO_COLOR fontColor) { //Constructor
				this->backgroundImage = background; //Set the background image
				this->textFont = textFont; //The font that will be displayed.
				this->fontColor = fontColor;
				textBoxWidth = al_get_bitmap_width(backgroundImage); //The width of the text box. (simply grabs the width of the bitmap)

				//Padding (or margin around the text).
				leftPadding = 6; //Padding on the left side of the text box
				rightPadding = 6; //Padding on the right side of the text box
				topPadding = 0; //Padding on the top side of the text box
				bottomPadding = 0; //Padding on bottom left side of the text box
				//Create the "Cache" bitmap. This is where the text will be drawn in, and then this bitmap will be drawn over the background
				textDrawBitmap = al_create_bitmap(al_get_bitmap_width(backgroundImage)-rightPadding-leftPadding+4,al_get_bitmap_height(backgroundImage)-topPadding-bottomPadding);
				cursor = !false; //Show the blinking cursor?
				focused = false; //Is this textbox focused?
				lastBlink = al_get_time(); //Last time the cursor blinked (so we know when to toggle again)
				eQueue = al_create_event_queue(); //Create Event queue 
				al_register_event_source(eQueue,al_get_keyboard_event_source()); //Register keyboard Events
				charReplacement = 0; //Replacement char (eg * for passwords, or anything else
				renderCache(); //Render the text
	
			}

			textbox::~textbox() { //Destructor
				al_destroy_event_queue(eQueue);
				al_destroy_bitmap(textDrawBitmap);
			}

			void textbox::setReplacement(char replace) { //Set character Replacements (eg '*' for passwords) use 0 to reset to no replacement
				charReplacement = replace;
			}

			void textbox::initialize() {//Initialize ("creation event")

			}

			void textbox::shutdown() {//Clean up

			}

			//Renders all the text to the surface..
			void textbox::renderCache() {
				al_set_target_bitmap(textDrawBitmap); //Set target to our cache bitmap
				al_clear_to_color(al_map_rgb(33,33,33)); //Fill with random color
				al_convert_mask_to_alpha(textDrawBitmap,al_map_rgb(33,33,33)); //Set the random color we filled to alpha channel
				al_hold_bitmap_drawing(true); //Hold on blitting until we are done
				al_draw_bitmap(backgroundImage,-leftPadding,-topPadding,0); //Draw the background
				int textWidth = al_get_text_width(textFont,charReplacement==0 ? Text.c_str() : std::string(Text.length(),charReplacement).c_str()); //Width of all the text
				if (textWidth>textBoxWidth-leftPadding-rightPadding) 
				{//If the width is larger then then our allowed width
					//Draw the text right aligned
					al_draw_text(textFont,fontColor,textBoxWidth-leftPadding-rightPadding,0,ALLEGRO_ALIGN_RIGHT, charReplacement==0 ? Text.c_str() : std::string(Text.length(),charReplacement).c_str());
					if (focused && cursor)
					{//If the text box is focused and has a cursor, draw the cursor
						al_draw_text(textFont,fontColor,textBoxWidth-leftPadding-rightPadding,0,ALLEGRO_ALIGN_LEFT,"|");
					}

				}else{//Text is small enough to fit in the box, no scrolling needed
					//Draw the text left aligned
					al_draw_text(textFont,fontColor,0,0,ALLEGRO_ALIGN_LEFT,charReplacement==0 ? Text.c_str() : std::string(Text.length(),charReplacement).c_str());
					if (focused && cursor)
					{//If the text box is focused and cursor is toggled on, draw it.
						al_draw_text(textFont,fontColor,max(textWidth,0),0,ALLEGRO_ALIGN_LEFT,"|");
					}
				}
				al_hold_bitmap_drawing(false); //Draw everything
				al_set_target_backbuffer(gameEngine::core::getDisplay()); //Reset the buffer
			}

			void textbox::update() {//Update the textbox
	
						ALLEGRO_EVENT iEvent; //Input event
							//Handle input
							if (al_get_next_event(eQueue, &iEvent))
							{
								if (focused)
								{
									switch (iEvent.type)
									{
									case ALLEGRO_EVENT_KEY_CHAR:
										{
											if (iEvent.keyboard.unichar==8)
											{//Backspace
												if (Text.size()>0)
												{
												Text.erase(Text.end()-1);
												renderCache(); //Re render the cache
												}
											}
											if (iEvent.keyboard.unichar>=32 && iEvent.keyboard.unichar<=126)
											{
												char Add = char(iEvent.keyboard.unichar);
												Text.append(&Add,1);
												renderCache(); //Re render the cache
											}else{
												if (iEvent.keyboard.unichar>=161)
												{
													Text.append("?");
													renderCache(); //Re render the cache
												}
											}
										break;
										}

									}
								}

							}
							if (focused)
							{
								if (al_get_time()-lastBlink>=0.5)
								{//One 0.5 second has passed since the last time the cursor toggled
									cursor = !cursor; //Toggle the cursor
									lastBlink = al_get_time(); //Set last time the cursor toggled
									renderCache(); //Re render the cache
								}
							}
			}

			void textbox::render(float x, float y, float alpha) {//Render the entity.
				al_draw_tinted_bitmap(backgroundImage,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x,y,0); //Render the background of the text box
				al_draw_tinted_bitmap(textDrawBitmap,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x+leftPadding,y+topPadding,0); //Render the text cache
	
	
			}

			void textbox::focus(bool focus) {//Focus the text box
				this->focused = focus;
				if (focus==false)
				{
					cursor = false;
				}
				renderCache(); //Re render the cache
			}

			bool textbox::isFocused() {//Is the textbox focused?
				return focused;
			}
}

}