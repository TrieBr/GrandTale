#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <string>
#include <BitStream.h>
#include <characterCustomization.h>
#include <item.h>

#ifndef _H_CHARDATA
#define _H_CHARDATA

class GTGameClient;
class queries;
class characterCreate;
namespace character {
	class characterData : public characterCustomization{ //Stores data for a character
	private:
		std::string charName;
		int mapID;
	public:
		void readCharacterData(RakNet::BitStream &data);
		void writeCharacterData(RakNet::BitStream &data);

		//Set name of character
		void setCharacterName(std::string name);
		//Get character name
		std::string getCharacterName();
		//Set Map ID
		void setMapID(int id);
		//Get the map ID
		int getMapID();
	};

}
#endif