
#include "characterData.h"

namespace character {

void characterData::readCharacterData(RakNet::BitStream &data) {
		RakNet::RakString characterName;
		data.Read<RakNet::RakString>(characterName); //Read the ID
		charName = characterName.C_String();

		
		readCharacterCustomization(data); //Read customization components
	}
	void characterData::writeCharacterData(RakNet::BitStream &data) {
		data.Write<RakNet::RakString>((RakNet::RakString)charName.c_str());

		writeCharacterCustomization(data); //Write customization components 


	}


		//Set name of character
		void characterData::setCharacterName(std::string name) {
			charName = name;
		}
		//Get character name
		std::string characterData::getCharacterName() {
			return charName;
		}
		//Set Map ID
		void characterData::setMapID(int id) {
			mapID = id;
		}
		//Get the map ID
		int characterData::getMapID() {
			return mapID;
		}
}