#include "packetProcessor.h"
#include "GTLoginClient.h"

class characterCreate : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
	RakNet::RakString		characterName;
	character::characterData customization;
	data.Read<RakNet::RakString>(characterName);
	customization.charName = characterName;
	customization.readCharacterCustomization(data);

	gameDB.query(RakNet::RakString("INSERT INTO characters (userid, charname, mapid, x, y, hairtype, haircolor, facialHairType, eyeType, mouthType, skincolor, race, gender)\
																						VALUES   (%i, '%s', %i,%i, %i, %i, %i, %i, %i, %i, %i, %i, %i )",
																						c.dbID, //User ID
																						customization.charName.C_String(), //Charname
																						0, //mapid
																						0, //x
																						0, //y
																						customization.hairType, //Hair type
																						customization.hairColor, //Hair color
																						customization.facialHairType, //Facial hair type
																						customization.eyeType, //Eye type
																						customization.mouthType, //Mouth type
																						customization.skinColor, //Skin color
																						customization.race, //Race
																						customization.gender //Gender
																						).C_String());



			for (int i=0; i<CHARACTERSLOTS; i++) {
				if (c.characterSlots[i].inUse==false) {
				c.characterSlots[i].cData = customization;
				c.characterSlots[i].inUse = true;
				break;
				}
			}
		c.sendCharacterList();
	}

};