
/*
Reads a map file from an ALLEGRO_FILE*

*/

#include "mapData.h"

enum mapReaderOptions {
	SKIPTILES = 1,
	SKIPBACKGROUNDS = 2,
};

class mapReader {
public:
	mapReader(mapData *mData, int optionFlags = 0);
	void setData(mapData *mData);
	void readData(ALLEGRO_FILE* fileStream);
	void setOptions(int optionFlags);
private:
	int		options;
	mapData* _mData;
};