#include "packetProcessor.h"
#include "GTLoginClient.h"

class characterCreate : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
	RakNet::RakString		characterName;
	character::characterData customization;
	data.Read<RakNet::RakString>(characterName);
	customization.setCharacterName(characterName.C_String());
	customization.readCharacterCustomization(data);


	//Create the Use Item Container
	gameDB.queryExecute(RakNet::RakString("INSERT INTO itemcontainer(slotCount, itemTypes)\
								   VALUES  (15,%i)",ITEM_USABLE).C_String());
	int containerID_Use = gameDB.last_id(); 
	//Create Equip item container
	gameDB.queryExecute(RakNet::RakString("INSERT INTO itemcontainer (slotCount, itemTypes) VALUES (15,%i)",ITEM_EQUIP).C_String());
	int containerID_Inv_Equip = gameDB.last_id(); 
	//Create Regular item container
	gameDB.queryExecute(RakNet::RakString("INSERT INTO itemcontainer (slotCount, itemTypes) VALUES (15,%i)",ITEM_REGULAR).C_String());
	int containerID_Regular = gameDB.last_id(); 

	//Create Regular item container
	gameDB.queryExecute(RakNet::RakString("INSERT INTO itemcontainer (slotCount, itemTypes) VALUES (%i,%i)",EQUIP_TYPE_COUNT,ITEM_EQUIP).C_String());
	int containerID_Equip = gameDB.last_id(); 


	gameDB.queryExecute(RakNet::RakString("INSERT INTO characters (userid, charname, mapid, x, y, hairtype, haircolor, facialHairType, eyeType, mouthType, skincolor, race, gender, container_InventoryEquip, container_InventoryUse, container_InventoryRegular, container_Equipment)\
																						VALUES   (%i, '%s', %i,%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i )",
																						c.dbID, //User ID
																						customization.getCharacterName().c_str(), //Charname
																						0, //mapid
																						0, //x
																						0, //y
																						customization.getHairType(), //Hair type
																						customization.getHairColor(), //Hair color
																						customization.getFacialHairType(), //Facial hair type
																						customization.getEyeType(), //Eye type
																						customization.getMouthType(), //Mouth type
																						customization.getSkinColor(), //Skin color
																						customization.getRace(), //Race
																						customization.getGender(), //Gender
																						containerID_Inv_Equip, //inventoryEquip
																						containerID_Use, //containter_InventoryUse
																						containerID_Regular, //container_InventoryRegular
																						containerID_Equip //container_Equipment
																						).C_String());
	


			for (int i=0; i<CHARACTERSLOTS; i++) {
				if (c.characterSlots[i].inUse==false) {
					c.characterSlots[i].dbID = gameDB.last_id();
				c.characterSlots[i].cData = customization;
				c.characterSlots[i].inUse = true;
				break;
				}
			}
		c.sendCharacterList();
	}

};