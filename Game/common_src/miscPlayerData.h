#include <BitStream.h>

#ifndef _H_MISCPLAYERDATA
#define _H_MISCPLAYERDATA


/* Contains miscplayer data such as settings, etc. */

enum MISC_DATA_TYPES {
	MISC_DATA_REMAINING_STAT_POINTS = 1,

	MISC_DATA_ALL = 0xFFFFFFFF
};

class miscPlayerData {
public:
	void setRemainingStatPoints(unsigned short points);
	unsigned short getRemainingStatPoints();

	void writeData(RakNet::BitStream &data, unsigned int dataSend = MISC_DATA_ALL);
	void readData(RakNet::BitStream &data);
private:
	unsigned short remainingStatPoints; //Number of stat points remaining to spend

};

#endif