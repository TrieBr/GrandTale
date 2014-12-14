#include <mapCollisionData.h>

mapCollisionData::mapCollisionData() {
	left = 0;
	top = 0;
	right = 1000;
	bottom = 1000;
rootNode = NULL;
}

mapCollisionData::~mapCollisionData() { //Clean up tiles..



}

void mapCollisionData::addCollisionLine(collisionLine* newLine) { //Adds a collision line

	if (rootNode==NULL) {
		rootNode = new collisionLineListNode(); //Create the root
		rootNode->prev = rootNode; //Set previous to the last node in chain, which is the root
		rootNode->next = NULL; //Next is null, nothing else in chain
		rootNode->line = newLine;
	}else{
		collisionLineListNode* newNode = new collisionLineListNode();
		newNode->line = newLine;
		newNode->next = NULL;
		newNode->prev = rootNode->prev; //Previous is what the root initially pointed to as the end
		rootNode->prev->next = newNode;
		rootNode->prev = newNode; //Root previous now points to the end
	}
		

	//this->collisionLineList.push_back(newLine);
}

collisionLineListNode* mapCollisionData::getRootCollisionLine() {
	return rootNode;
}

void mapCollisionData::removeCollisionLine(collisionLine* line) { //Removes a collision line
	for (collisionLineListNode* i = getRootCollisionLine(); i!=NULL; i=i->next) {
		
		if (i->line==line) {
			
			
    		i->prev->next = i->next;
			i->next->prev = i->prev;
			if (this->rootNode==i) {
               rootNode = rootNode->next;
			   rootNode->prev->next = NULL;
			}
			
   			delete i->line;
			delete i;
			break;
		}
	}
}

int mapCollisionData::getCollisionLineCount() {
	int c=0;
	for (collisionLineListNode* i = getRootCollisionLine(); i!=NULL; i=i->next) {
		c++;
	}
	return c;
}

void mapCollisionData::loadMapData(ALLEGRO_FILE* fileStream) { //Load all the tiles, blocks, etc
		al_fseek(fileStream,0,ALLEGRO_SEEK_SET);
		unsigned int offset_settings = 0;
		unsigned int offset_collision = 0;
		al_fread(fileStream,&offset_settings,sizeof(int));
		al_fread(fileStream,&offset_collision,sizeof(int));


		al_fseek(fileStream,offset_settings,ALLEGRO_SEEK_SET);

		al_fread(fileStream,&this->left,sizeof(int)); //Read start of line
		al_fread(fileStream,&this->top,sizeof(int)); //Read start of line
		al_fread(fileStream,&this->right,sizeof(int)); //Read start of line
		al_fread(fileStream,&this->bottom,sizeof(int)); //Read start of line

		al_fseek(fileStream,offset_collision,ALLEGRO_SEEK_SET);
		
		int collisionLineList;
		al_fread(fileStream,&collisionLineList,sizeof(int));
		for (unsigned int i=0; i<collisionLineList; i++) {
			collisionLine* newCLine = new collisionLine();

			int buffer;
			al_fread(fileStream,&buffer,sizeof(int)); //Read start of line
			newCLine->p1.x = buffer;
			al_fread(fileStream,&buffer,sizeof(int)); //Read start of line
			newCLine->p1.y = buffer;
			al_fread(fileStream,&buffer,sizeof(int)); //Read end of line
			newCLine->p2.x = buffer;
			al_fread(fileStream,&buffer,sizeof(int)); //Read end of line
			newCLine->p2.y = buffer;
			al_fread(fileStream,&newCLine->jumpthrough,sizeof(bool)); //jumpthrough platform?
			addCollisionLine(newCLine);
		}
}
