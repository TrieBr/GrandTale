#include <stats.h>
#include <BitStream.h>

#ifndef _H_COMBATENTITYSTATS
#define _H_COMBATENTITYSTATS
class combatEntityStats {
public:
	void setBaseStat(int stat, unsigned short val);
	unsigned short getBaseStat(int stat);

	void setBonusStat(int stat, unsigned short val);
	unsigned short getBonusStat(int stat);

	unsigned short getTotalStat(int stat);

	virtual void readData(RakNet::BitStream &data);
	virtual void writeData(RakNet::BitStream &data);
private:
	unsigned short base_stats[STAT_COUNT];
	unsigned short bonus_stats[STAT_COUNT];



};

#endif