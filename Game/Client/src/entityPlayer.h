#include "gameEngine.h"
#include "characterRenderer.h"
#include "characterData.h"
#include <string>
#include "physicsController.h"
#include "characterAnimationSequenceManager.h"
#include "playerSpeechBubble.h"
#include "skillHandlerRunner.h"
#include <combatEntity.h>
#ifndef _H_ENTITY_PLAYER
#define _H_ENTITY_PLAYER

struct positionUpdate {
	float X;
	float Y;
	bool animationChanged;
	unsigned short animationID;
	float animationPosition;
	float animationBlend;
	bool left; //Direction
};

namespace entities
{
	namespace gameMap
	{

		enum movementType{
			JUMPING = 1,
			FALLING = 2,
			MOVE_LEFT = 4,
			MOVE_RIGHT = 8,
			IDLE = 16
		};
		class entityPlayer: public gameEngine::abstractEntity, public skillHandlerRunner, public combatEntity
		{
		public:
			entityPlayer(character::characterData *data);
			virtual void initialize() = 0;
			virtual void cleanup() = 0;
			virtual void render(float oX = 0,float oY = 0) = 0;
			virtual void update(double _timeFactor) = 0;
			virtual bool handleEvent(ALLEGRO_EVENT &e) { return false; }
			void handleJumpingAnimation();
			character::characterRenderer *getRenderer() { return renderer; }
			
			float alpha;
			bool lastDirection; //true left, false right
			character::characterData		*cData;
			playerSpeechBubble* getSpeechBubbleHandler() { return &speechBubble; }

			virtual character::characterAnimationSequence* getIdleSequence();
			virtual character::characterAnimationSequence* getRunSequence();
			virtual character::characterAnimationSequence* getJumpUpSequence();
			virtual character::characterAnimationSequence* getFallSequence();

		protected:
			character::characterRenderer	*renderer;
			ALLEGRO_FONT*					namePlateFont;

			unsigned int currentMovement;

			float lastY;
			bool jumpingUp;
			bool fallingDown;

			
			playerSpeechBubble speechBubble;				
			
		};

	}

}

#endif