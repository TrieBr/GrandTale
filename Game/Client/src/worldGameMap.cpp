

#include "worldGameMap.h"
#include "gameServer.h"
#include "myData.h"
#include "Actions.h"
#include "collisionCheck.h"
#include "tooltipManager.h"
#ifndef _WIN32
#define max(a,b) ((a>b) ? a : b)
#define min(a,b) ((a<b) ? a : b)
#endif
namespace worlds {
void worldGameMap::initialize() {
		this->::gameEngine::abstractWorld::initialize();
		al_hide_mouse_cursor(gameEngine::core::getDisplay()); //Hide the system mouse
		al_register_event_source(this->eventQueue,al_get_mouse_event_source()); //Register the mouse events
		al_register_event_source(this->eventQueue,al_get_keyboard_event_source()); //Register the keyboard events
		cursor = gameEngine::resources::graphics.loadBitmap(":cursor.png"); //Load the logo bitmap
		guiWindowInventory = NULL;
		guiWindowCharacter = NULL;
		SlotController::LoadStaticIcons(); //Load the static icons
		this->mHandler = new mapHandler();
		this->mHandler->loadMap(0);
		camera.x = 0;
		camera.y = 0;

			mainPlayer = new entities::gameMap::entityPlayerMe(&myData::cData);
			this->addEntity(mainPlayer);
			mainPlayer->setDepth(-1);
	

		broadcastPositionInterval = 1.0/20; //1 second
		lastPositionBroadcast = al_get_time();

		NamePlateGUI = new entities::GameGUI::entityGUINamePlate();
		this->addEntity(NamePlateGUI);
		NamePlateGUI->x = 0;
		NamePlateGUI->y = 1;
		NamePlateGUI->setDepth(-5);

		MainBarGUI = new entities::GameGUI::entityGUIMainBar();
		this->addEntity(MainBarGUI);
		MainBarGUI->x = 0;
		MainBarGUI->y = 600;
		MainBarGUI->setDepth(-5);
		
		ChatGUI = new entities::GameGUI::entityGUIChat();
		this->addEntity(ChatGUI);
		ChatGUI->x = 1;
		ChatGUI->y = 600-74;
		ChatGUI->setDepth(-5);

		tooltipManager::initialize();
	}

	void worldGameMap::update(double _timeFactor) {
		if (networking::gameServer::parentWorld==this) {
			networking::gameServer::handle(); //Handle game server if it's parent is set to us
		}
		this->::gameEngine::abstractWorld::update(_timeFactor); 
		//Hold the camera on the main player
		camera.x += (((mainPlayer->getX()-(800/2))-camera.x)/6) * _timeFactor;
		camera.y +=	(((mainPlayer->getY()-(600/2))-camera.y)/6) * _timeFactor;

		//Limit the view so it doesnt go out of bounds
		camera.x = min(max(camera.x,this->mHandler->mData->left),this->mHandler->mData->right-800);
		camera.y = min(max(camera.y,this->mHandler->mData->top),this->mHandler->mData->bottom-600);

		tooltipManager::updateTooltip(_timeFactor);
		//Send the player movement
		if ((al_get_time()-lastPositionBroadcast)>=broadcastPositionInterval){ //1 second		
			
			static positionUpdate playerPos;
			playerPos.X = this->mainPlayer->getX();
			playerPos.Y = this->mainPlayer->getY();
			playerPos.animationID = this->mainPlayer->getRenderer()->animationPlayer.getCurrentSequence()->sequenceID;
			playerPos.animationPosition = this->mainPlayer->getRenderer()->animationPlayer.getCurrentPosition();
			playerPos.animationChanged = false;
			playerPos.animationBlend = this->mainPlayer->getRenderer()->animationPlayer.getLastBlend();
			playerPos.left = this->mainPlayer->lastDirection;
			if (lastUpdate.animationID!=playerPos.animationID) {
				playerPos.animationChanged = true;

			}
				networking::gameServer::sendPositionUpdate(playerPos);
				lastPositionBroadcast = al_get_time();
				lastUpdate = playerPos;
		}
	}

	void worldGameMap::cleanup() {
		delete mHandler;
		tooltipManager::cleanup();
		SlotController::FreeStaticIcons(); //free the static icons
		this->::gameEngine::abstractWorld::cleanup();
	}
	void worldGameMap::render(float offsetX, float offsetY) { //Render the world
		this->mHandler->render(-camera.x,-camera.y);
		this->::gameEngine::abstractWorld::render(-camera.x,-camera.y);

		ALLEGRO_MOUSE_STATE mState; //Mouse state
		al_get_mouse_state(&mState); //Get the state of the mouse
		al_draw_bitmap(cursor,mState.x,mState.y,0);
		tooltipManager::renderTooltip(mState.x,mState.y);
		if (SlotController::IsDraggingSlot()) {
			
			SlotController::GetDraggingSlot()->Render(mState.x-17,mState.y-17,true);
			al_draw_bitmap(SlotController::SlotBorderExpanded,mState.x-17-3,mState.y-17-3,0);
		}
	
	}

	void worldGameMap::addDummyPlayer(entities::gameMap::entityPlayerDummy* newDummy) { //Add a dummy player to the map
		addEntity(newDummy); //Add the dummy to the entity list so it's updated and shit
		this->playerDummyList.push_back(newDummy); //Add the player to the list
	}
	void worldGameMap::addMob(mobDummy* entity) {
		entity->setParentMap(this);
		addEntity(entity);
		this->mobList.push_back(entity);
	}

	mobDummy* worldGameMap::findMobDummy(int UID) {
		for(unsigned int i=0; i<this->mobList.size(); i++) {
			if (this->mobList[i]->getUID()==UID) {
				return this->mobList[i];
			}
		}
		return NULL;
	}

	entities::gameMap::entityPlayerDummy* worldGameMap::findDummyPlayer( short UID) { //Find a dummy player based off their UID
		for(unsigned int i=0; i<this->playerDummyList.size(); i++) {
			if (this->playerDummyList[i]->getUID()==UID) {
				return this->playerDummyList[i];
			}
		}
		return NULL;
	}



	void worldGameMap::openGUIWindow_Inventory() {
		guiWindowInventory = new entities::GameGUI::entityGUIInventory();
		guiWindowInventory->x = 553;
		guiWindowInventory->y = 336;
		addEntity(guiWindowInventory);
	}
		void worldGameMap::closeGUIWindow_Inventory() {
			removeEntity(guiWindowInventory,true);
			guiWindowInventory=NULL;
		}
		entities::GameGUI::entityGUIInventory*	worldGameMap::getGUIWindow_Inventory(){
			return guiWindowInventory;
		}
		bool worldGameMap::isOpen_GUIWindow_Inventory() {
			return !(guiWindowInventory==NULL);
		}

		void	worldGameMap::openGUIWindow_Character(){
			guiWindowCharacter = new entities::GameGUI::entityGUICharacter();
			guiWindowCharacter->x = 553;
			guiWindowCharacter->y = 336;
			addEntity(guiWindowCharacter);
		}
		void	worldGameMap::closeGUIWindow_Character(){
			removeEntity(guiWindowCharacter,true);
			guiWindowCharacter=NULL;
		}
		entities::GameGUI::entityGUICharacter*	worldGameMap::getGUIWindow_Character(){
			return guiWindowCharacter;
		}
		bool	worldGameMap::isOpen_GUIWindow_Character(){
			return !(guiWindowCharacter==NULL);
		}
		void worldGameMap::openGUIWindow_Skills() {
			guiWindowSkills = new entities::GameGUI::entityGUISkills();
			guiWindowSkills->x = 553;
			guiWindowSkills->y = 336;
			addEntity(guiWindowSkills);
		}
		void worldGameMap::closeGUIWindow_Skills() {
			removeEntity(guiWindowSkills,true);
			guiWindowSkills=NULL;
		}
		entities::GameGUI::entityGUISkills*	worldGameMap::getGUIWindow_Skills() {
			return guiWindowSkills;
		}
		bool worldGameMap::isOpen_GUIWindow_Skills() {
			return !(guiWindowSkills==NULL);
		}

		collisionLine* worldGameMap::getLineUnderArea(float x, float y, float width) { //Gets the first line under the specified area

		collisionLine* closestLine = NULL;
		for (int yy=this->mHandler->mData->getHeight(); yy>y; yy--) {
			for (collisionLineListNode* i = this->mHandler->mData->getRootCollisionLine(); i!=NULL; i=i->next) {
				Point p;
				p.x = x;
				p.y = yy;
				if (Collision::pointInLine(p,*i->line)) {
					closestLine = i->line;
				}
			}
		}
		return closestLine;
	
	}
}

