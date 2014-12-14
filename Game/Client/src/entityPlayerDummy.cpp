#include "entityPlayerDummy.h"
#include "characterAnimationSequenceManager.h"

namespace entities
{
	namespace gameMap
	{
		void entityPlayerDummy::initialize(){
			this->namePlateFont =  gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);
			lastX = this->getX();
			lastY = this->getY();
			destX = this->getX();
			destY = this->getY();
			updateInterval = 1/5;
			lSet = false;
		}
		void entityPlayerDummy::cleanup(){
			delete renderer;
		}
		void entityPlayerDummy::render(float oX,float oY){
			
			if (getX()+oX+100 > 0 && getX()+oX-100 < 800 && getY()+oY+100 > 0 && getY()+oY-100<600) { //TODO: Retreive actual screen dimensions, and possible chracter dimensions
					renderer->render(getX()+oX,getY()+oY,lastDirection);
					int w = al_get_text_width(this->namePlateFont,this->cData->getCharacterName().c_str());
					al_draw_filled_rectangle(getX()+oX-(w/2)-2,getY()+oY+29,getX()+oX+(w/2)+2,getY()+oY+48,al_map_rgba(0,0,0,180));
					al_draw_textf(this->namePlateFont,al_map_rgb(255,255,255),getX()+oX,getY()+oY+23,ALLEGRO_ALIGN_CENTRE,this->cData->getCharacterName().c_str());
			}
			this->getSpeechBubbleHandler()->render(getX()+oX,getY()+oY-75);
		}
		void entityPlayerDummy::update(double _timeFactor){

			renderer->animationPlayer.stepAnimation(_timeFactor,1);
			this->setX(this->getX()+(((destX-lastX)/(60/20))*_timeFactor));
			if ((destX-lastX<0 && this->getX()  < destX)||(destX-lastX>0 && this->getX() > destX)) {
				this->setX(destX);
			
			}
			this->setY(this->getY() +(((destY-lastY)/(60/20))*_timeFactor));
			if ((destY-lastY<0 && this->getY()  < destY) || (destY-lastY>0 && this->getY()  > destY)) {
				this->setY(destY);
		
			}		

			this->getSpeechBubbleHandler()->update(_timeFactor);

			for (int i=0; i<this->getSkillHandlerCount(); i++) {
					this->getSkillHandlerAt(i)->Handle(this);
				}

		}

		void entityPlayerDummy::updatePosition(positionUpdate& updateData){
			if (lSet==false) {
				lastUpdateData = updateData;
				lSet = true;
			}
			lastX = this->getX();
			lastY = this->getY();
			destX = updateData.X;
			destY = updateData.Y;

				lastDirection = lastUpdateData.left;
				if(lastUpdateData.animationChanged) {
					this->renderer->setAnimation(character::characterAnimationSequenceManager::getSequence(lastUpdateData.animationID),character::ANIMATION_LOOP,  (lastUpdateData.animationBlend!=0), lastUpdateData.animationBlend);
					this->renderer->animationPlayer.setCurrentPosition(lastUpdateData.animationPosition);
				}
			lastUpdateData = updateData;
		}

	}
}