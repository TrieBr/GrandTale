// ----------------------------------------------------------------------
// resourcePack.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Handles a resource package (.gtd file). Keeps the file open until the resourcePack is destroyed.
*/
// ------------------------------------------------------------------------


#include "resourcePack.h"
#include "customAllegroInterface.h"
#include <sstream>
#include "settings.h"
//#include <CoreFoundation/CoreFoundation.h>

namespace resourceManager
{

	ALLEGRO_FILE_INTERFACE resourcePack::allegroInterface; //The allegro file I/O interface
	void resourcePack::initializeAllegroInterface() { //Initialize the allegro interface
		allegroInterface.fi_fopen = cAI_fopen;
		allegroInterface.fi_fclose = cAI_fclose;
		allegroInterface.fi_fread = cAI_fread;
		allegroInterface.fi_fwrite = cAI_fwrite;
		allegroInterface.fi_fflush = cAI_fflush;
		allegroInterface.fi_ftell = cAI_ftell;
		allegroInterface.fi_fseek = cAI_fseek;
		allegroInterface.fi_feof = cAI_feof;
		allegroInterface.fi_ferror = cAI_ferror;
		allegroInterface.fi_fclearerr = cAI_fclearerr;
		allegroInterface.fi_fungetc = NULL;
		allegroInterface.fi_fsize = cAI_fsize;	
	}

	resourcePack::resourcePack(std::string fileName) { //The name of the resource pack to open.
		load(fileName);
	}

	resourcePack::resourcePack() { //The default consturctor
	}

	void resourcePack::load(std::string fileName) { //Load the specified file
        std::string fOpen = fileName;
        
#ifdef GTIOS
            //Because of the way IOS bundles files, we have to use some magic to find the file path
            CFURLRef manifest_url = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
                                                        CFSTR("Graphics"),CFSTR("gtd"),
                                                            NULL);
            char manifest_path[1024];
            CFURLGetFileSystemRepresentation(manifest_url, true, (unsigned char*)manifest_path, 1024);
            CFRelease(manifest_url);
            std::string bundleFName = manifest_path;
            bundleFName = bundleFName.substr(0,bundleFName.find_last_of('/')+1);
            fOpen = bundleFName.append(fileName);
#endif
		std::fstream f(fOpen.c_str());
			if (f.is_open()) {
				f.close();
			}else{
				fOpen.replace(0,fOpen.find_last_of("/")+1,"");
			}

		resourceFile.open(fOpen.c_str(),std::ios::in | std::ios::out | std::ios::binary); //Open the resource file
		assert(resourceFile.is_open()); //Assert if the resource couldn't be opened.
		if (resourceFile.is_open())
		{
			resourceFile.read(reinterpret_cast<char*>(&subFileCount),sizeof(int)); //Read the number of subfiles.
		}else{
			std::cout << "Could not open resource file: " << fOpen << std::endl; //Print an error
		}
	}

	resourcePack::~resourcePack() { //Desturctor
		//Close all the subfiles that are open
		for (unsigned int i=0; i<this->openSubFiles.size(); i++) {//For each subFilethat is open
				if (this->openSubFiles[i]->closeFileHandle) {
					al_fclose(this->openSubFiles[i]->fileHandle); //Close the allegro handle
				}
				delete this->openSubFiles[i]; //Delete the subFile
				this->openSubFiles[i] = NULL;
		}
		this->openSubFiles.clear();
		resourceFile.close(); //Close the resource File
	}

	ALLEGRO_FILE* resourcePack::openSubFile(std::string fileName, bool closeFileHandle) { //Opens a subfile in the resource pack (fileName example: :Gfol:file.png)
		subFile *newSubFile = new subFile();
		newSubFile->mainFileOffset = findSubFile(fileName); //Set the main offset (+4 for the DWORD of the file length);
		resourceFile.seekg(newSubFile->mainFileOffset); //Seek to the sub file
		resourceFile.read(reinterpret_cast<char*>(&newSubFile->fileLength),sizeof(int)); //Read the size of the subfile
		newSubFile->currentOffset = 0; //Current offset is 0
		newSubFile->parentResourcePack = this; //Set the parent resourcePack
		newSubFile->fileHandle = al_create_file_handle(&allegroInterface,newSubFile); //Create the allegro file handle
		newSubFile->closeFileHandle = closeFileHandle; //Close the file handle during cleanup?
		this->openSubFiles.push_back(newSubFile); //Add a subfile that is open to the list.
		return newSubFile->fileHandle; //Return the allegro file handle
	}
	void resourcePack::closeSubFile(ALLEGRO_FILE* fClose) { //Closes and frees the sub file
		for (unsigned int i=0; i<this->openSubFiles.size(); i++) {//For each subFilethat is open
			if (this->openSubFiles[i]->fileHandle==fClose){//If the subfile is the one we want
				al_fclose(fClose); //Close the allegro handle
				delete this->openSubFiles[i]; //Delete the subFile
				this->openSubFiles.erase(this->openSubFiles.begin()+i); //Erase from the vector
				break;
			}
		}
	}

	unsigned int resourcePack::findSubFile(std::string subFileName) { //Find the offset of a subfile. The subfile name must be in the ":" notation( eg. :Folder:File.extension)
			unsigned int assetHash =  hashFunction(subFileName.c_str(),subFileName.length()) % this->subFileCount; //Get the hash for the hash table
			unsigned int searchHash = crc32(reinterpret_cast<unsigned char*>(const_cast<char*>(subFileName.c_str())),subFileName.length()); //Get the crc32 hash for collisions
			resourceFile.seekg((assetHash*sizeof(int))+HEADERSIZE,std::ios::beg); //Seek to the bucket in the hash table
			unsigned int fPos = 0; //The position in the file
			resourceFile.read(reinterpret_cast<char*>(&fPos),sizeof(int)); //Read the position of the subfile in the main file
			resourceFile.seekg(fPos,std::ios::beg); //Seek to the file
			unsigned int crc32val= 0; //Declare crc32 value
			resourceFile.read(reinterpret_cast<char*>(&crc32val),sizeof(int)); //Read the crc32 of the subfile, to make sure it matches
			while (crc32val!=searchHash)
			{//While the crc32 doesnt match...
				if (resourceFile.eof()) {
					std::cout << "Unable to find file in resource: " << subFileName << std::endl;
					
				}
				unsigned int fileSize= 0; //The filesize
				resourceFile.read(reinterpret_cast<char*>(&fileSize),sizeof(int)); //Read the filesize
				resourceFile.seekg(fileSize,std::ios::cur); //Seek past the file
				resourceFile.read(reinterpret_cast<char*>(&crc32val),sizeof(int)); //Read the crc32 of the next file.
			}
		return resourceFile.tellg(); //Return the offset
	}

	unsigned int resourcePack::hashFunction(const char *key, unsigned int len) { //Primary hash function for getting an index from a resource name
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


	ALLEGRO_BITMAP* managedResourcePack::loadBitmap(std::string resourceName){
		if (loadedBitmaps.find(resourceName)==loadedBitmaps.end()) {
			 ALLEGRO_BITMAP* resource = al_load_bitmap_f(openSubFile(resourceName),".png");
			if (resource!=NULL) { //If resource was loaded
				loadedBitmaps[resourceName] = resource;
				bitmapReferences[resource] = 1;
				return resource;
			}
		}else{
			bitmapReferences.find(loadedBitmaps.find(resourceName)->second)->second += 1;
			return loadedBitmaps.find(resourceName)->second;
		}
		return NULL;
	}
	ALLEGRO_FONT* managedResourcePack::loadFont(std::string resourceName, int size, int flags){
		 // TODO: Function has a shit load of map lookups, so caching should be added
		 std::stringstream lookupString;
		 lookupString << resourceName << size; //Since fonts have to be loaded for each size, we need the lookup to be specific to the size specified
		if (loadedFonts.find(lookupString.str())==loadedFonts.end()) {
			ALLEGRO_FONT* resource = al_load_ttf_font_f(openSubFile(resourceName,false),"",size,flags); 
			if (resource !=NULL) { //If resource was loaded
				loadedFonts[lookupString.str()] = resource ;
				fontReferences[resource ] = 1;
				return resource;
			}
		}else{
			fontReferences.find(loadedFonts.find(lookupString.str())->second)->second +=1;
			return loadedFonts.find(lookupString.str())->second;
		}
		return NULL;
	}

	void managedResourcePack::cleanUp() {
		if (fontReferences.size()>0) {
			std::cout << "Some fonts still have references!" << std::endl;
			for(std::map<std::string,ALLEGRO_FONT*>::const_iterator i = loadedFonts.begin(); i!=loadedFonts.end(); i++) {
				std::cout << "\t" << i->first << std::endl;
			}
			for( std::map<ALLEGRO_FONT*,int>::const_iterator i = fontReferences.begin(); i!=fontReferences.end(); i++) {
				al_destroy_font(i->first);
			}
		}
		if (bitmapReferences.size()>0) {
			std::cout << "Some bitmaps still have references!" << std::endl;
			for(std::map<std::string, ALLEGRO_BITMAP*>::const_iterator i = loadedBitmaps.begin(); i!=loadedBitmaps.end(); i++) {
				std::cout << "\t" << i->first << std::endl;
			}
			for(std::map<ALLEGRO_BITMAP*,int>::const_iterator i = bitmapReferences.begin(); i!=bitmapReferences.end(); i++) {
				al_destroy_bitmap(i->first);
			}
		}

	}
}