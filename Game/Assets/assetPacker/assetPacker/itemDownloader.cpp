

#include "itemDownloader.h"

	itemDownloader::itemDownloader() {

	}
	bool itemDownloader::connect(std::string host, std::string db, std::string username, std::string password) {
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

	int itemDownloader::downloadItems(std::string fileDestination) {
		std::fstream* fOut = new std::fstream();
		fOut->open(fileDestination,std::ios::out | std::ios::binary | std::ios::trunc);
		int intBuffer = 0;
			short shortBuffer = 0;
		if (fOut->is_open()) {
			
			if (query("SELECT id,name,type,iconID,equipType,weaponType,classRestriction FROM items")) {
				if (result().num_rows()>0) {
					//Write number of items
					intBuffer =  (int)result().num_rows();
					fOut->write((char*)&intBuffer,sizeof(int));

					for (int i=0; i<result().num_rows(); i++) {//For each item

						intBuffer = result()[i][0];
						fOut->write((char*)&intBuffer,sizeof(int)); //ID

						std::string itemName = std::string(((mysqlpp::String)result()[i][1]).c_str(),((mysqlpp::String)result()[i][1]).length()); 
						shortBuffer =  (int)itemName.length();
						fOut->write((char*)&shortBuffer,sizeof(short)); //Name Length

						fOut->write((char*)itemName.c_str(),itemName.length()); //Write the name string

						shortBuffer =  (int)result()[i][2]; 
						fOut->write((char*)&shortBuffer,sizeof(short)); //Type of item


						shortBuffer =   (int)result()[i][3]; 
						fOut->write((char*)&shortBuffer,sizeof(short)); //iconID


						shortBuffer =   (int)result()[i][4]; 
						fOut->write((char*)&shortBuffer,sizeof(short)); //equip Type

						shortBuffer =   (int)result()[i][5]; 
						fOut->write((char*)&shortBuffer,sizeof(short)); //weapon Type

						unsigned int u =   (unsigned int)result()[i][6]; 
						fOut->write((char*)&u,sizeof(int)); //weapon Type

					}
				}

			}

			fOut->close();
			delete fOut;
			return 1;
		}
		return 0;
	}

	bool itemDownloader::query(std::string queryString) {
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

	