
#include "entityPlayerMe.h"
#include "characterAnimationSequenceManager.h"
#include "worldGameMap.h"
#include "gameServer.h"
#include "myData.h"
#include "globalData.h"
#include <equipmentConfiguration.h>
namespace entities
{
	namespace gameMap
	{
		
		void entityPlayerMe::initialize() {
				pController = new physicsController(physicsController::getDefaultPlayerPhysics(),this->getParentWorld<worlds::worldGameMap>()->mHandler->mData);
				
				pController->setDimensions((62/2),64,(62/2),26);

				this->namePlateFont =  gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);
				myData::myPlayer = this;
			}
			void entityPlayerMe::cleanup() {
				delete pController;
				delete renderer;
				myData::myPlayer = NULL;
			}
			void entityPlayerMe::render(float oX,float oY) {
				physicsState pS = pController->getState();

				if (pController->getState().hVelocity>0) {
					renderer->render(pS.x+oX,pS.y+oY,false);
				} else if (pController->getState().hVelocity<0) {
					renderer->render(pS.x+oX,pS.y+oY,true);
				}else{
					renderer->render(pS.x+oX,pS.y+oY,lastDirection);
				}
			
				int w = al_get_text_width(this->namePlateFont,this->cData->getCharacterName().c_str());
				al_draw_filled_rectangle(pS.x+oX-(w/2)-2,pS.y+oY+29,pS.x+oX+(w/2)+2,pS.y+oY+48,al_map_rgba(0,0,0,180));
					al_draw_textf(this->namePlateFont,al_map_rgb(255,255,255),pS.x+oX,pS.y+oY+23,ALLEGRO_ALIGN_CENTRE,this->cData->getCharacterName().c_str());

					this->getSpeechBubbleHandler()->render(pS.x+oX,pS.y+oY-75);
			}
			void entityPlayerMe::update(double _timeFactor) {
				handleJumpingAnimation();
				renderer->animationPlayer.stepAnimation(_timeFactor); //Step the animation
				pController->step(_timeFactor);
				this->getSpeechBubbleHandler()->update(_timeFactor);
				for (int i=0; i<this->getSkillHandlerCount(); i++) {
					this->getSkillHandlerAt(i)->Handle(this);
				}
			}

		bool entityPlayerMe::handleEvent(ALLEGRO_EVENT &e) {
				if (e.type==ALLEGRO_EVENT_KEY_DOWN) {
					if (e.keyboard.keycode==ALLEGRO_KEY_LEFT) {
						pController->getState().left = true;
						lastDirection = true; //LEft
						currentMovement |= MOVE_LEFT;
						
							renderer->setAnimation(getRunSequence(),character::ANIMATION_LOOP,  true,0.06);
						if (((currentMovement & MOVE_RIGHT)==MOVE_RIGHT)) {
							renderer->setAnimation(getIdleSequence(),character::ANIMATION_LOOP,  true,0.3);
						}
						//renderer->setResumeSequence(character::characterAnimationSequenceManager::getSequence(3),character::ANIMATION_LOOP,  true,0.06);
					}
					if (e.keyboard.keycode==ALLEGRO_KEY_RIGHT) {
						pController->getState().right = true;
						lastDirection = false; //Right
						currentMovement |= MOVE_RIGHT;
						
							renderer->setAnimation(getRunSequence(),character::ANIMATION_LOOP,true,0.06);

						if (((currentMovement & MOVE_LEFT)==MOVE_LEFT)) {
							renderer->setAnimation(getIdleSequence(),character::ANIMATION_LOOP,  true,0.3);
						}
						//renderer->setResumeSequence(character::characterAnimationSequenceManager::getSequence(3),character::ANIMATION_LOOP,  true,0.06);
					}
					if (e.keyboard.keycode==ALLEGRO_KEY_UP) {
						pController->getState().up = true;
						pController->hop(25,true);
						pController->getState().y -= 1;
						
					}
				}

				if (e.type==ALLEGRO_EVENT_KEY_UP) {
					if (e.keyboard.keycode==ALLEGRO_KEY_LEFT) {
						pController->getState().left = false;
						currentMovement &= ~MOVE_LEFT;
						if (!((currentMovement & MOVE_RIGHT)==MOVE_RIGHT)) {
							renderer->setAnimation(getIdleSequence(),character::ANIMATION_LOOP,  true,0.3);
						}else{
							lastDirection = false;//Right
							renderer->setAnimation(getRunSequence(),character::ANIMATION_LOOP,true,0.06);
						}
					}
					if (e.keyboard.keycode==ALLEGRO_KEY_RIGHT) {
						pController->getState().right = false;
						currentMovement &= ~MOVE_RIGHT;
						if (!((currentMovement & MOVE_LEFT)==MOVE_LEFT)) {
							renderer->setAnimation(getIdleSequence(),character::ANIMATION_LOOP,  true,0.3);
						}else{
							lastDirection = true; //LEft
							renderer->setAnimation(getRunSequence(),character::ANIMATION_LOOP,true,0.06);
						}
					}
					if (e.keyboard.keycode==ALLEGRO_KEY_UP) {
						pController->getState().up = false;
					}
				}
				return false;
			}

		float entityPlayerMe::getX() {
				return pController->getState().x;
			}
		float entityPlayerMe::getY() {
			return pController->getState().y;
		}

		void entityPlayerMe::handleJumpingAnimation(){
			if (lastY>getY()){
				if (!((currentMovement & JUMPING)==JUMPING)) {
					currentMovement |= JUMPING;
					currentMovement &= ~FALLING;
					renderer->setAnimation(getJumpUpSequence(),character::ANIMATION_LOOP, true,0.1);
				}
			}

			if (lastY<getY()){
				if (((currentMovement & JUMPING)==JUMPING)) {
					currentMovement &= ~JUMPING;
					currentMovement |= FALLING;
					renderer->setAnimation(getFallSequence(),character::ANIMATION_LOOP,  true,0.1);
				}else{
					currentMovement |= FALLING;
					renderer->setAnimation(getFallSequence(),character::ANIMATION_LOOP,  true,0.1);
				}
			}
			if (lastY==getY()){
				if (((currentMovement & FALLING)==FALLING)) {
					currentMovement &= ~FALLING;
					currentMovement &= ~JUMPING;
					if ((((currentMovement & MOVE_LEFT)==MOVE_LEFT) ||  ((currentMovement & MOVE_RIGHT)==MOVE_RIGHT)) && !(((currentMovement & MOVE_LEFT)==MOVE_LEFT) &&  ((currentMovement & MOVE_RIGHT)==MOVE_RIGHT)))  {
						renderer->setAnimation(getRunSequence(),character::ANIMATION_LOOP, true,0.07);
					}else{
						renderer->setAnimation(getIdleSequence(),character::ANIMATION_LOOP, true,0.07);
					}
					
				}
			}
			lastY = getY();
		}


			character::characterAnimationSequence* entityPlayerMe::getIdleSequence() {
                return character::characterAnimationSequenceManager::getSequence(12);
				/*if (equipmentConfiguration::isTwoHand(globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_MAINHAND).itemID),globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_OFFHAND).itemID))) {
					return character::characterAnimationSequenceManager::getSequence(12);
				}else{
					return character::characterAnimationSequenceManager::getSequence(0);
				}*/
			}
			character::characterAnimationSequence* entityPlayerMe::getRunSequence() {
                return character::characterAnimationSequenceManager::getSequence(4);
                /*
				if (equipmentConfiguration::isDialWielding(globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_MAINHAND).itemID),globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_OFFHAND).itemID))) {
					return character::characterAnimationSequenceManager::getSequence(4);
				}else if (equipmentConfiguration::isTwoHand(globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_MAINHAND).itemID),globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_OFFHAND).itemID))) {
					return character::characterAnimationSequenceManager::getSequence(7);
				}else{
					return character::characterAnimationSequenceManager::getSequence(3);
				}*/
			}
			character::characterAnimationSequence* entityPlayerMe::getJumpUpSequence() {
                return character::characterAnimationSequenceManager::getSequence(13);
                /*
				if (equipmentConfiguration::isTwoHand(globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_MAINHAND).itemID),globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_OFFHAND).itemID))) {
					return character::characterAnimationSequenceManager::getSequence(13);
				}else{
					return character::characterAnimationSequenceManager::getSequence(1);
				}*/
			}
			character::characterAnimationSequence* entityPlayerMe::getFallSequence() {
                return character::characterAnimationSequenceManager::getSequence(14);
                /*
				if (equipmentConfiguration::isTwoHand(globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_MAINHAND).itemID),globalData::getItemManager()->GetItem(myData::equipmentContainer.getItem(EQUIP_OFFHAND).itemID))) {
					return character::characterAnimationSequenceManager::getSequence(14);
				}else{
					return character::characterAnimationSequenceManager::getSequence(2);
				}*/
			}
	}

}