// ----------------------------------------------------------------------
// abstractEntity.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------
#include "abstractEntity.h"
#include "abstractWorld.h"

namespace gameEngine {

	void abstractEntity::setDepth(int newDepth, bool sort) {
			depth = newDepth;
			if (sort) {
				this->parentWorld->sortEntityDepth(); //Re sort the depths
			}
		}
}