// ----------------------------------------------------------------------
// abstractWorld.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	The abstract world that all other worlds need to derive from.
*/
// ------------------------------------------------------------------------
#include <vector>
#include "abstractEntity.h"
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <allegro5/allegro.h>

#ifndef _ABSTRACTWORLD_
#define _ABSTRACTWORLD_

namespace gameEngine {
	class abstractWorld
	{
	public:
		virtual void initialize(); //Initialize the world
		virtual void cleanup(); //Cleanup (deinitialize) the world
		virtual void update(double _timeFactor);  //Update the world
		virtual void render(float offsetX = 0, float offsetY = 0); //Render the world
		virtual void addEntity(abstractEntity* newEntity); //Add an entity that the world will control
		virtual void removeEntity(abstractEntity* entityRemove, bool deleteEntity = true); //Remove an entity that the world will control
		void sortEntityDepth(); //Sorts entities based on depth
	private:
		std::vector<abstractEntity*> entityList; //The children entities of this world
	protected:
		ALLEGRO_EVENT_QUEUE* eventQueue;
	};
}

#endif