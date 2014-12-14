
#include "characterData.h"
#include <SkillContainer.h>
#include <mysql++.h>
#include <stack>
#include "itemManager.h"
#include "skillUser.h"
#include "skillHandlerFactory.h"
#include "mobFactory.h"
#include "mobNPCFactory.h"
#include <itemCustomizationData.h>
#include <miscPlayerData.h>
#ifndef _DATABASE_
#define _DATABASE_

class database {
public:
	database(std::string host, std::string db, std::string username, std::string password);
	database();
	bool connect(std::string host, std::string db, std::string username, std::string password);
	bool query(std::string queryString);
	bool queryExecute(std::string queryString); //Does not get results
	mysqlpp::StoreQueryResult &result() { return lastResult; }

	void pushResult() {
		resultStack.push(result());
	}
	void popResult() {
		lastResult = resultStack.top();
		resultStack.pop();
	}
	int last_id() {
		return last_insert_id;
	}
	
private:
	mysqlpp::Connection* connection;
	mysqlpp::StoreQueryResult lastResult;
	std::stack<mysqlpp::StoreQueryResult> resultStack;
	mysqlpp::Query* lquery;
	int last_insert_id;
	
};

extern database accountDB;
extern database gameDB;

class queries {
public:
	static void downloadItems(database &db, itemManager *iManager);
	static character::characterData getCharacterData(database& db, int charID);
	static void getCharacterContainers(database& db, int charID, int *inventoryEquip, int *inventoryUse, int *inventoryRegular, int *equipment);
	static void populateContainer(database& db, ItemContainer &container, int containerID);
	static void downloadCharacterSkills(database& db, int charID,  skillUser* pSkillUserHandle);
	static void downloadMobs(database& db);
	static void downloadNPCMobs(database& db);
	static void downloadItemCustomizationData(database &db, int customizationDataID, itemCustomizationData* data);
	static void downloadCombatEntityStats(database &db, int combatStatsID, combatEntityStats *stats);

	static void downloadPlayerCombatData(database& db, combatEntity* entity, int charID);
	static void downloadPlayerMiscData(database& db, int charID,  miscPlayerData* miscDataPointer);
	static void updatePlayerCustomization(database &db, int charID, character::characterCustomization &c);
		
};

#endif