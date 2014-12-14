
#include "entityGUIInventory.h"
#include "myData.h"
#include "worldGameMap.h"

namespace entities
{
	namespace GameGUI
	{

			entityGUIInventory::entityGUIInventory() : abstractDraggableWindow(106,27){
				background = gameEngine::resources::graphics.loadBitmap(":gameGui:guiInventoryBackground.png");
			closeButtonImage = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCloseButton.png");
			tabPanels[0] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiInventoryTabUsableBackground.png");
			tabPanels[1] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiInventoryTabGearBackground.png");
			tabPanels[2] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiInventoryTabItemsBackground.png");

			nameFont = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",16);
			 closeButton = new GUI::widgets::button(closeButtonImage,GUI::widgets::HOVER_HIGHLIGHT);
			selectTab(0);
			RefreshInventory();

			}
			void entityGUIInventory::initialize(){
				abstractDraggableWindow::addOpenWindow(this);
				abstractDraggableWindow::setWindowFront(this);
			}
			void entityGUIInventory::cleanup(){
				delete closeButton;
				abstractDraggableWindow::closeOpenWindow(this);

			}
			void entityGUIInventory::render(float oX,float oY){
			al_draw_bitmap(background,x,y,0);
			
			al_draw_bitmap(tabPanels[selectedTab],x+7,y+34,0);
			UsableItems.Render(x,y);
			closeButton->render(x+212,y+5,1);
			}
			void entityGUIInventory::update(double _timeFactor){
				closeButton->update(x+212,y+5);
				if (closeButton->fullClicked()) {
					gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->closeGUIWindow_Inventory();
				}
			}
			bool entityGUIInventory::handleEvent(ALLEGRO_EVENT &e){
				UsableItems.HandleEvent(e,x,y);
				dragHandleEvent(e);
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x+7,y+34,65,27)) {
						selectTab(0);
					}
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x+74,y+34,65,27)) {
						selectTab(1);
					}
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x+141,y+34,65,27)) {
						selectTab(2);
					}
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x,y,241,187)) {
						return true;
					}
				}

				return false;
			}

			void entityGUIInventory::RefreshInventory() {
				UsableItems.rows = 3;
				UsableItems.editable = false;
				 UsableItems.relative = true;
				 UsableItems.x = 10;
				 UsableItems.y = 65;
				 UsableItems.rowSpacing = 38;
				 UsableItems.colSpacing = 38;
				 UsableItems.slots.clear();

				 for (int i=0; i<myData::Inventory_Equip.getSize(); i++) {
					 switch (selectedTab) {
					 case 0: UsableItems.slots.push_back(new Slot_ItemContainerReference(&myData::Inventory_Usable,i)); break; // TODO: Free this SlotEntry sometime
					 case 1: UsableItems.slots.push_back(new Slot_ItemContainerReference(&myData::Inventory_Equip,i)); break;
					 case 2: UsableItems.slots.push_back(new Slot_ItemContainerReference(&myData::Inventory_Regular,i)); break;
					 }
				 }
			}

			void entityGUIInventory::selectTab(int id) {
				selectedTab = id;
				RefreshInventory();
			}
	}
}

