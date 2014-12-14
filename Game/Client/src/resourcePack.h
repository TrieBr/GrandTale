// ----------------------------------------------------------------------
// resourcePack.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Handles a resource package (.gtd file). Keeps the file open until the resourcePack is destroyed.
*/
// ------------------------------------------------------------------------
#include <string>
#include <map>

#include <fstream>
#include <assert.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include "crc32.h"

#ifndef _H_RESOURCEPACK
#define _H_RESOURCEPACK

#define HEADERSIZE 4
namespace resourceManager
{
	class resourcePack;
	struct subFile
	{
		unsigned int mainFileOffset; //Offset of the subfile in the main file
		unsigned int currentOffset; //Current offset in the subfile (offset in main file = mainFileOffset+currentOffset+4(DWORD for file size)
		unsigned int fileLength; //Length of the subfile
		resourcePack* parentResourcePack; //The parent resourcePack handling this subfile
		ALLEGRO_FILE* fileHandle; //The ALLEGRO_FILE file handle
		bool closeFileHandle;
	};

	class resourcePack
	{
	public:
		resourcePack(std::string fileName); //The name of the resource pack to open.
		resourcePack(); //Constructor
		~resourcePack(); //Desturctor
		void load(std::string fileName); //Load the specified file
		ALLEGRO_FILE* openSubFile(std::string fileName,bool closeFileHandle = true); //Opens a subfile in the resource pack (fileName example: :Gfol:file.png)
		void closeSubFile(ALLEGRO_FILE* fClose); //Closes and frees the sub file
		std::fstream resourceFile; //The handle of the resource File that is being used
		static ALLEGRO_FILE_INTERFACE allegroInterface; //The allegro file I/O interface
		static void initializeAllegroInterface(); //Initialize the allegro interface
	private:
		unsigned int hashFunction(const char *key, unsigned int len); //Primary hash function for getting an index from a resource name
		unsigned int findSubFile(std::string subFileName); //Find the offset of a subfile. The subfile name must be in the ":" notation( eg. :Folder:File.extension)
		std::vector<subFile*> openSubFiles; //List of subfiles that are open
		unsigned int subFileCount; //Number of subfiles in the package
	};

	/*
		Similar to above class, but this loads ALLEGRO_<Resources>, and returns a pointer to them. It prevents loading of the same resource twice, and also keeps reference counts.
	*/
	class managedResourcePack : public resourcePack {
	public:
		ALLEGRO_BITMAP* loadBitmap(std::string resourceName);
		ALLEGRO_FONT* loadFont(std::string resourceName, int size, int flags = 0);
		void cleanUp();
			
	private:
		std::map<ALLEGRO_BITMAP*,int>				bitmapReferences;
		std::map<ALLEGRO_FONT*,int>					fontReferences;
		std::map<std::string,ALLEGRO_BITMAP*>		loadedBitmaps;
		std::map<std::string,ALLEGRO_FONT*>			loadedFonts;

	};

}

#endif