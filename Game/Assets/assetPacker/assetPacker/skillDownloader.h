 #include <mysql++.h>
#include <string>
#include <fstream>

/*
Downloads The skills into a file to be packed into assets
File Format:
<int>numberOfSkills
 {
	<int>ID
	<short>nameLength
	<char*>name
	<short>type
	<short>iconID
	}
	*/


class skillDownloader { //Downloads the list of items from the MySQL database for compiling into the assets.
public:
	skillDownloader();
	bool connect(std::string host, std::string db, std::string username, std::string password);
	int downloadSkills(std::string fileDestination);

private:
	bool query(std::string queryString);
	mysqlpp::StoreQueryResult &result() { return lastResult; }
	mysqlpp::Connection* connection;
	mysqlpp::StoreQueryResult lastResult;
	mysqlpp::Query* lquery;
};
