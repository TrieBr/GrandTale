#include "GTGameClient.h"
#include "packetOpCodes.h"
#include "gameMap.h"
#include <iostream>
#include "GTGameServer.h"
#include <formulas.h>
GTGameClient::GTGameClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface) : abstractClient(guid,parentServer,clientInterface) {
	currentMap = NULL;
	this->equipmentContainer.registerCallback(this);
}

void GTGameClient::SlotChanged(ItemContainer* containerSrc, int slotNum) { //A slot has changed on a container
	if (containerSrc==&this->equipmentContainer) {
		this->cData.setEquipment((equipType)slotNum,containerSrc->getItem(slotNum).itemID);


		queries::downloadItemCustomizationData(gameDB,containerSrc->getItem(slotNum).customizationID,&equipmentCustomizationData[(equipType)slotNum]);

		if ((equipType)slotNum==EQUIP_OFFHAND) { //Something changed in the offhand slot
			if (this->ParentGameServer().iManager.GetItem(containerSrc->getItem(slotNum).itemID).weaponType==WEAPON_SHIELD || this->ParentGameServer().iManager.GetItem(containerSrc->getItem(slotNum).itemID).weaponType==WEAPON_FIST)  { //If a shield is being equipped
				this->cData.setDrawOffHandInFront(true); //Shield needs to be drawn infront of the hand
			}else{
				this->cData.setDrawOffHandInFront(false); //Anything else is drawn begind the hand
			}
		}
		if ((equipType)slotNum==EQUIP_MAINHAND) { //Something changed in the mainhand slot
			if (this->ParentGameServer().iManager.GetItem(containerSrc->getItem(slotNum).itemID).weaponType==WEAPON_FIST)  { //If a fist shield is being equipped
				this->cData.setDrawMainHandInFront(false); //fist needs to be drawn behind of the hand
			}else{
				this->cData.setDrawMainHandInFront(true); //Anything else is drawn in front the hand
			}
		}
		broadcastCharacterCustomization();
		recalculateStats(true);
		
	}
}

void GTGameClient::recalculateStats(bool broadcast) {
	


	unsigned short totalWeaponDamage = 0;
	if (this->equipmentContainer.getItem(EQUIP_MAINHAND).itemID!=-1) totalWeaponDamage += equipmentCustomizationData[EQUIP_MAINHAND].getWeaponDamage();
	this->setBaseStat(STAT_ATK,formulas::calculateMeleeAttack(getTotalStat(STAT_STR),getTotalStat(STAT_DEX),totalWeaponDamage,0,1));
	this->setBaseStat(STAT_MAGIC_ATK,formulas::calculateMagicAttack(getTotalStat(STAT_INT)));
	this->setBaseStat(STAT_DEF,formulas::calculateDefencePercent(4)); //4 is the armor all your equipment gives
	this->setBaseStat(STAT_MAGIC_DEF,formulas::calculateMagicDefencePercent(4)); //4 is the armor all your equipment gives
	this->setBaseStat(STAT_HP,formulas::calculateMaxHealth(getTotalStat(STAT_VIT),this->getLevel()));
	if (broadcast) {
	RakNet::BitStream dataN;
			dataN.Write<RakNet::MessageID>(gamePackets::STAT_COMMAND);
			dataN.Write<RakNet::MessageID>(gamePackets::STAT_UPDATE);
			writeData(dataN);
			sendPacket(dataN);
	}
}

void GTGameClient::hitCombatEntity(combatEntity* entity,hitData &data) {
	entity->getCurrentHealth();
	
	RakNet::BitStream dataPacket; //The bitstream
	dataPacket.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY); //Message ID
	dataPacket.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY_HIT); //Message ID
	dataPacket.Write<int>(entity->getUID()); //Send the combat entities unique ID
	dataPacket.Write<hitData>(data);

	this->getCurrentMap()->broadcastPacket(dataPacket);
	
}

void GTGameClient::mapGoto(gameMap *map) { //Transfer the player to a new map
	if (currentMap!=NULL) {
		currentMap->removeCharacter(this);
	}
	currentMap = map;
	if (currentMap!=NULL) {
		map->addCharacter(this); //Add us to the new map
		this->setParentMap(map);
		RakNet::BitStream data; //The bitstream
		data.Write<RakNet::MessageID>(gamePackets::MAP_GOTO); //Message ID
		data.Write<unsigned short>(map->getMapDataID()); //Send the unique ID
		sendPacket(data);
		currentMap->sendMapObjects(this); //Send all the existing map data to this client
	}else{
		std::cout << "GTGameclient::mapGoto() called with NULL map." << std::endl;
	}
}

void GTGameClient::sendInitialData() { //Send player initial data when logging in..
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::INITIAL_INFOLOAD); //Message ID
	data.Write<int>(this->UID);
	this->cData.writeCharacterData(data); //Write the character Data
	this->writeCombatData(data);
	this->Inventory_Usable.writeContainer(data);
	this->Inventory_Equip.writeContainer(data);
	this->Inventory_Regular.writeContainer(data);
	this->equipmentContainer.writeContainer(data);
	//this->skills.writeSkillContainer(data);
	this->miscData.writeData(data);
	sendPacket(data);

	for (int i=0; i<this->getAvailableSkillCount(); i++) {
		this->addClientSkill(this->getSkillHandlerAt(i));
	}
}

void GTGameClient::sendPlayerData(GTGameClient* dest) {
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::PLAYER_CHARACTER_DATA); //Message ID
	data.Write<unsigned short>(this->UID); //Send the players Unique ID
	cData.writeCharacterData(data); //Write the player's data
	dest->sendPacket(data);
}

void GTGameClient::sendNewCombatEntity(combatEntity* entity) {
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY); //Message ID
	data.Write<RakNet::MessageID>(gamePackets::COMBAT_ENTITY_CREATE); //Message ID
	data.Write<CombatEntityType>(entity->getType());
	data.Write<int>(entity->getUID()); //Send the combat entities unique ID
	entity->writeCombatData(data);
	this->sendPacket(data);
}

void GTGameClient::Logout() {
	getCurrentMap()->removeCharacter(this); //Remove ourselves from the map
	saveData();
}

void GTGameClient::saveData() {

}

void GTGameClient::updateContainer(ItemContainer* container, int slot) {
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::ITEM_CONTAINER_ACTION);
	data.Write<int>(gamePackets::ITEM_CONTAINER_UPDATE_SLOT);
	data.Write<int>(container->linkID);
	data.Write<int>(slot);
	data.Write<ItemContainerEntry>(container->getItem(slot));
	sendPacket(data);
}

bool GTGameClient::canEquipItem(ItemContainerEntry &item, int equipmentSlot) {
	if (this->ParentGameServer().iManager.GetItem(item.itemID).type==ITEM_TYPE::ITEM_EQUIP) { //Is the item equippable?
		if (this->ParentGameServer().iManager.GetItem(this->equipmentContainer.getItem(EQUIP_MAINHAND).itemID).equipType==EQUIP_TWOHAND && equipmentSlot==EQUIP_OFFHAND){ return false; } //Cant equip something in offhand, when a 2handed is in mainhand

		if (this->ParentGameServer().iManager.GetItem(item.itemID).equipType==equipmentSlot) return true; //Putting equip in its slot
		if (this->ParentGameServer().iManager.GetItem(item.itemID).equipType==EQUIP_RING && (equipmentSlot==EQUIP_RING || equipmentSlot==EQUIP_RING2)) return true; //Puting a ring in any ring slot
		if (this->ParentGameServer().iManager.GetItem(item.itemID).equipType==EQUIP_WEAPON && (equipmentSlot==EQUIP_OFFHAND || equipmentSlot==EQUIP_MAINHAND)) return true; //Putting "weapon" in mainhand or offhand
		if (this->ParentGameServer().iManager.GetItem(item.itemID).equipType==EQUIP_TWOHAND  && (equipmentSlot==EQUIP_MAINHAND)) return true;
		

	}
	return false;
}
	
void GTGameClient::broadcastCharacterCustomization() {
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::PLAYER_UPDATE_CUSTOMIZATION);
	data.Write<int>(this->UID);
	this->cData.writeCharacterCustomization(data);
	if (this->getCurrentMap()!=NULL) {
		this->getCurrentMap()->broadcastPacket(data);
	}

}

void GTGameClient::sendChatMessage(std::string author, std::string message, int color) { //Sends a chat message from the server
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::PLAYER_CHAT);
	data.Write<RakNet::RakString>(RakNet::RakString(message.c_str()));
	data.Write<RakNet::RakString>(RakNet::RakString(author.c_str()));
	data.Write<bool>(false); //No speech bubble
	this->sendPacket(data);

}

void GTGameClient::sendChatMessageWithSpeechBubble(std::string author, std::string message, GTGameClient* speechBubblePlayer, int color) { //Sends a chat message from the server
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::PLAYER_CHAT);
	data.Write<RakNet::RakString>(RakNet::RakString(message.c_str()));
	data.Write<RakNet::RakString>(RakNet::RakString(author.c_str()));
	data.Write<bool>(true); //speech bubble
	data.Write<int>(speechBubblePlayer->UID); //Player for speech bubble to appear on
	this->sendPacket(data);

}
	
void GTGameClient::updateClientSkill(abstractSkillHandler* skillHandler) { //Updates the client about a skill

}
void GTGameClient::addClientSkill(abstractSkillHandler* skillHandler) { //Adds a skill to the remote client (so they can use it
	RakNet::BitStream data; //The bitstream
	data.Write<RakNet::MessageID>(gamePackets::SKILLHANDLER_ACTION);
	data.Write<RakNet::MessageID>(gamePackets::SKILL_CLIENTADD);
	data.Write<int>(skillHandler->getSkillID());
	skillHandler->writeSkillHandlerData(data);
	this->sendPacket(data);
}
void GTGameClient::removeClientSkill(abstractSkillHandler* skillHandler) { //Removes a skill from the remote client


}