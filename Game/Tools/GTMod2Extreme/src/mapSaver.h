#include "mapData.h"

class mapSaver {
private:
	mapData _mData;
public:
	mapSaver (mapData &mData);
	void setData(mapData &mData);
	void writeData(ALLEGRO_FILE* fileStream);
};