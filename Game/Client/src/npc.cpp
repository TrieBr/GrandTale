#include "npc.h"
#include "characterAnimationSequenceManager.h"

npc::npc() : mobDummy() {
	this->cRenderer = NULL;
	lastDirectionRight = true;
	platform = NULL;
	namePlateFont =  gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",11);

}
npc::~npc() {
	if (cRenderer!=NULL) delete cRenderer;
}
void npc::loadRenderer() {
	cRenderer = new character::characterRenderer(&customization);
	cRenderer->setAnimation(character::characterAnimationSequenceManager::getSequence(SEQ_IDLE),character::ANIMATION_LOOP); 
	
}
void npc::stateChanged() {
	if (getSpeed()!=0) {
		//mRenderer->playAnimation(MonsterAnimationType::MONSTER_ANIM_RUN, true);
		lastDirectionRight = false;
		if (getSpeed()>0) lastDirectionRight = true;
		
	}else{
		//mRenderer->playAnimation(MonsterAnimationType::MONSTER_ANIM_IDLE, true);
	}
}

void npc::initialize() { //Initialize the entity

}
void npc::cleanup() { //Cleanup/deinitialize the entity
}
void npc::update(double _timeFactor) { //Update the entity
	this->setX(this->getX()+(double)this->getSpeed()*_timeFactor);
	//mRenderer->updateAnimation(_timeFactor);
	if (getX()>platform->p2.x) { setX(platform->p2.x); }
	if (getX()<platform->p1.x) { setX(platform->p1.x); }
	if (isFalling()) {
		
		if (getY()>platform->p1.y) {
			stopFalling();

		}
		setY(getY()+2*_timeFactor);
	}

}
void npc::render(float offsetX , float offsetY ) { //Render the entity

	cRenderer->render(getX()+offsetX,getY()+offsetY-27, !lastDirectionRight ? true : false);

	
	al_draw_filled_rectangle(getX()+offsetX-32,getY()+offsetY+8,getX()+offsetX+32,getY()+offsetY+14,al_map_rgb(36,36,36));
	float healthPercent = 0.5;

	al_draw_filled_rectangle(getX()+offsetX-32,getY()+offsetY+8,getX()+offsetX-32+(64*healthPercent),getY()+offsetY+14,al_map_rgb(69,189,0));
	al_draw_filled_rectangle(getX()+offsetX-32,getY()+offsetY+9,getX()+offsetX-32+(64*healthPercent),getY()+offsetY+11,al_map_rgb(88,232,0));

	al_draw_rectangle(getX()+offsetX-32,getY()+offsetY+8,getX()+offsetX+32,getY()+offsetY+14,al_map_rgb(150,150,150),1);


	int w = al_get_text_width(this->namePlateFont,this->getName().c_str());
	al_draw_filled_rectangle(getX()+offsetX -(w/2)-2,getY()+offsetY+14,getX()+offsetX +(w/2)+2,getY()+offsetY+26,al_map_rgba(0,0,0,180));
	al_draw_textf(this->namePlateFont,al_map_rgb(232,213,9),getX()+offsetX,getY()+offsetY+9,ALLEGRO_ALIGN_CENTRE,this->getName().c_str());
	
}

void npc::readCombatData(RakNet::BitStream &data) {
	this->::mobDummy::readCombatData(data);
	this->customization.readCharacterCustomization(data);
}
void npc::writeCombatData(RakNet::BitStream &data) {
	this->::mobDummy::writeCombatData(data);
	this->customization.writeCharacterCustomization(data);
}

