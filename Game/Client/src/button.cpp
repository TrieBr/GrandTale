// ----------------------------------------------------------------------
// button.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "button.h"
#include "globalFunctions.h"

namespace GUI {
	namespace widgets {

			button::button(ALLEGRO_BITMAP *buttonImage, buttonFlags flags) {
				mouseEvents = al_create_event_queue();
				al_register_event_source(mouseEvents,al_get_mouse_event_source());

				width = al_get_bitmap_width(buttonImage);
				height = al_get_bitmap_height(buttonImage);
				_isClicked = false;
				_isHovered = false;
				_fullClick = false;
				this->buttonImage = buttonImage; //The buttons image;
				this->flags = flags;
			}

			button::~button() {
				al_destroy_event_queue(mouseEvents);
			}

			void button::setImage(ALLEGRO_BITMAP* newImage) { //Set a new image
				this->buttonImage = newImage;
			}

			void button::render(float x, float y, float alpha) { //Render the button at a specific location
				if ((flags & HOVER_HIGHLIGHT) == HOVER_HIGHLIGHT) {
					if (isHovered()) { //Hovered, so draw highlighted..
						al_draw_tinted_bitmap(buttonImage,al_map_rgba_f(1*alpha,1*alpha,1*alpha,0.8*alpha),x,y,0);
					}else{
						al_draw_tinted_bitmap(buttonImage,al_map_rgba_f(1*alpha,1*alpha,1*alpha,1*alpha),x,y,0);
					}
					return;
				}
			}

			void button::update(float x, float y) { //Update based on the location..
				if (this->_fullClick==true) {
					this->_fullClick = false;
				}
				 ALLEGRO_EVENT ev;
				 if (al_get_next_event(mouseEvents, &ev)) { //An event was received
					 if (ev.type==ALLEGRO_EVENT_MOUSE_AXES) { //The mouse moved..
						 if(gameEngine::globalFunctions::pointInRegion(ev.mouse.x,ev.mouse.y,x,y,x+width,y+height)) {
							 this->_isHovered = true;
						 }else{
							 this->_isHovered = false;
						 }
					 }
					 if (ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) { //Button was pressed down
						 if (this->_isHovered) { //If button is being hovered over
							 this->_isClicked = true;
						 }
					 }
					  if (ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP) { //Button was released
						 if (this->_isHovered) { //If button is being hovered over
							 if (this->_isClicked==true) {
								 this->_fullClick = true;
							 }
							 this->_isClicked = false;
						 }
					 }
				 }
			}

			bool button::isHovered() { //mouse hovered over button?
				return _isHovered;
			}

			bool button::isClicked() { //Was the button clicked this frame?
				return _isClicked;
			}

			bool button::fullClicked() { //Was the button clicked this frame?
				return _fullClick;
			}
	}


}
