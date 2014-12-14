#include "monster.h"


monster::monster() : mobDummy() {
	this->mRenderer = NULL;
	lastDirectionRight = true;
	platform = NULL;
	namePlateFont =  gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",11);
	this->beingHit = false;
}
monster::~monster() {
	if (mRenderer!=NULL) delete mRenderer;
}
void monster::loadRenderer() {
	mRenderer = new monsterRenderer();
	mRenderer->load(this->getID());
}
void monster::stateChanged() {
	if (beingHit) {
		if (getCurrentHealth()>0) {
			mRenderer->playAnimation(MONSTER_ANIM_HIT, true);
			if (getLastHitData().direction==HIT_DIRECTION_FROM_LEFT)
					setKnockbackSpeed(3);
			else
				setKnockbackSpeed(-3);
		}else{
			mRenderer->playAnimation(MONSTER_ANIM_DYING, true);
		}
		return;
	}
	if (getSpeed()!=0) {
		mRenderer->playAnimation(MONSTER_ANIM_RUN, true); 
		lastDirectionRight = false;
		if (getSpeed()>0) lastDirectionRight = true;
		
	}else{
		mRenderer->playAnimation(MONSTER_ANIM_IDLE, true);
	}
}

void monster::initialize() { //Initialize the entity

}
void monster::cleanup() { //Cleanup/deinitialize the entity
}
void monster::update(double _timeFactor) { //Update the entity
	if (beingHit) {
		if (hitAnimationTimer>0) { hitAnimationTimer-=0.06*_timeFactor; }else{
			beingHit=false;
			stateChanged();
		}
		this->setX(this->getX()+(double)this->getKnockbackSpeed()*_timeFactor);
	}else{
		this->setX(this->getX()+(double)this->getSpeed()*_timeFactor);
	}
	mRenderer->updateAnimation(_timeFactor);
	if (getX()>platform->p2.x) { setX(platform->p2.x); }
	if (getX()<platform->p1.x) { setX(platform->p1.x); }
	if (isFalling()) {
		
		if (getY()>platform->p1.y) {
			stopFalling();

		}
		setY(getY()+2*_timeFactor);
	}

}
void monster::render(float offsetX , float offsetY ) { //Render the entity

	mRenderer->render(getX()+offsetX,getY()+offsetY, lastDirectionRight ? true : false);

	
	al_draw_filled_rectangle(getX()+offsetX-32,getY()+offsetY+8,getX()+offsetX+32,getY()+offsetY+14,al_map_rgb(36,36,36));
	float healthPercent = (float)this->getCurrentHealth()/(float)this->getTotalStat(STAT_HP);

	al_draw_filled_rectangle(getX()+offsetX-32,getY()+offsetY+8,getX()+offsetX-32+(64*healthPercent),getY()+offsetY+14,al_map_rgb(69,189,0));
	al_draw_filled_rectangle(getX()+offsetX-32,getY()+offsetY+9,getX()+offsetX-32+(64*healthPercent),getY()+offsetY+11,al_map_rgb(88,232,0));

	al_draw_rectangle(getX()+offsetX-32,getY()+offsetY+8,getX()+offsetX+32,getY()+offsetY+14,al_map_rgb(150,150,150),1);


	int w = al_get_text_width(this->namePlateFont,this->getName().c_str());
	al_draw_filled_rectangle(getX()+offsetX -(w/2)-2,getY()+offsetY+14,getX()+offsetX +(w/2)+2,getY()+offsetY+26,al_map_rgba(0,0,0,180));
	al_draw_textf(this->namePlateFont,al_map_rgb(232,213,9),getX()+offsetX,getY()+offsetY+9,ALLEGRO_ALIGN_CENTRE,this->getName().c_str());
}

void monster::hit(hitData &data) {
	this->::combatEntity::hit(data);
	this->beingHit = true;
	this->hitAnimationTimer = 1;
	stateChanged();
}

