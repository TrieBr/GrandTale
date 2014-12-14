#include "globalData.h"
#include <fstream>

itemManager* globalData::iManager;
skillManager* globalData::sManager;
	void globalData::initializeItemManager() {
		//See asset packer for data format.

		iManager = new itemManager();
		ALLEGRO_FILE* itemDatabaseFile = gameEngine::resources::data.openSubFile(":items:itemdb.bin",false);
		int intBuffer = 0;
		int shortBuffer = 0;
		al_fread(itemDatabaseFile ,&intBuffer,sizeof(int)); //Read number of items 
		int itemCount = intBuffer;
		iManager->allocateItems(itemCount+1);
		for (int i=0; i<itemCount; i++) { //For each item
			Item newItem;
			
			al_fread(itemDatabaseFile ,&intBuffer,sizeof(int)); //Read ID of item
			int itemID = intBuffer;

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read Name Length
			char* buffer = new char[shortBuffer];
			al_fread(itemDatabaseFile,buffer,shortBuffer); //Read the name string
			newItem.itemName = std::string(buffer,shortBuffer);

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read Item Type
			newItem.type = (ITEM_TYPE)shortBuffer;

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read The Icon ID
			newItem.iconID= shortBuffer;


			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read The equipment Type
			newItem.equipType = shortBuffer;

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read The equipment Type
			newItem.weaponType = shortBuffer;

			
			al_fread(itemDatabaseFile ,&intBuffer,sizeof(int)); //Read The equipment Type
			newItem.classRestrictions = (unsigned int)intBuffer;

	



			iManager->SetItem(itemID,newItem);
		}



	}
	void globalData::cleanupItemManager() {
		delete iManager;
	}
	itemManager* globalData::getItemManager() {
		return iManager;
	}

	void  globalData::initializeSkillManager() {
		//See asset packer for data format.
		sManager = new skillManager();
		ALLEGRO_FILE* itemDatabaseFile = gameEngine::resources::data.openSubFile(":skills:skilldb.bin",false);
		int intBuffer = 0;
		int shortBuffer = 0;
		al_fread(itemDatabaseFile ,&intBuffer,sizeof(int)); //Read number of items 
		int itemCount = intBuffer;
		sManager->allocateSkills(itemCount+1);
		for (int i=0; i<itemCount; i++) { //For each item
			skillData newSkill;
			
			al_fread(itemDatabaseFile ,&intBuffer,sizeof(int)); //Read ID of item
			int itemID = intBuffer;

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read Name Length
			char* buffer = new char[shortBuffer];
			al_fread(itemDatabaseFile,buffer,shortBuffer); //Read the name string
			newSkill.name = std::string(buffer,shortBuffer);

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read Item Type
			newSkill.type = (skillType)shortBuffer;

			al_fread(itemDatabaseFile ,&shortBuffer,sizeof(short)); //Read The Icon ID
			newSkill.iconID= shortBuffer;


			sManager->SetSkill(itemID,newSkill);
		}
	}
	void  globalData::cleanupSkillManager() {
		delete sManager;
	}
	skillManager*  globalData::getSkillManager() {
		return sManager;
	}


