#include "abstractSkillHandler.h"

class skillHandler_1 : public abstractSkillHandler {
public:

	virtual void Handle(entities::gameMap::entityPlayer* playerHandler) {
		if (this->skillState==0) {
			playerHandler->getRenderer()->animationPlayer.overrideTopAnimation();
			playerHandler->getRenderer()->animationPlayer.getTopOverrideAnimation()->setCurrentState(playerHandler->getRenderer()->animationPlayer.getCurrentState());

			Item mainHand = globalData::getItemManager()->GetItem(playerHandler->cData->getEquipment(EQUIP_MAINHAND));
			Item offHand = globalData::getItemManager()->GetItem(playerHandler->cData->getEquipment(EQUIP_OFFHAND));
			if (equipmentConfiguration::isTwoHand(mainHand,offHand)) {
				playerHandler->getRenderer()->animationPlayer.getTopOverrideAnimation()->setAnimation(character::characterAnimationSequenceManager::getSequence(18),character::ANIMATION_PLAY_ONCE,  true,0.06,0.6);
			}else{
				playerHandler->getRenderer()->animationPlayer.getTopOverrideAnimation()->setAnimation(character::characterAnimationSequenceManager::getSequence(17),character::ANIMATION_PLAY_ONCE,  true,0.06,0.6);

			}
			

		//	playerHandler->getRenderer()->animationPlayer.overrideBottomAnimation();
			//playerHandler->getRenderer()->animationPlayer.getBottomOverrideAnimation()->setCurrentState(playerHandler->getRenderer()->animationPlayer.getCurrentState());
		//	playerHandler->getRenderer()->animationPlayer.getBottomOverrideAnimation()->setAnimation(character::characterAnimationSequenceManager::getSequence(17),character::ANIMATION_PLAY_ONCE,  true,0.06,0.6);

			skillState= 1;
		}

	}

	virtual void ExecuteSkill() {
		this->::abstractSkillHandlerDummy::ExecuteSkill();
		skillState = 0;
	}

		

};