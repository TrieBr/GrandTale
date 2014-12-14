// ----------------------------------------------------------------------
// entityPlayerMe.h
//     Copyright � Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "entityPlayer.h"
#include "characterData.h" 


#ifndef _H_ENTITY_PLAYERME
#define _H_ENTITY_PLAYERME
namespace entities
{
	namespace gameMap
	{
		class entityPlayerMe: public entityPlayer {	
		public:
			entityPlayerMe(character::characterData *data) : entityPlayer(data) { }
			virtual void initialize();
			virtual void cleanup();
			virtual void render(float oX = 0,float oY = 0);
			virtual void update(double _timeFactor);
			bool handleEvent(ALLEGRO_EVENT &e);
			virtual float getX();
			virtual float getY();

			virtual character::characterAnimationSequence* getIdleSequence();
			virtual character::characterAnimationSequence* getRunSequence();
			virtual character::characterAnimationSequence* getJumpUpSequence();
			virtual character::characterAnimationSequence* getFallSequence();


			physicsController*				pController; //PHysics controller

		private:
			void handleJumpingAnimation();
		};

	}

}

#endif