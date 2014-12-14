// ----------------------------------------------------------------------
// abstractEntity.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	Abstract entity that all other entities should derive from
*/
// ------------------------------------------------------------------------
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <allegro5/allegro.h>

#ifndef _ABSTRACTENTITY_
#define _ABSTRACTENTITY_

namespace gameEngine {
	class abstractWorld;

	class abstractEntity
	{
	public:
		virtual ~abstractEntity() {} 
		virtual void initialize() = 0; //Initialize the entity
		virtual void cleanup() = 0; //Cleanup/deinitialize the entity
		virtual void update(double _timeFactor) = 0; //Update the entity
		virtual void render(float offsetX = 0, float offsetY = 0) = 0; //Render the entity
		template <class T>
		T* getParentWorld() { //Returns the parent world
			return reinterpret_cast<T*>(parentWorld);
		}
		void setParentWorld(abstractWorld* newParent) { //Set the new parent world
			parentWorld = newParent;
		}
		virtual bool handleEvent(ALLEGRO_EVENT &e) { return false;}
		void setDepth(int newDepth, bool sort = true); 

		bool operator<(const abstractEntity &entity) const {
			return  (this->depth < entity.depth);
		}
		
	private:
		int depth;
	protected:
		abstractWorld* parentWorld;
		
	};
}

#endif 