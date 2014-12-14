// ----------------------------------------------------------------------
// worldGameMap.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	A map for the game. Consists of tiles, collision objects, players, etc
*/
// ------------------------------------------------------------------------



#include "gameEngine.h"

#include "mapHandler.h"
#include "entityPlayerMe.h"
#include "entityPlayerDummy.h"
#include "entityGUINamePlate.h"
#include "entityGUIMainBar.h"
#include "entityGUIChat.h"
#include "entityGUIInventory.h"
#include "entityGUICharacter.h"
#include "entityGUISkills.h"
#include "mobDummy.h"

namespace worlds
{
	
	class worldGameMap : public gameEngine::abstractWorld
	{
	public:
		void initialize();
		void render(float offsetX=0, float offsetY=0);
		void cleanup();
		void update(double _timeFactor);
		void addDummyPlayer(entities::gameMap::entityPlayerDummy* newDummy);
		void addMob(mobDummy* entity);
		mobDummy* findMobDummy(int UID);
		entities::gameMap::entityPlayerDummy* findDummyPlayer( short UID); //Find a dummy player based off their UID
		mapHandler					*mHandler; //mapHandler
		entities::GameGUI::entityGUIChat* getGUI_Chat() { return ChatGUI; }

		//GUI Windows
		void									openGUIWindow_Inventory();
		void									closeGUIWindow_Inventory();
		entities::GameGUI::entityGUIInventory*	getGUIWindow_Inventory();
		bool									isOpen_GUIWindow_Inventory();
		void									openGUIWindow_Character();
		void									closeGUIWindow_Character();
		entities::GameGUI::entityGUICharacter*	getGUIWindow_Character();
		bool									isOpen_GUIWindow_Character();
		void									openGUIWindow_Skills();
		void									closeGUIWindow_Skills();
		entities::GameGUI::entityGUISkills*	getGUIWindow_Skills();
		bool									isOpen_GUIWindow_Skills();


		entities::gameMap::entityPlayerMe* mainPlayer; //Main player entity

		collisionLine* getLineUnderArea(float x, float y, float width); //Gets the first line under the specified area
	private:
		ALLEGRO_BITMAP				*cursor; //Cursor sprite
		Point						camera;
		double						broadcastPositionInterval;
		double						lastPositionBroadcast;
		
		std::vector<entities::gameMap::entityPlayerDummy*> playerDummyList; //List of dummy players on the map
		std::vector<mobDummy*> mobList;
		//GUI
		entities::GameGUI::entityGUINamePlate* NamePlateGUI;
		entities::GameGUI::entityGUIMainBar*	MainBarGUI;
		entities::GameGUI::entityGUIChat*		ChatGUI;
		//GUI Windows
		entities::GameGUI::entityGUIInventory* guiWindowInventory;
		entities::GameGUI::entityGUICharacter* guiWindowCharacter;
		entities::GameGUI::entityGUISkills* guiWindowSkills;
		positionUpdate lastUpdate;
	};
}