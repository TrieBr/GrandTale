

#ifndef _H_HITDATA
#define _H_HITDATA

enum HitDirection {
	HIT_DIRECTION_FROM_LEFT,
	HIT_DIRECTION_FROM_RIGHT
};


struct hitData {
	int damage;
	unsigned char direction; 

};

#endif