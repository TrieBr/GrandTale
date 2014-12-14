#include "abstractClient.h"
#include "characterData.h"
#include <abstractItemContainerCallback.h>
#include <SkillContainer.h>
#include "skillUser.h"
#include <combatEntity.h>
#include <miscPlayerData.h>
#include <itemCustomizationData.h>
#ifndef _GTGAMECLIENT_
#define _GTGAMECLIENT_

class gameMap;
class GTGameServer;
class GTGameClient : public abstractClient, public abstractItemContainerCallback, public skillUser {
public:
	GTGameClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface);
	GTGameServer& ParentGameServer() { return (GTGameServer&)this->parentServer(); }
	int charDBID;
	int userDBID;
	int UID; //Unique ID, can be different every time the player connects
	character::characterData cData;
	miscPlayerData miscData; //Miscellaneous data
	ItemContainerLinker itemContainerLinks; //Linker for connecting the client item containers with the server.
	ItemContainer Inventory_Usable; //Make a container for each type of item
	ItemContainer Inventory_Equip; //Make a container for each type of item
	ItemContainer Inventory_Regular; //Make a container for each type of item
	ItemContainer equipmentContainer;
	virtual void SlotChanged(ItemContainer* containerSrc, int slotNum); //A slot has changed on a container
	virtual void recalculateStats(bool broadcast = false);

	virtual void hitCombatEntity(combatEntity* entity,hitData &data);

	gameMap* getCurrentMap() { return currentMap; }
	void mapGoto(gameMap *map); //Transfer the player to a new map
	void sendInitialData(); //Send player initial data when logging in..
	void sendPlayerData(GTGameClient* dest);
	void sendNewCombatEntity(combatEntity* entity);
	void Logout();
	void saveData();
	void updateContainer(ItemContainer* container, int slot);
	bool canEquipItem(ItemContainerEntry &item, int equipmentSlot);
	void broadcastCharacterCustomization();
	void sendChatMessage(std::string author, std::string message, int color = 0xFFFFFF); //Sends a chat message from the server
	void sendChatMessageWithSpeechBubble(std::string author, std::string message, GTGameClient* speechBubblePlayer, int color = 0xFFFFFF); //Sends a chat message from the server
	//Skill shit
	void updateClientSkill(abstractSkillHandler* skillHandler); //Updates the client about a skill
	void addClientSkill(abstractSkillHandler* skillHandler); //Adds a skill to the remote client (so they can use it)
	void removeClientSkill(abstractSkillHandler* skillHandler); //Removes a skill from the remote client
	SkillContainer<SkillContainerEntryExtended> skills;
private:
	gameMap* currentMap;
	itemCustomizationData equipmentCustomizationData[EQUIP_TYPE_COUNT]; //Cache for customization in equipment
	

};

#endif