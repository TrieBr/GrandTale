

#include "entityPlayer.h"
#include <combatEntity.h>
#ifndef _H_ENTITY_PLAYERDUMMY
#define _H_ENTITY_PLAYERDUMMY
namespace entities
{
	namespace gameMap
	{
		class entityPlayerDummy: public entityPlayer {	
		public:
			entityPlayerDummy(character::characterData *data, short UIDnumber) : entityPlayer(data) {  UID = UIDnumber;}
			virtual void initialize();
			virtual void cleanup();
			virtual void render(float oX = 0,float oY = 0);
			virtual void update(double _timeFactor);
			short getUID() { return UID; }
			void updatePosition(positionUpdate& updateData);
		private:
			
			short UID;
			double updateInterval;
			float destX, destY, lastX, lastY;
			bool lSet;
			positionUpdate lastUpdateData;
			
		};

	}

}

#endif