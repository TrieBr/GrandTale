#include <combatEntityStats.h>



	void combatEntityStats::setBaseStat(int stat, unsigned short val) {
		base_stats[stat] = val;
	}

	unsigned short combatEntityStats::getBaseStat(int stat) {
		return base_stats[stat];
	}

	void combatEntityStats::setBonusStat(int stat, unsigned short val) {
		bonus_stats[stat] = val;
	}
	unsigned short combatEntityStats::getBonusStat(int stat) {
		return bonus_stats[stat];
	}

	unsigned short combatEntityStats::getTotalStat(int stat) {
		return base_stats[stat]+bonus_stats[stat];
	}

	void combatEntityStats::readData(RakNet::BitStream &data) {
		for (int i=0; i <STAT_COUNT; i++) {
			data.Read<unsigned short>(base_stats[i]);
			data.Read<unsigned short>(bonus_stats[i]);
			
		}
	}
	void combatEntityStats::writeData(RakNet::BitStream &data) {
		for (int i=0; i <STAT_COUNT; i++) {
			data.Write<unsigned short>(getBaseStat(i));
			data.Write<unsigned short>(getBonusStat(i));
		}
	}
