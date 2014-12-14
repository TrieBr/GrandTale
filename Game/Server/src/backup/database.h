
#include "characterData.h"
#include <mysql++.h>
#include <stack>


#ifndef _DATABASE_
#define _DATABASE_

class database {
public:
	database(std::string host, std::string db, std::string username, std::string password);
	database();
	bool connect(std::string host, std::string db, std::string username, std::string password);
	bool query(std::string queryString);
	mysqlpp::StoreQueryResult &result() { return lastResult; }

	void pushResult() {
		resultStack.push(result());
	}
	void popResult() {
		lastResult = resultStack.top();
		resultStack.pop();
	}
	int last_id() {
		return lquery->insert_id();
	}
	
private:
	mysqlpp::Connection* connection;
	mysqlpp::StoreQueryResult lastResult;
	std::stack<mysqlpp::StoreQueryResult> resultStack;
	mysqlpp::Query* lquery;
	
};

extern database accountDB;
extern database gameDB;

class queries {
public:
	static character::characterData getCharacterData(database& db, int charID);
};

#endif