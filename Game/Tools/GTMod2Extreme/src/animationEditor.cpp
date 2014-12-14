#include "animationEditor.h"
#include <raceProperties.h>
#include <characterAnimationSequenceManager.h>
#include <algorithm>
#include <fstream>

bool frameSort (character::animationPoint &point1, character::animationPoint &point2) { return (point1.timeFrame<point2.timeFrame); }

animationEditor::animationEditor(){
	aSeq = NULL;
	aSeq = new character::characterAnimationSequence();
	this->draggingFramePosition = false;
	draggingPart = false;


}
void animationEditor::initialize(){
	this->display  = al_create_display(800,600);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_mouse_event_source());
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	font = al_load_ttf_font("arial.ttf",-20,0);

	character::animationPoint p = character::characterAnimationSequenceManager::getSequence(0)->animationTimeframe[0];
	animationFrames.push_back(p);

	setFrameEdit(0);

	partEdit = HEAD;
}
void animationEditor::update(double timeStep){
	ALLEGRO_MOUSE_STATE mS;
	al_get_mouse_state(&mS);
	ALLEGRO_KEYBOARD_STATE kS;
	al_get_keyboard_state(&kS);
	ALLEGRO_EVENT ev;
	character::bodyPartPosition *pEdit;
	switch (partEdit) {
	case HEAD: pEdit = &editingPoint->Head; break;
	case BODY: pEdit = &editingPoint->body; break;
	case LEFTARM: pEdit = &editingPoint->leftHand; break;
	case RIGHTARM: pEdit = &editingPoint->rightHand; break;
	case LEFTFOOT: pEdit = &editingPoint->leftFoot; break;
	case RIGHTFOOT: pEdit = &editingPoint->rightFoot; break;
	}
	
	if (al_get_next_event(eventQueue,&ev)) {
			switch (ev.type) {
				case ALLEGRO_EVENT_KEY_UP: {
					if (ev.keyboard.keycode==ALLEGRO_KEY_RIGHT) {
						setFrameEdit(findAdjacentFrame(false,animationFrames[frameEdit].timeFrame));
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_LEFT) {
						setFrameEdit(findAdjacentFrame(true,animationFrames[frameEdit].timeFrame));
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_1) {
						ALLEGRO_FILECHOOSER* fc = al_create_native_file_dialog(NULL,"Save location","*.*",ALLEGRO_FILECHOOSER_SAVE);
						al_show_native_file_dialog(this->display,fc);
						const char* fName = al_get_native_file_dialog_path(fc,0);
						//const char* fName = al_path_cstr(p,ALLEGRO_NATIVE_PATH_SEP);
						SaveAnimation(fName);
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_2) {

						ALLEGRO_FILECHOOSER* fc = al_create_native_file_dialog(NULL,"Load location","*.*",0);
						al_show_native_file_dialog(this->display,fc);
						const char* fName = al_get_native_file_dialog_path(fc,0);
						//const char* fName = al_get_path_filename(p);
						LoadAnimation(fName);
					}
					break;
				}
				case ALLEGRO_EVENT_KEY_CHAR: {
					if (ev.keyboard.keycode==ALLEGRO_KEY_SPACE) {
						switch (partEdit) {
							case HEAD: partEdit = BODY; break;
							case BODY: partEdit = LEFTARM; break;
							case LEFTARM: partEdit = RIGHTARM; break;
							case RIGHTARM: partEdit = LEFTFOOT; break;
							case LEFTFOOT: partEdit = RIGHTFOOT; break;
							case RIGHTFOOT: partEdit = HEAD; break;
							}
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_D) {
						pEdit->x += 1;
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_A) {
						pEdit->x -= 1;
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_W) {
						pEdit->y -= 1;
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_S) {
						pEdit->y += 1;
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_E) {
						pEdit->rotation += 0.1;
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_Q) {
						pEdit->rotation -= 0.1;
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_Z) {
						if (pEdit->footState==character::STRAIGHT) { pEdit->footState = character::FACING; }
						else{
							pEdit->footState = character::STRAIGHT; 
						}
						ApplyChanges();
					}
					if (ev.keyboard.keycode==ALLEGRO_KEY_DELETE) {
						int currentSel = frameEdit;
						this->setFrameEdit(this->findAdjacentFrame(true,this->animationFrames[frameEdit].timeFrame));
						this->animationFrames.erase(this->animationFrames.begin()+currentSel);
						ApplyChanges();
					}
					
					break;
				}
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
					if(ev.mouse.button==1) {
						if (ev.mouse.x > scrubberLeft && ev.mouse.x < scrubberLeft+scrubberWidth && ev.mouse.y > scrubberTop && ev.mouse.y < scrubberTop+scrubberHeight) {
							draggingFramePosition = true;
							break;
						}
					}
					if(ev.mouse.button==2) {
						character::animationPoint p = animationFrames[animationFrames.size()-1];
						p.timeFrame = min(max(0,float((ev.mouse.x-scrubberLeft))/float(scrubberWidth)),1);
						animationFrames.push_back(p);
						this->setFrameEdit(animationFrames.size()-1);
					}
					if(ev.mouse.button==3) {
						draggingPart = true;
						dragPartX = pEdit->x- ev.mouse.x;
						dragPartY = pEdit->y-ev.mouse.y;

					}
					
					break;
				}
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
					if(ev.mouse.button==1) {
						if (draggingFramePosition) {
							draggingFramePosition = false;
							ApplyChanges();
						}
					}
					if(ev.mouse.button==3) {
						if (draggingPart) {
							draggingPart = false;
							ApplyChanges();
						}
					}
					break;
				}
				case ALLEGRO_EVENT_MOUSE_AXES: {
					if (al_mouse_button_down(&mS,3)) {
						if (draggingPart) {
						pEdit->x = mS.x+dragPartX;
						pEdit->y = mS.y+dragPartY;
						}
					}
									break;
											   }
			}

		}

	if (draggingFramePosition) {
		float percent = min(max(0,float((mS.x-scrubberLeft))/float(scrubberWidth)),1);
		animationFrames[frameEdit].timeFrame = percent;

	}
	
	this->renderer->animationPlayer.stepAnimation(timeStep,1);
}
void animationEditor::render(){
	al_set_target_backbuffer(this->display);
	al_clear_to_color(al_map_rgb(44,44,44));

	switch (partEdit) {
	case HEAD: al_draw_text(font,al_map_rgb(255,255,255),0,0,0,"HEAD"); break;
	case BODY: al_draw_text(font,al_map_rgb(255,255,255),0,0,0,"BODY"); break;
	case LEFTARM:al_draw_text(font,al_map_rgb(255,255,255),0,0,0,"LEFT ARM"); break;
	case RIGHTARM:al_draw_text(font,al_map_rgb(255,255,255),0,0,0,"RIGHT ARM"); break;
	case LEFTFOOT: al_draw_text(font,al_map_rgb(255,255,255),0,0,0,"LEFT FOOT"); break;
	case RIGHTFOOT: al_draw_text(font,al_map_rgb(255,255,255),0,0,0,"RIGHT FOOT"); break;
	}


	renderer->render(400,200,*this->editingPoint);
	al_draw_line(200, 200+29,600,200+29,al_map_rgb(255,255,255),1);
	
	renderer->render(400,500);
	al_draw_line(200, 500+29,600,500+29,al_map_rgb(255,255,255),1);

	static int width = 700;
	al_draw_filled_rectangle(scrubberLeft,scrubberTop,scrubberLeft+scrubberWidth,scrubberTop+scrubberHeight,al_map_rgb(99,99,99));
	for(unsigned int i=0; i<animationFrames.size(); i++) {
		ALLEGRO_COLOR col;
		if (i==frameEdit) {
			col = al_map_rgb(120,255,77);
		}else{
			col = al_map_rgb(255,0,0);
		}
		al_draw_line(scrubberLeft+(scrubberWidth*animationFrames[i].timeFrame),scrubberTop,scrubberLeft+(width*animationFrames[i].timeFrame),(scrubberTop+scrubberHeight),col,1);

	}
	al_flip_display();
}



void animationEditor::createRenderer(){
	character::characterCustomization *c = new character::characterCustomization();

		ALLEGRO_CONFIG* config = al_load_config_file("equip.ini");
	c->setEquipment(EQUIP_BELT,atoi(al_get_config_value(config,"Equip","belt")));
	c->setEquipment(EQUIP_GLOVE,atoi(al_get_config_value(config,"Equip","glove")));
	c->setEquipment(EQUIP_HELMET,atoi(al_get_config_value(config,"Equip","helmet")));
	c->setEquipment(EQUIP_PANTS,atoi(al_get_config_value(config,"Equip","pants")));
	c->setEquipment(EQUIP_SHIRT,atoi(al_get_config_value(config,"Equip","shirt")));
	c->setEquipment(EQUIP_SHOE,atoi(al_get_config_value(config,"Equip","shoe")));
	c->setEquipment(EQUIP_SHOULDER,atoi(al_get_config_value(config,"Equip","shoulder")));
	c->setEquipment(EQUIP_MAINHAND,atoi(al_get_config_value(config,"Equip","mainHand")));
	c->setEquipment(EQUIP_OFFHAND,atoi(al_get_config_value(config,"Equip","offHand")));
	c->setEquipment(EQUIP_RANGED,atoi(al_get_config_value(config,"Equip","ranged")));

	al_destroy_config(config);
	this->renderer = new character::characterRenderer(c);

	renderer->setAnimation(character::characterAnimationSequenceManager::getSequence(0),character::ANIMATION_LOOP);
}



void animationEditor::ApplyChanges() {
	
	aSeq->animationTimeframe = animationFrames;
	std::sort(aSeq->animationTimeframe.begin(),aSeq->animationTimeframe.end(),frameSort);
	renderer->setAnimation(aSeq,character::ANIMATION_LOOP);
}

int animationEditor::findAdjacentFrame(bool left, float pos){
	float distance = 1;
	int current = 0;
	for(unsigned int i=0; i<animationFrames.size(); i++) {
		if (animationFrames[i].timeFrame!=pos) {
			if (abs(pos-animationFrames[i].timeFrame)<distance) {
				if (left==1 && pos-animationFrames[i].timeFrame>0) {
					distance = abs(pos-animationFrames[i].timeFrame);
					current = i;
				}
				if (left==0 && pos-animationFrames[i].timeFrame<0) {
					distance = abs(pos-animationFrames[i].timeFrame);
					current = i;
				}
			}
		}

	}
	return current;
}

void animationEditor::setFrameEdit(int frameNum){
	frameEdit = frameNum;
	this->editingPoint = &animationFrames[frameNum];
}

void animationEditor::SaveAnimation(std::string fName) {
	ApplyChanges();
	std::fstream f(fName,std::ios::binary | std::ios::out);
	float buf;
	buf = 	aSeq->animationTimeframe.size();
	f.write(reinterpret_cast<char*>(&buf),sizeof(float));
	for(unsigned int i=0; i<aSeq->animationTimeframe.size(); i++) {
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].timeFrame),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].Head.x),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].Head.y),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].Head.rotation),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].body.x),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].body.y),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].body.rotation),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].leftHand.x),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].leftHand.y),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].leftHand.rotation),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].rightHand.x),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].rightHand.y),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].rightHand.rotation),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].leftFoot.x),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].leftFoot.y),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].leftFoot.rotation),sizeof(float));
		buf = aSeq->animationTimeframe[i].leftFoot.footState;
		f.write(reinterpret_cast<char*>(&buf),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].rightFoot.x),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].rightFoot.y),sizeof(float));
		f.write(reinterpret_cast<char*>(&aSeq->animationTimeframe[i].rightFoot.rotation),sizeof(float));
		buf = aSeq->animationTimeframe[i].rightFoot.footState;
		f.write(reinterpret_cast<char*>(&buf),sizeof(float));
	}

}

void animationEditor::LoadAnimation(std::string fName){
	animationFrames.clear();
	fName.replace(fName.find("."),fName.size()-fName.find("."),"");
	
	animationFrames = character::characterAnimationSequenceManager::getSequence(atoi(fName.c_str()))->animationTimeframe;

	setFrameEdit(0);
}