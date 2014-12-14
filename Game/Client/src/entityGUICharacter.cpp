
#include "entityGUICharacter.h"
#include "myData.h"
#include "worldGameMap.h"
#include "characterAnimationSequenceManager.h"
#include <formulas.h>
namespace entities
{
	namespace GameGUI
	{

			entityGUICharacter::entityGUICharacter() : abstractDraggableWindow(106,27){
				background = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterBackground.png");
			closeButtonImage = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCloseButton.png");

			tabPanels[0] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterTabGear.png");
			tabPanels[1] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterTabStats.png");

		raceBackgrounds[RACE_ELDER] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterPreviewBackground_Elder.png");
		raceBackgrounds[RACE_OORKA] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterPreviewBackground_Oorka.png");
		raceBackgrounds[RACE_UNDEAD] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterPreviewBackground_Undead.png");
		raceBackgrounds[RACE_NORELF] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCharacterPreviewBackground_Norelf.png");

			nameFont = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",16);
			statFont = gameEngine::resources::fonts.loadFont(":gameGui:smallPixel.ttf",8);
			leftButton= gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonLeft.png");
			rightButton=  gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonRight.png");
			button_str_left = new GUI::widgets::button(leftButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_str_right= new GUI::widgets::button(rightButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_int_left= new GUI::widgets::button(leftButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_int_right= new GUI::widgets::button(rightButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_dex_left= new GUI::widgets::button(leftButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_dex_right= new GUI::widgets::button(rightButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_agi_left= new GUI::widgets::button(leftButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_agi_right= new GUI::widgets::button(rightButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_vit_left= new GUI::widgets::button(leftButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_vit_right= new GUI::widgets::button(rightButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_luk_left= new GUI::widgets::button(leftButton,GUI::widgets::HOVER_HIGHLIGHT);
			button_luk_right= new GUI::widgets::button(rightButton,GUI::widgets::HOVER_HIGHLIGHT);


			leftColumn.colSpacing = 0;
			leftColumn.editable = false;
			leftColumn.relative = true;
			leftColumn.rows = 5;
			leftColumn.rowSpacing = 40;
			leftColumn.x = 12;
			leftColumn.y = 64;
			leftColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_HELMET,&myData::equipmentContainer,EQUIP_HELMET));
			leftColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_HEAD_LOWER,&myData::equipmentContainer,EQUIP_HEAD_LOWER));
			leftColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_SHIRT,&myData::equipmentContainer,EQUIP_SHIRT));
			leftColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_BELT,&myData::equipmentContainer,EQUIP_BELT));
			leftColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_PANTS,&myData::equipmentContainer,EQUIP_PANTS));

			bottomRow.colSpacing = 39;
			bottomRow.editable = false;
			bottomRow.relative = true;
			bottomRow.rows = 1;
			bottomRow.rowSpacing = 0;
			bottomRow.x = 63;
			bottomRow.y = 224;
			bottomRow.slots.push_back(new Slot_EquipmentSlot(EQUIP_MAINHAND,&myData::equipmentContainer,EQUIP_MAINHAND));
			bottomRow.slots.push_back(new Slot_EquipmentSlot(EQUIP_OFFHAND,&myData::equipmentContainer,EQUIP_OFFHAND));
			bottomRow.slots.push_back(new Slot_EquipmentSlot(EQUIP_RANGED,&myData::equipmentContainer,EQUIP_RANGED));


			rightColumn.colSpacing = 0;
			rightColumn.editable = false;
			rightColumn.relative = true;
			rightColumn.rows = 5;
			rightColumn.rowSpacing = 40;
			rightColumn.x = 192;
			rightColumn.y = 64;
			rightColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_GLOVE,&myData::equipmentContainer,EQUIP_GLOVE));
			rightColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_SHOE,&myData::equipmentContainer,EQUIP_SHOE));
			rightColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_RING,&myData::equipmentContainer,EQUIP_RING));
			rightColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_RING,&myData::equipmentContainer,EQUIP_RING2));
			rightColumn.slots.push_back(new Slot_EquipmentSlot(EQUIP_TRINKET,&myData::equipmentContainer,EQUIP_TRINKET));

			previewRenderer.initialize(&myData::cData);

			if (myData::myPlayer!=NULL) previewRenderer.setAnimation(myData::myPlayer->getIdleSequence(),character::ANIMATION_LOOP); //Get the players idle sequence
			else
			previewRenderer.setAnimation(character::characterAnimationSequenceManager::getSequence(SEQ_IDLE),character::ANIMATION_LOOP); //Else, use default idle sequence

			closeButton = new GUI::widgets::button(closeButtonImage,GUI::widgets::HOVER_HIGHLIGHT);
			selectTab(0);

			
			}
			void entityGUICharacter::initialize(){
				abstractDraggableWindow::addOpenWindow(this);
				abstractDraggableWindow::setWindowFront(this);
			}
			void entityGUICharacter::cleanup(){
				delete button_str_left;
			delete button_str_right;
			delete button_int_left;
			delete button_int_right;
			delete button_dex_left;
			delete button_dex_right;
			delete button_agi_left;
			delete button_agi_right;
			delete button_vit_left;
			delete button_vit_right;
			delete button_luk_left;
			delete button_luk_right;
				delete closeButton;
				abstractDraggableWindow::closeOpenWindow(this);
			}
			void entityGUICharacter::render(float oX,float oY){
			al_draw_bitmap(background,x,y,0);
			
			al_draw_bitmap(tabPanels[selectedTab],x+5,y+32,0);
			if (selectedTab==0) {
				al_draw_bitmap(raceBackgrounds[(RACE)myData::cData.getRace()],x+52,y+64,0);
				leftColumn.Render(x,y);
				bottomRow.Render(x,y);
				rightColumn.Render(x,y);
				al_set_clipping_rectangle(x+52+3,y+64+3,132,154);
				previewRenderer.render(x+122,y+174);
				al_set_clipping_rectangle(0,0,al_get_display_width(al_get_current_display()),al_get_display_width(al_get_current_display()));
			}
			if (selectedTab==1) {
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16,y+213,0,"%i",0); //aspd
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16,y+213+19,0,"%.2f",formulas::calculateCrit(myData::myCombatEntity.getTotalStat(STAT_LUK))); //crit
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16,y+213+38,0,"%i",formulas::calculateWeight(myData::myCombatEntity.getTotalStat(STAT_STR),myData::myCombatEntity.getLevel())); //weight

				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16+81,y+213,0,"%i",formulas::calculateHit(myData::myCombatEntity.getTotalStat(STAT_DEX),myData::myCombatEntity.getLevel()) ); //hit
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16+81,y+213+19,0,"%i",formulas::calculateFlee(myData::myCombatEntity.getTotalStat(STAT_AGI),myData::myCombatEntity.getLevel())); //flee

				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16+158,y+213,0,"%i",myData::myCombatEntity.getTotalStat(STAT_HP)); //hp
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+16+158,y+213+19,0,"%i",myData::myCombatEntity.getTotalStat(STAT_HP)); //sp


				al_draw_textf(statFont,al_map_rgb(191,12,12),x+165+27,y+122,ALLEGRO_ALIGN_CENTRE ,"%i",myData::myCombatEntity.getBaseStat(STAT_ATK)); //attack
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+165+27,y+122+19,ALLEGRO_ALIGN_CENTRE ,"%i",myData::myCombatEntity.getBaseStat(STAT_MAGIC_ATK)); //m attack
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+165+27,y+122+38,ALLEGRO_ALIGN_CENTRE ,"%.2f",(float)myData::myCombatEntity.getBaseStat(STAT_DEF)); //defence
				al_draw_textf(statFont,al_map_rgb(191,12,12),x+165+27,y+122+57,ALLEGRO_ALIGN_CENTRE ,"%.2f",(float)myData::myCombatEntity.getBaseStat(STAT_MAGIC_DEF)); //m defence

				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85,y+54,ALLEGRO_ALIGN_CENTRE,"%i",myData::myCombatEntity.getBaseStat(STAT_STR)); //STR
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85,y+54+23,ALLEGRO_ALIGN_CENTRE,"%i",myData::myCombatEntity.getBaseStat(STAT_INT)); // INT
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85,y+54+46,ALLEGRO_ALIGN_CENTRE,"%i",myData::myCombatEntity.getBaseStat(STAT_DEX)); //DEX
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85,y+54+69,ALLEGRO_ALIGN_CENTRE,"%i",myData::myCombatEntity.getBaseStat(STAT_AGI)); //AGI
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85,y+54+92,ALLEGRO_ALIGN_CENTRE,"%i",myData::myCombatEntity.getBaseStat(STAT_VIT)); //VIT
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85,y+54+115,ALLEGRO_ALIGN_CENTRE,"%i",myData::myCombatEntity.getBaseStat(STAT_LUK)); //LUK

				//POINT COST
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85+56,y+54,ALLEGRO_ALIGN_CENTRE,"%i",formulas::statRequiredToUpgrade(myData::myCombatEntity.getBaseStat(STAT_STR))); //STR
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85+56,y+54+23,ALLEGRO_ALIGN_CENTRE,"%i",formulas::statRequiredToUpgrade(myData::myCombatEntity.getBaseStat(STAT_INT))); // INT
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85+56,y+54+46,ALLEGRO_ALIGN_CENTRE,"%i",formulas::statRequiredToUpgrade(myData::myCombatEntity.getBaseStat(STAT_DEX))); //DEX
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85+56,y+54+69,ALLEGRO_ALIGN_CENTRE,"%i",formulas::statRequiredToUpgrade(myData::myCombatEntity.getBaseStat(STAT_AGI))); //AGI
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85+56,y+54+92,ALLEGRO_ALIGN_CENTRE,"%i",formulas::statRequiredToUpgrade(myData::myCombatEntity.getBaseStat(STAT_VIT))); //VIT
				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+85+56,y+54+115,ALLEGRO_ALIGN_CENTRE,"%i",formulas::statRequiredToUpgrade(myData::myCombatEntity.getBaseStat(STAT_LUK))); //LUK


				al_draw_textf(nameFont,al_map_rgb(44,17,19),x+192,y+77,ALLEGRO_ALIGN_CENTRE,"%i",myData::miscData.getRemainingStatPoints()); //Remaining
				
				button_str_left->render(x+41,y+58,1);
				button_str_right->render(x+41+63,y+58,1);
				button_int_left->render(x+41,y+58+23,1);
				button_int_right->render(x+41+63,y+58+23,1);
				button_dex_left->render(x+41,y+58+46,1);
				button_dex_right->render(x+41+63,y+58+46,1);
				button_agi_left->render(x+41,y+58+69,1);
				button_agi_right->render(x+41+63,y+58+69,1);
				button_vit_left->render(x+41,y+58+92,1);
				button_vit_right->render(x+41+63,y+58+92,1);
				button_luk_left->render(x+41,y+58+115,1);
				button_luk_right->render(x+41+63,y+58+115,1);

			}
			closeButton->render(x+212,y+5,1);
			}
			void entityGUICharacter::update(double _timeFactor){
				previewRenderer.animationPlayer.stepAnimation(_timeFactor);
				closeButton->update(x+212,y+5);

				button_str_left->update(x+41,y+58);
				button_str_right->update(x+41+63,y+58);
				button_int_left->update(x+41,y+58+23);
				button_int_right->update(x+41+63,y+58+23);
				button_dex_left->update(x+41,y+58+46);
				button_dex_right->update(x+41+63,y+58+46);
				button_agi_left->update(x+41,y+58+69);
				button_agi_right->update(x+41+63,y+58+69);
				button_vit_left->update(x+41,y+58+92);
				button_vit_right->update(x+41+63,y+58+92);
				button_luk_left->update(x+41,y+58+115);
				button_luk_right->update(x+41+63,y+58+115);

				if (button_str_right->fullClicked()) 
					networking::gameServer::stat_increase(STAT_STR,1);
				if (button_int_right->fullClicked()) 
					networking::gameServer::stat_increase(STAT_INT,1);
				if (button_dex_right->fullClicked()) 
					networking::gameServer::stat_increase(STAT_DEX,1);
				if (button_agi_right->fullClicked()) 
					networking::gameServer::stat_increase(STAT_AGI,1);
				if (button_vit_right->fullClicked()) 
					networking::gameServer::stat_increase(STAT_VIT,1);
				if (button_luk_right->fullClicked()) 
					networking::gameServer::stat_increase(STAT_LUK,1);


				if (closeButton->fullClicked()) {
					gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->closeGUIWindow_Character();
				}
				
			}
			bool entityGUICharacter::handleEvent(ALLEGRO_EVENT &e){
				dragHandleEvent(e);
				leftColumn.HandleEvent(e,x,y);
				rightColumn.HandleEvent(e,x,y);
				bottomRow.HandleEvent(e,x,y);
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x+7,y+34,65,27)) {
						selectTab(0);
					}
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x+74,y+34,65,27)) {
						selectTab(1);
					}
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x,y,240,274)) {
						return true; //We have handled the event, don't pass the event to anything below this window
					}
				}
				
				return false;
			}


			void entityGUICharacter::selectTab(int id) {
				selectedTab = id;
			}
	}
}

