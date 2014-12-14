#include <WinSock2.h>
#include "equipAligner.h"


equipAligner::equipAligner() {


}

void equipAligner::initialize(){
	this->display  = al_create_display(800,600);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_mouse_event_source());
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	font = al_load_ttf_font("arial.ttf",-20,0);

	bodyPart newBodyPart;
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_BODY);
	availableBodyParts.push_back(newBodyPart);
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_FACINGFOOT);
	availableBodyParts.push_back(newBodyPart);
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_HEAD);
	availableBodyParts.push_back(newBodyPart);
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_LEFTHAND);
	availableBodyParts.push_back(newBodyPart);
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_RIGHTHAND);
	availableBodyParts.push_back(newBodyPart);
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_CLOSEDHAND);
	availableBodyParts.push_back(newBodyPart);
	newBodyPart.bodyPartImage = character::characterImageManager::getSkinImage(1, 0, character::BODY_STRAIGHTFOOT);
	availableBodyParts.push_back(newBodyPart);

	cache_head_eyes = character::characterImageManager::getEyesImage(1);

	cache_head_mouth = character::characterImageManager::getMouthImage(1);
	
	selectedBodyPart = 0;
	aligningImage = NULL;
	imageAlignAlpha = 1;
}

void equipAligner::update(double timeStep){
	ALLEGRO_MOUSE_STATE mS;
	al_get_mouse_state(&mS);
	ALLEGRO_KEYBOARD_STATE kS;
	al_get_keyboard_state(&kS);
	ALLEGRO_EVENT ev;
	if (al_get_next_event(eventQueue,&ev)) {
			switch (ev.type) {
				case ALLEGRO_EVENT_KEY_UP: {
					if (ev.keyboard.keycode==ALLEGRO_KEY_O) {
							if (al_key_down(&kS,ALLEGRO_KEY_LCTRL)) {
								this->pickAlignmentPiece();
							}
						}
					if (ev.keyboard.keycode==ALLEGRO_KEY_S) {
							if (al_key_down(&kS,ALLEGRO_KEY_LCTRL)) {
								this->saveAlignmentPieceData();
							}
						}
					if (ev.keyboard.keycode==ALLEGRO_KEY_SPACE) {
						if (imageAlignAlpha==1) { imageAlignAlpha=0.6; }else{ imageAlignAlpha = 1;}

						}
					
					break;
				}
					 case ALLEGRO_EVENT_KEY_CHAR: {

					if (ev.keyboard.keycode==ALLEGRO_KEY_RIGHT) {
						aligningImageProperties.offsetX += 1;
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_LEFT) {
						aligningImageProperties.offsetX -= 1;
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_UP) {
						aligningImageProperties.offsetY -= 1;
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_DOWN) {
						aligningImageProperties.offsetY+= 1;
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_D) {
						selectedBodyPart++;
						if (selectedBodyPart>availableBodyParts.size()-1) {
							selectedBodyPart = 0;
						}
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_A) {
						selectedBodyPart--;
						if (selectedBodyPart<0) {
							selectedBodyPart = availableBodyParts.size()-1;
						}

					}
					break;
					 }
			}

	}

}

void equipAligner::render(){
	al_set_target_backbuffer(this->display);
	al_clear_to_color(al_map_rgb(44,44,44));

	al_draw_bitmap(availableBodyParts[selectedBodyPart].bodyPartImage->image,(800/2)-availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginX,100-availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginY,0);
	
	if (selectedBodyPart==2) {
	al_draw_bitmap(cache_head_eyes->image,((800/2)-availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginX)+cache_head_eyes->imageRelativeX+availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginX-cache_head_eyes->imageOriginX,(100-availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginY)+availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginY+cache_head_eyes->imageRelativeY-cache_head_eyes->imageOriginY,0);
	al_draw_bitmap(cache_head_mouth->image,((800/2)-availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginX)+cache_head_mouth->imageRelativeX+availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginX-cache_head_mouth->imageOriginX,(100-availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginY)+availableBodyParts[selectedBodyPart].bodyPartImage->imageOriginY+cache_head_mouth->imageRelativeY-cache_head_mouth->imageOriginY,0);
	}

	if (aligningImage!=NULL) {
		al_draw_tinted_bitmap(aligningImage,al_map_rgba_f(imageAlignAlpha,imageAlignAlpha,imageAlignAlpha,imageAlignAlpha),((800/2)-aligningImageProperties.originX)+aligningImageProperties.offsetX,(100-aligningImageProperties.originY)+aligningImageProperties.offsetY,0);
	}


	int spacing = 800/availableBodyParts.size();
	int xx=0;
	for(int i=0; i<availableBodyParts.size(); i++) {
		if (i==selectedBodyPart) {
			
			al_draw_filled_rectangle(xx,300,xx+al_get_bitmap_width(availableBodyParts[i].bodyPartImage->image),300+al_get_bitmap_height(availableBodyParts[i].bodyPartImage->image),al_map_rgba(200,200,200,120));
		}
		al_draw_bitmap(availableBodyParts[i].bodyPartImage->image,xx,300,0);
		if (i==2) {
			al_draw_bitmap(cache_head_eyes->image,xx+cache_head_eyes->imageRelativeX+availableBodyParts[i].bodyPartImage->imageOriginX-cache_head_eyes->imageOriginX,300+availableBodyParts[i].bodyPartImage->imageOriginY+cache_head_eyes->imageRelativeY-cache_head_eyes->imageOriginY,0);
			al_draw_bitmap(cache_head_mouth->image,xx+cache_head_mouth->imageRelativeX+availableBodyParts[i].bodyPartImage->imageOriginX-cache_head_mouth->imageOriginX,300+availableBodyParts[i].bodyPartImage->imageOriginY+cache_head_mouth->imageRelativeY-cache_head_mouth->imageOriginY,0);
		}
		xx+=spacing;
	}


	al_flip_display();
}

void equipAligner::pickAlignmentPiece() {
	ALLEGRO_FILECHOOSER* fC = al_create_native_file_dialog("","Open Image to align..","*.png",0);
	al_show_native_file_dialog(this->display,fC);
	const char* pathName = al_get_native_file_dialog_path(fC,0);
	if (pathName!=NULL) {
		//const char* pathName = al_path_cstr(savePath, ALLEGRO_NATIVE_PATH_SEP);
		ALLEGRO_BITMAP* image = al_load_bitmap(pathName);
		if (image!=NULL) {
			aligningImage = image;
			aligningImageProperties.offsetX = 0;
			aligningImageProperties.offsetY = 0;
			aligningImageProperties.originX = al_get_bitmap_width(image)/2;
			aligningImageProperties.originY = al_get_bitmap_height(image)/2;
		}
	}

	return;
}

void equipAligner::saveAlignmentPieceData() {
	ALLEGRO_FILECHOOSER* fC = al_create_native_file_dialog("","Open Image to align..","*.raw",ALLEGRO_FILECHOOSER_SAVE);
	al_show_native_file_dialog(this->display,fC);
	const char* pathName = al_get_native_file_dialog_path(fC,0);
	if (pathName!=NULL) {
		//const char* pathName = al_path_cstr(savePath, ALLEGRO_NATIVE_PATH_SEP);
		std::fstream o(pathName, std::ios::out | std::ios::binary | std::ios::trunc);
		if (o.is_open()) {
			o.write((char*)&aligningImageProperties,sizeof(aligningImageProperties));
			o.close();
		}
	}
}