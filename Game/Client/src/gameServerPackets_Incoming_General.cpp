
#include "gameServer.h"
#include "gameEngine.h"
#include "worldGameMap.h"
#include "myData.h"
#include <iostream>
#include "skillHandlerFactory.h"
#include "mob.h"
#include "monster.h"
#include "npc.h"

namespace networking {


	void gameServer::receiveInitialInfo(RakNet::Packet *packet) { //Receive the player's initial info
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		data.Read<int>(myData::myUID);
		myData::cData.readCharacterData(data);
		myData::myCombatEntity.readCombatData(data);
		myData::Inventory_Usable.readContainer(data);
		myData::Inventory_Equip.readContainer(data);
		myData::Inventory_Regular.readContainer(data);
		myData::equipmentContainer.readContainer(data);

		myData::containerLinks.LinkContainer(&myData::Inventory_Usable,myData::Inventory_Usable.linkID);
		myData::containerLinks.LinkContainer(&myData::Inventory_Equip,myData::Inventory_Equip.linkID);
		myData::containerLinks.LinkContainer(&myData::Inventory_Regular,myData::Inventory_Regular.linkID);
		myData::containerLinks.LinkContainer(&myData::equipmentContainer,myData::equipmentContainer.linkID);
		
		myData::miscData.readData(data);
		std::cout << "Receiving player info..." << std::endl;
	}


	void gameServer::mapGoto(RakNet::Packet *packet) { //Server is telling us to switch maps
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		unsigned short mapID;
		data.Read<unsigned short>(mapID); //Read the map ID

		gameServer::currentGameMap  = new worlds::worldGameMap();
		gameEngine::core::setCurrentWorld(gameServer::currentGameMap);
		gameServer::parentWorld = gameServer::currentGameMap;

		std::cout << "Server requested map change to: " << mapID << std::endl;
	}

	void gameServer::mapAddPlayer(RakNet::Packet *packet) { //Adding another player to the map
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		if (gameServer::currentGameMap!=NULL) { //If there is a game world active
			character::characterData* dummyData = new character::characterData();
			short UID;
			data.Read<short>(UID); //Read the player's UID
			dummyData->readCharacterData(data); //Read the player's data
			entities::gameMap::entityPlayerDummy* newDummy = new entities::gameMap::entityPlayerDummy(dummyData,UID);
			gameServer::currentGameMap->addDummyPlayer(newDummy);
		}else{
			assert(gameServer::currentGameMap!=NULL);
		}
	}

	void gameServer::playerPositionUpdate(RakNet::Packet *packet) { //A remote player has executed a movement action
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		positionUpdate positionInfo;
		short UID;
		data.Read<positionUpdate>(positionInfo);
		data.Read<short>(UID);
		gameServer::currentGameMap->findDummyPlayer(UID)->updatePosition(positionInfo);

	}

	void gameServer::playerChatMessage(RakNet::Packet *packet){ //A remote player sent a chat message
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		RakNet::RakString Msg, Name;
		bool speechBubble;
		data.Read<RakNet::RakString>(Msg);
		data.Read<RakNet::RakString>(Name);
		data.Read<bool>(speechBubble);
		if (speechBubble) {
			int playerSpeechBubble;
			data.Read<int>(playerSpeechBubble);
			if (playerSpeechBubble!=myData::myUID) {
				gameServer::currentGameMap->findDummyPlayer(playerSpeechBubble)->getSpeechBubbleHandler()->displayText(Msg.C_String());
			}else{
				myData::myPlayer->getSpeechBubbleHandler()->displayText(Msg.C_String());
			}
		}
		gameServer::currentGameMap->getGUI_Chat()->AddMessage(Name.C_String(),Msg.C_String(),0,0,0);
	}

	void gameServer::itemContainer_Operation(RakNet::Packet *packet){ //Server is sending an item container operation
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		int operation;
		data.Read<int>(operation);
		if (operation==gamePackets::ITEM_CONTAINER_UPDATE_SLOT) {
			int containerID;
			data.Read<int>(containerID);
			ItemContainer* container;
			container = myData::containerLinks.FetchLinkedContainer(containerID);
			if (container!=NULL) {
				int slotID;
				data.Read<int>(slotID);
				ItemContainerEntry buffer;
				data.Read<ItemContainerEntry>(buffer);
				container->setItem(slotID,buffer);
			}
		}
	}

	void gameServer::updateCharacterCustomization(RakNet::Packet *packet) { //Player is updating their character Customization
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		int UID;
		data.Read<int>(UID);
		if (UID==myData::myUID) {
			myData::cData.readCharacterCustomization(data);
			myData::cData.disbatchCustomizationChange();		
		}else{
			gameServer::currentGameMap->findDummyPlayer(UID)->cData->readCharacterCustomization(data);
			gameServer::currentGameMap->findDummyPlayer(UID)->cData->disbatchCustomizationChange();	
		}
	}

	void gameServer::skillHandlerAction(RakNet::Packet *packet) {
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		RakNet::MessageID subAction;
		data.Read<RakNet::MessageID>(subAction);
		switch (subAction) {
		case gamePackets::SKILL_CLIENTADD: {
			int skillID;
			data.Read<int>(skillID);
			abstractSkillHandler* handlerTemp = skillHandlerFactory::generateHandler(skillID);
			handlerTemp->readSkillHandlerData(data);
			myData::skills.addSkillHandler(handlerTemp);
			break;
										   }
		case gamePackets::SKILL_EXECUTED: {
			short UID;
			int skillID;
			data.Read<short>(UID); //UID of the character
			data.Read<int>(skillID); //ID of the skill
			abstractSkillHandler* handler = skillHandlerFactory::generateHandler(skillID);
			gameServer::currentGameMap->findDummyPlayer(UID)->addSkillHandler(handler);
			handler->ExecuteSkill();
			break;
										   }
		}
	}

	void gameServer::combatEntity(RakNet::Packet *packet) { 
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		RakNet::MessageID subAction;
		data.Read<RakNet::MessageID>(subAction);
		if (subAction==gamePackets::COMBAT_ENTITY_CREATE) { //Creating a new combat entity on the map
			CombatEntityType entityType;
			data.Read<CombatEntityType>(entityType);

			if (entityType==COMBAT_MONSTER) {
				monster* newMon = new monster();
				int uid = 0;
				data.Read<int>(uid);
				newMon->setUID(uid);
				newMon->readCombatData(data);
				newMon->loadRenderer();
				newMon->setPlatform(gameServer::currentGameMap->getLineUnderArea(newMon->getX(), newMon->getY(),1));
				gameServer::currentGameMap->addMob(newMon);
			}
			if (entityType==COMBAT_NPC) {
				npc* newMon = new npc();
				int uid = 0;
				data.Read<int>(uid);
				newMon->setUID(uid);
				newMon->readCombatData(data);
				newMon->loadRenderer();
				newMon->setPlatform(gameServer::currentGameMap->getLineUnderArea(newMon->getX(), newMon->getY(),1));
				gameServer::currentGameMap->addMob(newMon);
			}
			
		}
		if (subAction==gamePackets::COMBAT_ENTITY_UPDATE) { //updating a new entity in the map
			int uid;
			data.Read<int>(uid);
			mobDummy* dummy = gameServer::currentGameMap->findMobDummy(uid);
			if (dummy!=NULL) {
				dummy->readCombatData(data);
				dummy->stateChanged();
				return;
			}
		}

		if (subAction==gamePackets::COMBAT_ENTITY_HIT) { //Entity was hit with damage
			int uid;
			data.Read<int>(uid);
			hitData hData;
			data.Read<hitData>(hData);
			mobDummy* dummy = gameServer::currentGameMap->findMobDummy(uid);
			if (dummy!=NULL) {
				dummy->hit(hData);
				dummy->stateChanged();
				return;
			}
		}
	}

	void gameServer::item_fetchCustomizationData_received(RakNet::Packet *packet) { //Item custom data fetch was received
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		int fetchID;
		data.Read<int>(fetchID);
		 itemCustomizationFetchHandle* handle = itemCusomizationDataFetch::getFetchHandleFromFetchID(fetchID);
		 if (handle) {
			 handle->getCustomizationData().readData(data);
			 handle->setStatus(IC_FETCH_DONE);
			 itemCusomizationDataFetch::removeFromFetching(fetchID);
		 }
	}

	void gameServer::statCommandReceived(RakNet::Packet *packet) { //Command for stats
		RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
		RakNet::MessageID subID;
		data.Read<RakNet::MessageID>(subID);
		if (subID==gamePackets::STAT_UPDATE) {
			myData::myCombatEntity.readData(data);
		}
	}
		void gameServer::miscDataUpdateReceived(RakNet::Packet *packet) { //Command for misc Data
			RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
			myData::miscData.readData(data);
		}

}


