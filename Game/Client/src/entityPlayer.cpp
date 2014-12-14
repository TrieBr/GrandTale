
#include "entityPlayer.h"

#include "worldGameMap.h"
namespace entities
{
	namespace gameMap
	{
		entityPlayer::entityPlayer(character::characterData *data) {
			cData = data;
			renderer = new character::characterRenderer(cData);
			renderer->setAnimation(character::characterAnimationSequenceManager::getSequence(0),character::ANIMATION_LOOP);
			jumpingUp = false;
			fallingDown = false;
			lastY = getY();
			currentMovement = 0;
			
		}

		
		character::characterAnimationSequence* entityPlayer::getIdleSequence() {
			return character::characterAnimationSequenceManager::getSequence(0);
		}
		character::characterAnimationSequence* entityPlayer::getRunSequence() {
			return character::characterAnimationSequenceManager::getSequence(3);
		}
		character::characterAnimationSequence* entityPlayer::getJumpUpSequence() {
			return character::characterAnimationSequenceManager::getSequence(1);
		}
		character::characterAnimationSequence* entityPlayer::getFallSequence() {
			return character::characterAnimationSequenceManager::getSequence(2);
		}
			
			

			
			


	}

}