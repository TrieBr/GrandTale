#include <miscPlayerData.h>

void miscPlayerData::setRemainingStatPoints(unsigned short points) {
	remainingStatPoints = points;
}

unsigned short miscPlayerData::getRemainingStatPoints() {
	return remainingStatPoints;
}


void miscPlayerData::writeData(RakNet::BitStream &data, unsigned int dataSend) {
	data.Write<unsigned int>(dataSend);
	if ((dataSend & MISC_DATA_REMAINING_STAT_POINTS)==MISC_DATA_REMAINING_STAT_POINTS) {
		data.Write<unsigned short>(getRemainingStatPoints());
	}

}
void miscPlayerData::readData(RakNet::BitStream &data) {
	unsigned int receivedData;
	data.Read<unsigned int>(receivedData);
	if ((receivedData & MISC_DATA_REMAINING_STAT_POINTS)==MISC_DATA_REMAINING_STAT_POINTS) {
		data.Read<unsigned short>(remainingStatPoints);
	}

}