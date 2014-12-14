#include "database.h"

database accountDB;
database gameDB;

database::database(std::string host, std::string db, std::string username, std::string password) {
	connect(host,db,username,password);
}

database::database() {

}
bool database::connect(std::string host, std::string db, std::string username, std::string password) {
	connection = new mysqlpp::Connection(false); //Create the connection object
	if (connection->connect(db.c_str(),host.c_str(),username.c_str(),password.c_str())) { //connect to the mysql server
		connection->set_option(new mysqlpp::ReconnectOption(true)); //Set to reconnect automatically
		std::cout << "[MYSQL] " << "Connected to MYSQL server." << std::endl;
		return true; //Sucessful connect
	}else{
		std::cout <<"[MYSQL] " << connection->error() << std::endl;
		return false; //Failed to connect
	}
}

bool database::query(std::string queryString) {
	mysqlpp::Query query = this->connection->query(queryString);
	lquery = &query;
	if ((lastResult = query.store())) { //Store the result
			return true;
		}else{
			std::cout << "[MYSQL Error] " << connection->error() << std::endl;
			return false;
		}
		return false;
	}

bool database::queryExecute(std::string queryString) { //Does not get results
	mysqlpp::Query query = this->connection->query(queryString);
	lquery = &query;
	if ((query.execute())) { //Store the result
		last_insert_id = (int)query.insert_id();
			return true;
		}else{
			std::cout << "[MYSQL Error] " << connection->error() << std::endl;
			return false;
		}
		return false;
}

void queries::downloadItems(database &db, itemManager *iManager) {
	db.pushResult();
	if (db.query(RakNet::RakString("SELECT id,name,type,iconID,equipType,weaponType, classRestriction FROM items").C_String())) {
		if (db.result().num_rows()>0) {
			iManager->allocateItems(db.result().num_rows()+1);
			std::cout << "Downloading " << db.result().num_rows() << " Items..." << std::endl;
			for (int i=0; i<db.result().num_rows(); i++) {
				Item newItem;
				
				newItem.type = (ITEM_TYPE)(int)db.result()[i][2];
				newItem.itemName = std::string(((mysqlpp::String)db.result()[i][1]).c_str(),((mysqlpp::String)db.result()[i][1]).length()); 
				newItem.iconID = db.result()[i][3];
				newItem.equipType  = db.result()[i][4];
				newItem.weaponType  = db.result()[i][5];
				newItem.classRestrictions  = db.result()[i][6];
				iManager->SetItem((int)db.result()[i][0],newItem);
			}
		}

	}
	db.popResult();
}

character::characterData queries::getCharacterData(database& db, int charID) {
	character::characterData newCharacter;
	db.pushResult();
	if (db.query(RakNet::RakString("SELECT * FROM characters WHERE id = %i",charID).C_String())) {
		if (db.result().num_rows()>0) {
            mysqlpp::String t = (db.result()[0][2]);
			newCharacter.setCharacterName(t.c_str());
            
				newCharacter.setMapID(db.result()[0][3]);


				newCharacter.setHairType( db.result()[0][6]);
				newCharacter.setHairColor(db.result()[0][7]);
				newCharacter.setFacialHairType(db.result()[0][8]);
				newCharacter.setEyeType(db.result()[0][9]);
				newCharacter.setMouthType(db.result()[0][10]);
				newCharacter.setSkinColor(db.result()[0][11]);
				newCharacter.setRace(db.result()[0][12]);
				newCharacter.setGender((character::genderType)(int)db.result()[0][13]);

				newCharacter.setFaction((character::faction)(int)db.result()[0][18]);
		}else{
		  std::cout << "DB Handler fetching invalid character ID." << charID << std::endl;
		}
		 
	}
	int equipmentInventory;
	getCharacterContainers(db,charID,NULL,NULL,NULL,&equipmentInventory);
	ItemContainer equipContainer;
	populateContainer(db, equipContainer, equipmentInventory);
	for (int i=0; i<equipContainer.getSize(); i++) {
		equipContainer.getItem(0);
		newCharacter.setEquipment((equipType)i,equipContainer.getItem(i).itemID);
	}

		db.popResult();
		return newCharacter;
}

void queries::getCharacterContainers(database& db, int charID, int *inventoryEquip, int *inventoryUse, int *inventoryRegular, int *equipment){
	db.pushResult();
	if (db.query(RakNet::RakString("SELECT container_InventoryEquip,container_InventoryUse,container_InventoryRegular,container_Equipment FROM characters WHERE id = %i",charID).C_String())) {
		if (db.result().num_rows()>0) {
			if (inventoryEquip!=NULL) *inventoryEquip = db.result()[0][0];
			if (inventoryUse!=NULL) *inventoryUse = db.result()[0][1];
			if (inventoryRegular!=NULL) *inventoryRegular = db.result()[0][2];
			if (equipment!=NULL) *equipment = db.result()[0][3];
		}
	}
	db.popResult();
}



void queries::populateContainer(database& db, ItemContainer &container, int containerID) {
	db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT slotCount, itemTypes FROM itemContainer WHERE id = %i",containerID).C_String())) {
		if (db.result().num_rows()>0) {
				container.setSize(db.result()[0][0]);
				container.itemTypes = db.result()[0][1];
		}else{
		  std::cout << "DB Handler error fetching item container " << containerID << std::endl;
		}
	}

	if (db.query(RakNet::RakString("SELECT isCustom,stackSize, itemID, slotID, customizationID, iconID FROM itemContainerEntry WHERE containerID = %i",containerID).C_String())) {
		if (db.result().num_rows()>0) {
			for (int i=0; i<db.result().num_rows(); i++) {
				ItemContainerEntry nE;
				nE.isCustom = db.result()[i][0];;
				nE.stackCount = db.result()[i][1];
				nE.itemID  = db.result()[i][2];
				nE.customizationID =  db.result()[i][4];
				nE.iconID = db.result()[i][5];
				container.setItem(db.result()[i][3],nE);
			}
		}else{
		  std::cout << "DB Handler error fetching item container " << containerID << std::endl;
		}
	}
db.popResult();
}

void queries::downloadCharacterSkills(database& db, int charID,  skillUser* pSkillUserHandle) {
db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT id, skillID, skillLevel,skillCooldown FROM characterSkills WHERE characterID = %i",charID).C_String())) {
		if (db.result().num_rows()>0) {
			for (int i=0; i<db.result().num_rows(); i++) {
				int skillID = db.result()[0][1];
				abstractSkillHandler* newSkill = skillHandlerFactory::generateSkillHandler(skillID); //Generate a handler for this skill ID
				if (newSkill!=NULL) {
					std::cout << "New skill added to player available list: UID: " << pSkillUserHandle->addAvailableSkill(newSkill) << std::endl;
					newSkill->setLevel(db.result()[0][2]);
					newSkill->setCooldown(db.result()[0][3]);
					newSkill->setSkillID(skillID);
				}
			}
		}
	}
db.popResult();
}

void queries::downloadMobs(database& db) {
	db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT id,name,level,maxHP,maxMP,element,size,combatStatsID FROM mobs").C_String())) {
		if (db.result().num_rows()>0) {
			for (int i=0; i<db.result().num_rows(); i++) {
				mob newMob;
				newMob.setType(COMBAT_MONSTER);
				newMob.setID(db.result()[i][0]);
				newMob.setName(std::string(db.result()[i][1]));
				newMob.setLevel(db.result()[i][2]);
				newMob.setBaseStat(STAT_HP,db.result()[i][3]);
				newMob.setBaseStat(STAT_MP,db.result()[i][4]);
				newMob.setElement(db.result()[i][5]);
				newMob.setSize(db.result()[i][6]);
				int combatStatsID = db.result()[i][7];
				downloadCombatEntityStats(db,combatStatsID,&newMob);
				mobFactory::addMob(newMob);
			}
		}
	}
db.popResult();
}

void queries::downloadNPCMobs(database& db) {
db.pushResult();
	if (db.query(RakNet::RakString("SELECT id, name, level, hairType, hairColor, facialHairType, eyeType, mouthType, skinColor, race, gender, maxHP, maxMP, faction, combatStatsID, container_Equipment FROM npc").C_String())) {
		if (db.result().num_rows()>0) {
			character::characterData newCharacter;
			for (int i=0; i<db.result().num_rows(); i++) {
				mobNPC newMob;
				newMob.setType(COMBAT_NPC);
				 mysqlpp::String t = (db.result()[0][1]);
				newMob.setName(t.c_str());
         
				newCharacter.setHairType( db.result()[0][3]);
				newCharacter.setHairColor(db.result()[0][4]);
				newCharacter.setFacialHairType(db.result()[0][5]);
				newCharacter.setEyeType(db.result()[0][6]);
				newCharacter.setMouthType(db.result()[0][7]);
				newCharacter.setSkinColor(db.result()[0][8]);
				newCharacter.setRace(db.result()[0][9]);
				newCharacter.setGender((character::genderType)(int)db.result()[0][10]);

				newCharacter.setFaction((character::faction)(int)db.result()[0][13]);

				newMob.setBaseStat(STAT_HP,db.result()[0][11]);
				newMob.setBaseStat(STAT_MP,db.result()[0][12]);

				int combatStatsID = db.result()[0][14];
				downloadCombatEntityStats(db,combatStatsID,&newMob);

				int equipmentContainer =db.result()[0][15];


				mobNPCFactory::addMobNPC(newMob);
			}
		}
	}
db.popResult();
}

void queries::downloadItemCustomizationData(database &db, int customizationDataID, itemCustomizationData* data) {
		db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT stat_base_str, stat_bonus_str, stat_base_dex, stat_bonus_dex, stat_base_agi, stat_bonus_agi, \
								    stat_base_vit, stat_bonus_vit, stat_base_luk, stat_bonus_luk, \
									stat_base_int, stat_bonus_int, stat_base_atk, stat_bonus_atk, \
									stat_base_magic_atk, stat_bonus_magic_atk, stat_base_defence, stat_bonus_defence, \
									stat_base_magic_def, stat_bonus_magic_def, \
									stat_base_hp, stat_bonus_hp, stat_base_mp, stat_bonus_mp, \
									equip_text, equip_scriptID, \
									active_text, active_scriptID, weapon_damage FROM itemcustomizationdata WHERE id = %i",customizationDataID).C_String())) {
		if (db.result().num_rows()>0) {
			for (unsigned char i=0; i<STAT_COUNT; i++) {
				data->setBaseStat((statTypes)(int)i,db.result()[0][2*i]);
				data->setBonusStat((statTypes)(int)i,db.result()[0][(2*i)+1]);
			}

			data->setEquipText(std::string(mysqlpp::String(db.result()[0][24]).c_str()));
			data->setActiveText(std::string(mysqlpp::String(db.result()[0][26]).c_str()));
			data->setWeaponDamage(db.result()[0][28]);








		}
	}
db.popResult();

}

void queries::downloadCombatEntityStats(database &db, int combatStatsID, combatEntityStats *stats) {

			db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT stat_base_str, stat_base_dex,  stat_base_agi,  \
								    stat_base_vit,  stat_base_luk, \
									stat_base_int, stat_base_atk,  \
									stat_base_magic_atk, stat_base_def,  \
									stat_base_magic_def, \
									stat_base_hp, stat_bonus_hp, stat_base_hp, stat_bonus_hp FROM combatstats WHERE id = %i",combatStatsID).C_String())) {
		if (db.result().num_rows()>0) {
			for (unsigned char i=0; i<STAT_COUNT; i++) {
				stats->setBaseStat((statTypes)(int)i,db.result()[0][i]);
				stats->setBonusStat((statTypes)(int)i,0);
			}

		}
	}
db.popResult();
}

void queries::downloadPlayerCombatData(database& db, combatEntity* entity, int charID) {
		db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT x,y,currentHP,maxHP,currentMP,maxMP,faction,combatStatsID, level FROM characters WHERE id = %i",charID).C_String())) {
		if (db.result().num_rows()>0) {
			for (int i=0; i<db.result().num_rows(); i++) {
				entity->setX(db.result()[0][0]);
				entity->setY(db.result()[0][1]);
				entity->setBaseStat(STAT_HP,db.result()[0][3]);
				entity->setCurrentHealth(db.result()[0][2]);
				entity->setBaseStat(STAT_MP,db.result()[0][5]);
				entity->setCurrentMana(db.result()[0][4]);
				entity->setLevel(db.result()[0][8]);
				int combatStatsID = db.result()[0][7];
				downloadCombatEntityStats(db,combatStatsID,entity);
			}
		}
	}
db.popResult();

}

void queries::downloadPlayerMiscData(database& db, int charID,  miscPlayerData* miscDataPointer) {
			db.pushResult();
	
	if (db.query(RakNet::RakString("SELECT statPoints FROM characters WHERE id = %i",charID).C_String())) {
		if (db.result().num_rows()>0) {
			miscDataPointer->setRemainingStatPoints(db.result()[0][0]);
		}
	}
db.popResult();
}

 void queries::updatePlayerCustomization(database &db, int charID, character::characterCustomization &c) {
			db.pushResult();
	
	if (db.queryExecute(RakNet::RakString("UPDATE characters SET hairType=%i, hairColor=%i, facialHairType=%i, eyeType=%i, mouthType=%i, skinColor=%i WHERE id = %i",
		c.getHairType(),
		c.getHairColor(),
		c.getFacialHairType(),
		c.getEyeType(),
		c.getMouthType(),
		c.getSkinColor(),
		charID
		).C_String())) {
			//Succeeded
	}
db.popResult();

}