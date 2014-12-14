
#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"
#include "mobFactory.h"
#include "database.h"
#include "monster.h"
#include "mobAI_monster.h"
class playerChatMessage : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		RakNet::BitStream dataN;
		dataN.Write<RakNet::MessageID>(gamePackets::PLAYER_CHAT);
		

		RakNet::RakString chatMessage;
		data.Read<RakNet::RakString>(chatMessage);
		std::vector<std::string> commandArguments = parseCommands(chatMessage.C_String());

		if (getArgument(commandArguments,0)=="@item") {
				if (getArgument(commandArguments,1)=="help") {
					c.sendChatMessage("Server","Gives item to player.");
					c.sendChatMessage("Server","Syntax: @item <itemID> [\"Player\"]");
				}else {	
					if (getArgument(commandArguments,1)!="") {
					
						int itemID = atoi(getArgument(commandArguments,1).c_str());

							ItemContainerEntry entry;
							entry.customizationID = 0;
							entry.itemID = itemID;
							entry.isCustom = false;
							entry.iconID = c.ParentGameServer().iManager.GetItem(itemID).iconID;
							entry.stackCount = 1;
						switch (c.ParentGameServer().iManager.GetItem(itemID).type) {
						case ITEM_USABLE: {c.Inventory_Usable.setItem(0,entry); c.updateContainer(&c.Inventory_Usable,0); break;}
						case ITEM_EQUIP: {c.Inventory_Equip.setItem(0,entry); c.updateContainer(&c.Inventory_Equip,0); break; }
						case ITEM_REGULAR: {c.Inventory_Regular.setItem(0,entry);  c.updateContainer(&c.Inventory_Regular,0); break; }
						default: c.sendChatMessage("Server", "Can't find item container for item type.");
						}
	
					}
				}
			return;
		}
		if (getArgument(commandArguments,0)=="@spawnm") {
				if (getArgument(commandArguments,1)=="help") {
					c.sendChatMessage("Server","Spawns a monster above you");
					c.sendChatMessage("Server","Syntax: @spawnm <Monster ID> <amount>");
				}else {	
					if (getArgument(commandArguments,1)!="") {
						int amount = 1;
						if (getArgument(commandArguments,2)!="") amount = atoi(getArgument(commandArguments,2).c_str());
						for (int i=0; i<amount; i++) {
							int monsterID = atoi(getArgument(commandArguments,1).c_str());
							mob* newMonster = mobFactory::getMob(monsterID);
							mobAI_monster *ai = new mobAI_monster();
							newMonster->setAIController(ai);
							
							newMonster->setX(c.getX());
							newMonster->setY(c.getY());
							ai->setPlatform(c.getCurrentMap()->getLineUnderArea(newMonster->getX(),newMonster->getY(),1));
							c.getCurrentMap()->addCombatEntity((combatEntity*)newMonster);
							newMonster->setSpeed(1);
							newMonster->fall(); //Make the monster fall towards a platform
							c.getCurrentMap()->broadcastCombatEntityChanges(newMonster);
						}
					}
				}
			return;
		}
		if (getArgument(commandArguments,0)=="@spawnn") {
				if (getArgument(commandArguments,1)=="help") {
					c.sendChatMessage("Server","Spawns an npc above you");
					c.sendChatMessage("Server","Syntax: @spawnn <NPC ID> <amount>");
				}else {	
					if (getArgument(commandArguments,1)!="") {
						int amount = 1;
						if (getArgument(commandArguments,2)!="") amount = atoi(getArgument(commandArguments,2).c_str());
						for (int i=0; i<amount; i++) {
							int NPCID = atoi(getArgument(commandArguments,1).c_str());
							mobNPC* newNPC = mobNPCFactory::getMobNPC(NPCID);
							mobAI_monster *ai = new mobAI_monster();
							newNPC->setAIController(ai);
							
							newNPC->setX(c.getX());
							newNPC->setY(c.getY());
							ai->setPlatform(c.getCurrentMap()->getLineUnderArea(newNPC->getX(),newNPC->getY(),1));
							c.getCurrentMap()->addCombatEntity((combatEntity*)newNPC);
							newNPC->setSpeed(1);
							newNPC->fall(); //Make the monster fall towards a platform
							c.getCurrentMap()->broadcastCombatEntityChanges(newNPC);
						}
					}
				}
			return;
		}
		if (getArgument(commandArguments,0)=="@setcustomization") {
				if (getArgument(commandArguments,1)=="help") {
					c.sendChatMessage("Server","Sets a part of your customization");
					c.sendChatMessage("Server","Syntax: @setcustomization <type> <id>");
					c.sendChatMessage("Server","Type can be: hairType, hairColor, facialHairType, eyeType, mouthType");
					c.sendChatMessage("Server",", skinColor");
					
				}else {	
					if (getArgument(commandArguments,1)=="hairType")
						c.cData.setHairType(atoi(getArgument(commandArguments,2).c_str()));
					if (getArgument(commandArguments,1)=="hairColor")
						c.cData.setHairColor(atoi(getArgument(commandArguments,2).c_str()));
					if (getArgument(commandArguments,1)=="facialHairType")
						c.cData.setFacialHairType(atoi(getArgument(commandArguments,2).c_str()));
					if (getArgument(commandArguments,1)=="eyeType")
						c.cData.setEyeType(atoi(getArgument(commandArguments,2).c_str()));
					if (getArgument(commandArguments,1)=="mouthType")
						c.cData.setMouthType(atoi(getArgument(commandArguments,2).c_str()));
					if (getArgument(commandArguments,1)=="skinColor")
						c.cData.setSkinColor(atoi(getArgument(commandArguments,2).c_str()));
					c.broadcastCharacterCustomization();	
					queries::updatePlayerCustomization(gameDB,c.charDBID,c.cData);
				}
			return;
		}
		if (getArgument(commandArguments,0)=="@hitr") {
				if (getArgument(commandArguments,1)=="help") {
					c.sendChatMessage("Server","Hits all enemies in radius r for damage damage");
					c.sendChatMessage("Server","Syntax: @hitr <r> <damage>>");
				}else {	
					if (getArgument(commandArguments,1)!="") {
						int dmg = 0;
						if (getArgument(commandArguments,2)!="") dmg = atoi(getArgument(commandArguments,2).c_str());
						
							int radius = atoi(getArgument(commandArguments,1).c_str());
							
							std::vector<combatEntity*> v = c.getCurrentMap()->getCombatEntitiesInArea(c.getX(),c.getY(),radius);
							hitData hData;
							hData.damage = dmg;
							for (unsigned int i=0; i<v.size(); i++) {
								if (v[i]->getX()>c.getX()) hData.direction = HIT_DIRECTION_FROM_LEFT;
								else hData.direction = HIT_DIRECTION_FROM_RIGHT;
								c.hitCombatEntity(v[i],hData);
							}

						
					}
				}
			return;
		}

		dataN.Write<RakNet::RakString>((RakNet::RakString)c.cData.getCharacterName().c_str());
		c.getCurrentMap()->getMapChatChannel()->broadcastChatMessageWithSpeechBubble(c.cData.getCharacterName().c_str(),chatMessage.C_String(),&c);
	}

	std::string getArgument(std::vector<std::string> &commandArguments, int index) {
		if (commandArguments.size()>index) {
			return commandArguments[index];
		}
		return "";
	}

	std::vector<std::string> parseCommands(std::string stringToParse) {
		//Parses a string and explodes it into tokens, but ignores spaces in quotation markes. so @command "test one" 5 would end up as "@command", "test one", "5"
		std::vector<std::string> commandArguments;
		std::string stringSplit = stringToParse;
		while(!stringSplit.empty()) {
			size_t delimPosition = stringSplit.find_first_of(" ",0); //Find a space.
			std::string argument;
			if (delimPosition==stringSplit.npos) {
				argument = stringSplit.substr(0,stringSplit.length());
				stringSplit.erase(0,stringSplit.length());
			}else{
				size_t quotationOpen = stringSplit.find_first_of("\"",0); //Find a quotation
				bool quotationFound = false;
				if (quotationOpen!=stringSplit.npos) {
					if (quotationOpen<delimPosition) {
						size_t quotationClose = stringSplit.find_first_of("\"",quotationOpen+1); //Find a quotation
						if (quotationClose!=stringSplit.npos) {
							argument = stringSplit.substr(quotationOpen+1,quotationClose-(quotationOpen+1));
							if (stringSplit.find_first_of(" ",0)!=stringSplit.npos) {
								stringSplit.erase(quotationOpen,quotationClose+2);
							}else{
								stringSplit.erase(quotationOpen,quotationClose+1);	
							}
							quotationFound = true;
						}
					}

				}
				if (!quotationFound) {
					argument = stringSplit.substr(0,delimPosition);
					stringSplit.erase(0,delimPosition+1);
				}
			}
				commandArguments.push_back(argument);

		}
		return commandArguments;
	}

};