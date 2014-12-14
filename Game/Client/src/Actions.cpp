#include "Actions.h"
#include "worldGameMap.h"
#include "tooltipManager.h"

Slot::Slot(): Border(SlotController::SlotBorder), Background(SlotController::SlotBackground), ExpandedBorder(SlotController::SlotBorderExpanded){
	dropTypesAccepted = S_UNDEFINED;
}

	ALLEGRO_BITMAP* SlotController::AC_Inventory;
	ALLEGRO_BITMAP* SlotController::AC_Social;
	ALLEGRO_BITMAP* SlotController::AC_Quest;
	ALLEGRO_BITMAP* SlotController::AC_Skills;
	ALLEGRO_BITMAP* SlotController::AC_Talents;
	ALLEGRO_BITMAP* SlotController::AC_Pvp;
	ALLEGRO_BITMAP* SlotController::AC_Menu;
	ALLEGRO_BITMAP* SlotController::EquipmentIcons[EQUIP_TYPE_COUNT];
	ALLEGRO_BITMAP* SlotController::EquipmentRing2Icon;
	ALLEGRO_BITMAP*	SlotController::SlotBackground;
	ALLEGRO_BITMAP*  SlotController::SlotBorder;
	ALLEGRO_BITMAP*  SlotController::SlotBorderExpanded;

	Slot* SlotController::dragSlot = NULL;

	void SlotController::LoadStaticIcons(){
		AC_Inventory = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Inventory.png");	
		AC_Social = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Social.png");	
		AC_Quest = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Quest.png");	
		AC_Skills = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Skills.png");	
		AC_Talents = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Talents.png");	
		AC_Pvp = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Pvp.png");	
		AC_Menu = gameEngine::resources::graphics.loadBitmap(":gameGui:ActionBarStaticIcon_Menu.png");	
		SlotBackground = gameEngine::resources::graphics.loadBitmap(":gameGui:actionBarSlotBackground.png");	
		SlotBorder  = gameEngine::resources::graphics.loadBitmap(":gameGui:actionBarBorderBrown.png");	
		SlotBorderExpanded= gameEngine::resources::graphics.loadBitmap(":gameGui:expandedBorder.png");	
		EquipmentIcons[EQUIP_BELT] = gameEngine::resources::graphics.loadBitmap(":gameGui:beltSlot.png");	
		EquipmentIcons[EQUIP_GLOVE] = gameEngine::resources::graphics.loadBitmap(":gameGui:gloveSlot.png");
		EquipmentIcons[EQUIP_HELMET] = gameEngine::resources::graphics.loadBitmap(":gameGui:headSlot.png");
		EquipmentIcons[EQUIP_PANTS] = gameEngine::resources::graphics.loadBitmap(":gameGui:pantSlot.png");
		EquipmentIcons[EQUIP_SHIRT] = gameEngine::resources::graphics.loadBitmap(":gameGui:ShirtSlot.png");
		EquipmentIcons[EQUIP_SHOE] = gameEngine::resources::graphics.loadBitmap(":gameGui:shoeSlot.png");
		EquipmentIcons[EQUIP_SHOULDER] = gameEngine::resources::graphics.loadBitmap(":gameGui:shoulderSlot.png");
		EquipmentIcons[EQUIP_OFFHAND] = gameEngine::resources::graphics.loadBitmap(":gameGui:offhandSlot.png");
		EquipmentIcons[EQUIP_RANGED] = gameEngine::resources::graphics.loadBitmap(":gameGui:rangedSlot.png");
		EquipmentIcons[EQUIP_RING] = gameEngine::resources::graphics.loadBitmap(":gameGui:ring1Slot.png");
		EquipmentRing2Icon = gameEngine::resources::graphics.loadBitmap(":gameGui:ring2Slot.png");
		EquipmentIcons[EQUIP_MAINHAND] = gameEngine::resources::graphics.loadBitmap(":gameGui:mainhandSlot.png");
		EquipmentIcons[EQUIP_TRINKET] = gameEngine::resources::graphics.loadBitmap(":gameGui:trinketSlot.png");
		EquipmentIcons[EQUIP_HEAD_LOWER] = gameEngine::resources::graphics.loadBitmap(":gameGui:lowerheadSlot.png");
		
	}

	void SlotController::FreeStaticIcons(){

	}


	void SlotController::PickupSlot(Slot* slot){
		dragSlot = slot;
	}
	Slot* SlotController::GetDraggingSlot() {
		return dragSlot;
	}
	bool SlotController::IsDraggingSlot(){
		return dragSlot!=NULL;
	}
	void SlotController::CancelPickup(){
		dragSlot = NULL;
	}

	void Slot::Render(float x, float y, bool noTint, bool highlight){
					if (GetIcon()!=NULL) {
						if (SlotController::GetDraggingSlot()==this && noTint==false) {
							al_draw_tinted_bitmap(GetIcon(),al_map_rgba_f(0.3,0.3,0.3,1),x+3,y+3,0);
						}else{
							if (highlight) {
								al_draw_tinted_bitmap(GetIcon(),al_map_rgba_f(1*1,1*1,1*1,0.6*1),x+3,y+3,0);
							}else{
								al_draw_bitmap(GetIcon(),x+3,y+3,0);
							}


							
						}
					}
	}



	void Slot_Action_Inventory::ExetuteAction() {
		if (gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->isOpen_GUIWindow_Inventory()) {
			gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->closeGUIWindow_Inventory();
		}else{
			gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->openGUIWindow_Inventory();
		}
	}

	void Slot_Action_Character::ExetuteAction() {
		if (gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->isOpen_GUIWindow_Character()) {
			gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->closeGUIWindow_Character();
		}else{
			gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->openGUIWindow_Character();
		}
	}

	void Slot_Action_Skills::ExetuteAction() {
		if (gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->isOpen_GUIWindow_Skills()) {
			gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->closeGUIWindow_Skills();
		}else{
			gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->openGUIWindow_Skills();
		}
	}

	void SlotArray::Render(float relativeX, float relativeY){
		short perCol = 0;
		if (rows!=0) {
		perCol = slots.size()/rows;
		}
		short colCount = 0;
		float xx = 0;
		float yy = 0;

		float posX;
		float posY;

		if (relative) {
			posX = relativeX+x;
			posY = relativeY+y;
		}else{
			posX = x;
			posY = y;
		}

		for(short i=0; i<slots.size(); i++) {
			//

			if (slots[i]->GetBackground()!=NULL) { //Draw the background, if its not NULL
				al_draw_bitmap(slots[i]->GetBackground(),posX+xx,posY+yy,0);
			}
			if (i==this->slotHover){ //Mouse is over the slot
				slots[i]->Render(posX+xx,posY+yy,false,true); //Render the Slot.

			}else{
				slots[i]->Render(posX+xx,posY+yy,false,false); //Render the Slot.
			}

			if (slots[i]->GetBorder()!=NULL) { //Render the border, if its not NULL
			al_draw_bitmap(slots[i]->GetBorder(),posX+xx,posY+yy,0);
			}

			xx += colSpacing;
			colCount ++;
			if (colCount>=perCol) {
				yy += rowSpacing;
				colCount = 0;
				xx = 0;
			}
		}
	
	}

	void SlotArray::HandleEvent(ALLEGRO_EVENT &e,float relativeX, float relativeY) {

		short perCol = 0;
		if (rows!=0) {
			perCol = slots.size()/rows;
		}
		short colCount = 0;
		float xx = 0;
		float yy = 0;
		float posX;
		float posY;
		if (relative) {
			posX = relativeX+x;
			posY = relativeY+y;
		}else{
			posX = x;
			posY = y;
		}
		bool hovering = false;
		int oldHover = this->slotHover;
		for(short i=0; i<slots.size(); i++) {
				if (gameEngine::globalFunctions::pointInRegion(gameEngine::core::mouseX,gameEngine::core::mouseY,posX+xx,posY+yy,relativeX+x+xx+32,relativeY+y+yy+32)){
					hovering = true;
					this->slotHover = i;
				}

				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,posX+xx,posY+yy,relativeX+x+xx+32,relativeY+y+yy+32)){
						if (e.mouse.button==2) { //Right click
									slots[i]->ExetuteAction();
						}
						if (e.mouse.button==1) { //Left Click
								if (!SlotController::IsDraggingSlot()) {
									if (slots[i]->CanDrag()) {
										SlotController::PickupSlot(slots[i]);
									}
								}
						}
					}
				}

				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
						if (e.mouse.button==1) { //Left Click
							if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,posX+xx,posY+yy,relativeX+x+xx+32,relativeY+y+yy+32)){
								if (SlotController::IsDraggingSlot()) { //Something is being dragged
									if((slots[i]->dropTypesAccepted & SlotController::GetDraggingSlot()->type)==SlotController::GetDraggingSlot()->type) { //If the dragging slot can be dropped here:
										if (slots[i]->SlotDropped(SlotController::GetDraggingSlot())) {
											SlotController::CancelPickup();
										}
									}
								}
							}
						}
				}
			xx += colSpacing;
			colCount ++;
			if (colCount>=perCol) {
				yy += rowSpacing;
				colCount = 0;
				xx = 0;
			}
		}
		if (!hovering) this->slotHover = -1;
		if (oldHover != this->slotHover) { //Hovering item has changed
			if (slotHover==-1) tooltipManager::setTooltip(NULL);
			else tooltipManager::setTooltip(slots[slotHover]->GenerateTooltip()); //Generate tooltip on hovered item, set it as tooltip
			
		}
	}
	


	bool Slot_EquipmentSlot::SlotDropped(Slot* src){ //A slot was dropped onto this one
		if(src->type==S_ITEMCONTAINER) { //From the inventory
			networking::gameServer::itemContainer_SwapSlots(this->referenceContainer,reinterpret_cast<Slot_ItemContainerReference*>(src)->referenceContainer,this->referenceSlot,reinterpret_cast<Slot_ItemContainerReference*>(src)->referenceSlot);
				return true;
		}
		return false;
	}
	