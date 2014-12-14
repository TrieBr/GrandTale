// ----------------------------------------------------------------------
// abstractWorld.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	The abstract world that all other worlds need to derive from.
*/
// ------------------------------------------------------------------------

#include "abstractWorld.h"
#include <algorithm>

namespace gameEngine {

		void  abstractWorld::initialize() { //Initialize the world
			eventQueue = al_create_event_queue();
		}

		void abstractWorld::cleanup() { //Cleanup (deinitialize) the world
			for (unsigned int i=0; i<this->entityList.size(); i++) { //For each entity that is still active
				this->entityList[i]->cleanup(); //Clean up the entity
				delete this->entityList[i]; //Delete the entity
			}
			this->entityList.clear(); //Clear the vector
			al_destroy_event_queue(eventQueue);
		}

		void abstractWorld::update(double _timeFactor) {  //Update the world
			ALLEGRO_EVENT ev;
			if (al_get_next_event(eventQueue, &ev) ) { //Event has happened.
				for (int i = this->entityList.size()-1; i>=0; i-=1) { //For each entity that is still active
					if (this->entityList[i]->handleEvent(ev))
						break; //Pass the event down, if it returns true it was handled, and we break
				}
			}
			for (unsigned int i=0; i<this->entityList.size(); i++) { //For each entity that is still active
				this->entityList[i]->update(_timeFactor); //Update the entity
			}
		}

		void abstractWorld::render(float offsetX, float offsetY) { //Render the world
			for (unsigned int i=0; i<this->entityList.size(); i++) { //For each entity that is still active
				this->entityList[i]->render(offsetX, offsetY); //render the entity
			}
		}

		void abstractWorld::addEntity(abstractEntity* newEntity) { //Add an entity that the world will control
			newEntity->setParentWorld(this);
			newEntity->setDepth(0);
			newEntity->initialize(); //Initialize the new identity
			this->entityList.push_back(newEntity); //Add the new entity
			
		}

		void abstractWorld::removeEntity(abstractEntity* entityRemove, bool deleteEntity) { //Remove an entity that the world will control

			for (unsigned int i=0; i<this->entityList.size(); i++) { //For each entity that is still active
				if (this->entityList[i]==entityRemove) { //If the entiry is the entity we want to delete
					if (deleteEntity) { //If we need to cleanup/delete
						this->entityList[i]->cleanup(); //Clean up the entity
						delete this->entityList[i]; //Delete the entity
					}
					this->entityList.erase(this->entityList.begin()+i); //Delete from the vector
					break;
				}
			}
		}

		bool entitySort (abstractEntity* one, abstractEntity* two) { return (*one<*two); }

		void abstractWorld::sortEntityDepth() { //Sorts entities based on depth
			std::sort(this->entityList.begin(),this->entityList.end(),entitySort);
			std::reverse(this->entityList.begin(),this->entityList.end());
		}

}