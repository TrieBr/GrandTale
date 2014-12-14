// ----------------------------------------------------------------------
// customAllegroInterface.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	Implements the custom allegro file I/O interface that works with the data files for Grand Tale.
*/
// ------------------------------------------------------------------------
#include "customAllegroInterface.h"
#include "resourcePack.h"



void* cAI_fopen(const char *path, const char *mode) {

	return NULL;
}

void cAI_fclose(ALLEGRO_FILE *f) {

}

size_t cAI_fread(ALLEGRO_FILE *f, void *ptr, size_t size) {
	resourceManager::subFile *subFileData = reinterpret_cast<resourceManager::subFile*>(al_get_file_userdata(f)); //Get the subFile handle for this ALLEGRO_FILE

	subFileData->parentResourcePack->resourceFile.seekg(subFileData->mainFileOffset+4+subFileData->currentOffset); //Seek to the position where we left off..
	subFileData->parentResourcePack->resourceFile.read(reinterpret_cast<char*>(ptr),size); //Read the data 
	subFileData->currentOffset+=size; //Increase our position
	return size; //Return the amount of bytes read

}

size_t cAI_fwrite(ALLEGRO_FILE *f, const void *ptr, size_t size) {
	return 0; //Writing is disabled.
}

bool cAI_fflush(ALLEGRO_FILE *f) {
	return false; //Flushing is diables.
}

int64_t cAI_ftell(ALLEGRO_FILE *f) {
	resourceManager::subFile *subFileData = reinterpret_cast<resourceManager::subFile*>(al_get_file_userdata(f)); //Get the subFile handle for this ALLEGRO_FILE
	return subFileData->currentOffset; //Return our offset in the subfile
}

bool cAI_fseek(ALLEGRO_FILE *f, int64_t offset, int whence) {
	resourceManager::subFile *subFileData = reinterpret_cast<resourceManager::subFile*>(al_get_file_userdata(f)); //Get the subFile handle for this ALLEGRO_FILE
	switch (whence)
	{
	case ALLEGRO_SEEK_SET:
		{
			subFileData->currentOffset = offset;
			break;
		}
	case ALLEGRO_SEEK_CUR:
		{
			subFileData->currentOffset += offset;
			break;
		}
	case ALLEGRO_SEEK_END:
		{
			subFileData->currentOffset = subFileData->fileLength-offset;
			break;
		}
	}
	return true;
}

bool cAI_feof(ALLEGRO_FILE *f) {
	resourceManager::subFile *subFileData = reinterpret_cast<resourceManager::subFile*>(al_get_file_userdata(f)); //Get the subFile handle for this ALLEGRO_FILE
	if (subFileData->currentOffset>=subFileData->fileLength)
	{
		return true;
	}
	return false;
}
bool cAI_ferror(ALLEGRO_FILE *f) {
	return false;
}

void cAI_fclearerr(ALLEGRO_FILE *f) {

}

int	 cAI_fungetc(ALLEGRO_FILE *f, int c) {
	return 0;
}

off_t cAI_fsize(ALLEGRO_FILE *f) {
	resourceManager::subFile *subFileData = reinterpret_cast<resourceManager::subFile*>(al_get_file_userdata(f)); //Get the subFile handle for this ALLEGRO_FILE
	return subFileData->fileLength; //Return the size
}