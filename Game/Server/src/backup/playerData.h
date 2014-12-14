// ----------------------------------------------------------------------
// playerData.h
//     Copyright © Brad Triebwasser 2010
/* Description:
		Contains data on a players inventory, map info, character information, etc
*/
// ------------------------------------------------------------------------



#include "characterData.h"

#ifndef _H_PLAYERDATA
#define _H_PLAYERDATA
class map;
class playerData {
public:
	character::characterData character;
};

#endif