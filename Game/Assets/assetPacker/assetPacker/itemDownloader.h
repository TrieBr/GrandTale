 #include <mysql++.h>
#include <string>
#include <fstream>

/*
Downloads The items into a file to be packed into assets
File Format:
<int>numberOfItems
 {
	<int>ID
	<short>nameLength
	<char*>name
	<short>type
	<short>iconID
	<short>equipType
	<short>weaponType
	}
	*/


class itemDownloader { //Downloads the list of items from the MySQL database for compiling into the assets.
public:
	itemDownloader();
	bool connect(std::string host, std::string db, std::string username, std::string password);
	int downloadItems(std::string fileDestination);

private:
	bool query(std::string queryString);
	mysqlpp::StoreQueryResult &result() { return lastResult; }
	mysqlpp::Connection* connection;
	mysqlpp::StoreQueryResult lastResult;
	mysqlpp::Query* lquery;
};
