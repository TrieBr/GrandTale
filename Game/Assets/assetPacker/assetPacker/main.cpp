// ----------------------------------------------------------------------
// main.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	Compiles resources from the RAW_ASSETS directory. Each folder in that directory is a seperate .gtd file. Any folders/files in that will be compiled into the .gdf.
	Example
	rawAssets				Root folder
		Graphics			Sub folder of root (will be Graphics.gtd)
			Gfol			Sub folder of "Graphics" will be a "Section" in Graphics.gtd
				file.png	File in the "GFol" section of "Graphics.gtd"
		Fonts				Sub folder of root (will be "Fonts.gtd")

		Note that file names in the resource pack are like
		:Folder:Filename.ext
		for example :Gfol:file.png
*/
// ------------------------------------------------------------------------


#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "crc.h"
#include <sstream>
#include "hashTable.h"
#include <fstream>
#include "itemDownloader.h"
#include "skillDownloader.h"

#define HEADERSIZE 4
using namespace std;

#define RAW_ASSETS "rawAssets"
#define COMPILED_ASSETS "compiledAssets"
#define MYSQL_ITEMS_OUTPUT "rawAssets/Data/items/itemdb.bin"
#define MYSQL_SKILLS_OUTPUT "rawAssets/Data/skills/skilldb.bin"
#define MYSQL_SERVER "gtserver.zapto.org"
#define MYSQL_USER "root"
#define MYSQL_PASS "root"

unsigned int hashFunction(const char *key, unsigned int len) { //Primary hash function for getting an index from a resource name
		unsigned int hash, i;
		for(hash = i = 0; i < len; ++i)
		{
			hash += key[i];
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}

struct Asset
{ //An asset file that needs to be compiled
	string filePath;
	string assetName;
	bool writtenToFile;
};


struct assetFile
{//A resource file that contains compiled assets
	string fileName; //The name of the compiled asset file (eg. Graphics.gtd)
	std::vector<Asset*> assetList;
};


std::vector<assetFile*> assetFiles; //List of resource files that need to be compiled





void searchFolder(string folderPath, string parentFolder, assetFile* aFile)
{
	HANDLE			 folderSearch;
	WIN32_FIND_DATA	 fData;
	folderSearch = FindFirstFile(string(folderPath).append("\\*").c_str(), &fData);


	if (folderSearch!=INVALID_HANDLE_VALUE) {
		while (FindNextFile(folderSearch,&fData)) { //For each sub folder/file
			if ((fData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==FILE_ATTRIBUTE_DIRECTORY) { //If it is a directory
					if (string(fData.cFileName)!=".." && string(fData.cFileName)!=".") { //If its not the parent/current folder
						searchFolder(string(folderPath).append("\\").append(fData.cFileName),string(parentFolder).append(":").append(fData.cFileName),aFile); //Add the child folder
					}
			}else{ //Its a normal file
				Asset * newAsset = new Asset(); //Create a new asset
				newAsset->filePath=string(folderPath).append("\\").append(fData.cFileName); 
				newAsset->assetName = string(parentFolder).append(":").append(fData.cFileName);
				newAsset->writtenToFile = false; //Not written yet
				aFile->assetList.push_back(newAsset);

			}
		}
	}

}


void fileCopy(fstream &read, fstream &write){ //Copys contents of "read" into "write"
			int				fileSize = 0;
			int				position = 0;
			int				chunkSize = 1024;
			char*			chunkBuffer = new char[chunkSize];
			//Write the asset data
			read.seekg(0,ios::end);
			fileSize = (int)read.tellg();
			read.seekg(0, ios::beg);
			write.write(reinterpret_cast<char*>(&fileSize),sizeof(int));
			while (position<fileSize)
			{
				int readSize = chunkSize;
				if (position+chunkSize>fileSize) {
					readSize = fileSize-position;
				}
				//Copy the data over
				read.read(chunkBuffer,readSize);
				write.write(chunkBuffer,readSize);
				position+=readSize;
			}
			delete [] chunkBuffer;
}


int main()
{
	itemDownloader dload;
	if (dload.connect(MYSQL_SERVER,"triebrco_GTdata",MYSQL_USER,MYSQL_PASS)) {
		dload.downloadItems(MYSQL_ITEMS_OUTPUT);
	}else{
		std::cout << "Unable to connect to MSQL, not downloading item list." << std::endl;
	}

	skillDownloader sdload;
	if (sdload.connect(MYSQL_SERVER,"triebrco_GTdata",MYSQL_USER,MYSQL_PASS)) {
		sdload.downloadSkills(MYSQL_SKILLS_OUTPUT);
	}else{
		std::cout << "Unable to connect to MSQL, not downloading skill list." << std::endl;
	}

	WIN32_FIND_DATA fileData;
	HANDLE			rootSearch;
	rootSearch = FindFirstFile(string(RAW_ASSETS).append("\\*").c_str(), &fileData);
	if (rootSearch!=INVALID_HANDLE_VALUE) {
		while (FindNextFile(rootSearch,&fileData)) { //For each sub folder/file
				if ((fileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==FILE_ATTRIBUTE_DIRECTORY) { //If it is a directory
					if (string(fileData.cFileName)!=".." && string(fileData.cFileName)!=".") {  //If its not the parent/current folder
						assetFile* newAFile = new assetFile();
						newAFile->fileName = string(COMPILED_ASSETS).append("\\").append(fileData.cFileName).append(".gtd");
						searchFolder(string(RAW_ASSETS).append("\\").append(fileData.cFileName),"",newAFile);
						assetFiles.push_back(newAFile);
					}
				}
		}
	}


	for (unsigned int i=0; i<assetFiles.size(); i++) { //For each resource file
		unsigned int				hashTableSize = assetFiles[i]->assetList.size(); //Size of the hash table
		std::vector<unsigned int>	hashTable; //The hash table itself
		unsigned int				headerSize = hashTableSize*sizeof(int); //Size in bytes of the hash table

		hashTable.resize(hashTableSize); //Resize the hash table
		for(unsigned int j=0; j<hashTableSize; j++) { //Set all the entries to NULL/0x00
			hashTable[j] = 0;
		}

		std::fstream dataFile(assetFiles[i]->fileName,std::ios::trunc | std::ios::binary | std::ios::out | std::ios::in); //The resource archive that will contain the assets
		 
		unsigned int numberOfFiles = assetFiles[i]->assetList.size(); //The number of assets
		dataFile.write(reinterpret_cast<char*>(&numberOfFiles),sizeof(int)); //Write the number of assets
	
		unsigned int hashTableOffset; //Offset in the file where the hash table is located
		hashTableOffset =  (unsigned int)dataFile.tellp();
		
		for (unsigned int j=0; j<hashTableSize; j++) {//Reserve space for the hash table in the file
			unsigned int w = 0x00;
			dataFile.write(reinterpret_cast<char*>(&w),sizeof(int));
		}

		for (unsigned int j=0; j<assetFiles[i]->assetList.size(); j++) { //For each asset in this resource pack
			
			std::fstream	assetData(assetFiles[i]->assetList[j]->filePath,std::ios::binary | std::ios::in); //Read the asset file
			unsigned int	assetHash; 
			assetHash =  hashFunction(assetFiles[i]->assetList[j]->assetName.c_str(),assetFiles[i]->assetList[j]->assetName.length()) % hashTableSize; //The hash/index of this asset in the hash table

			if (hashTable[assetHash]==0x00){ //If the entry in the hash table isn't in use..
				hashTable[assetHash] = (unsigned int)dataFile.tellp(); //Set the entry to the offset of this asset

				unsigned int nameCRC32 = crc(reinterpret_cast<unsigned char*>(const_cast<char*>(assetFiles[i]->assetList[j]->assetName.c_str())),assetFiles[i]->assetList[j]->assetName.length()); //Get the crc32 of the asset name
				dataFile.write(reinterpret_cast<char*>(&nameCRC32),sizeof(unsigned int)); //Write the crc32 of the name
				fileCopy(assetData,dataFile); //Copy the asset into the resource folder
				assetFiles[i]->assetList[j]->writtenToFile = true; //It has now been written to file
				assetData.close(); //Close the asset file
			
				//We want all other assets that collide with this to appear right after this...
				for (unsigned int jj=0; jj<assetFiles[i]->assetList.size(); jj++) { //For each asset
					if (hashFunction(assetFiles[i]->assetList[jj]->assetName.c_str(),assetFiles[i]->assetList[jj]->assetName.length()) % hashTableSize==assetHash) { //If the hash is the same as the current asset
						if (assetFiles[i]->assetList[jj]->writtenToFile==false) { //If the asset hasnt been written yet
							std::fstream	assetData(assetFiles[i]->assetList[jj]->filePath,std::ios::binary | std::ios::in); //Open the asser
							unsigned int nameCRC32 = crc(reinterpret_cast<unsigned char*>(const_cast<char*>(assetFiles[i]->assetList[jj]->assetName.c_str())),assetFiles[i]->assetList[jj]->assetName.length()); //crc32 hash the asset name
							dataFile.write(reinterpret_cast<char*>(&nameCRC32),sizeof(unsigned int)); //Write the crc32
							fileCopy(assetData,dataFile); //Copy the asset data into the asset pckage
							assetFiles[i]->assetList[jj]->writtenToFile = true; //It has now been written
							assetData.close(); //Close the asset
						}
					}
				}
			}else{
				if (!assetFiles[i]->assetList[j]->writtenToFile) { //If the asset hasn't beem written
					cout << "Hash bucket is already in use for: " << assetFiles[i]->assetList[j]->assetName << endl; //Show an error
				}
			}

		}

		dataFile.seekp(hashTableOffset); //Seek to the hash table
		for (unsigned int j=0; j<hashTableSize; j++) { //Rewrite the hash table using the actual hash data.
			dataFile.write(reinterpret_cast<char*>(&hashTable[j]),sizeof(int));
		}

		dataFile.close(); //Close the asset package
	}


	DWORD first = GetTickCount();
	for (unsigned int i=0; i<assetFiles.size(); i++) {
		std::fstream sFile(assetFiles[i]->fileName,std::ios::binary | std::ios::out | std::ios::in);
		for (unsigned int j=0; j<assetFiles[i]->assetList.size(); j++) { //For each asset
			unsigned int assetHash =  hashFunction(assetFiles[i]->assetList[j]->assetName.c_str(),assetFiles[i]->assetList[j]->assetName.length()) % assetFiles[i]->assetList.size();
			unsigned int searchHash = crc(reinterpret_cast<unsigned char*>(const_cast<char*>(assetFiles[i]->assetList[j]->assetName.c_str())),assetFiles[i]->assetList[j]->assetName.length());

			sFile.seekg(assetHash*sizeof(int)+HEADERSIZE);
			unsigned int fPos = 0;
			sFile.read(reinterpret_cast<char*>(&fPos),sizeof(int));
			sFile.seekg(fPos);
			unsigned int crc32= 0;
			sFile.read(reinterpret_cast<char*>(&crc32),sizeof(int));
			while (crc32!=searchHash)
			{
				unsigned int fileSize= 0;
				sFile.read(reinterpret_cast<char*>(&fileSize),sizeof(int));
				sFile.seekg(fileSize,std::ios::cur);
				sFile.read(reinterpret_cast<char*>(&crc32),sizeof(int));
			}
			
		}
		cout << "Took: " << double((GetTickCount()-first)/1000) << "s" << endl;
		sFile.close();
	}


}

