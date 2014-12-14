#include "entityGUIMainBar.h"
#include "myData.h"
#include "gameServer.h"

namespace entities
{
	namespace GameGUI
	{

			entityGUIMainBar::entityGUIMainBar(){
				expBackground = gameEngine::resources::graphics.loadBitmap(":gameGui:expBarBackground.png");	
				expBar = gameEngine::resources::graphics.loadBitmap(":gameGui:expBar.png");	
				actionBarBackground  = gameEngine::resources::graphics.loadBitmap(":gameGui:actionBarBackground.png");	
				actionBarSlotBackground = gameEngine::resources::graphics.loadBitmap(":gameGui:actionBarSlot.png");	
				actionBarSlotBorderBrown = gameEngine::resources::graphics.loadBitmap(":gameGui:actionBarBorderBrown.png");	
				actionBarSlotBorderRed = gameEngine::resources::graphics.loadBitmap(":gameGui:actionBarBorderRed.png");	
				
				 latencyGreen= gameEngine::resources::graphics.loadBitmap(":gameGui:latencyGreen.png");	
				 latencyYellow= gameEngine::resources::graphics.loadBitmap(":gameGui:latencyYellow.png");	
				  latencyRed= gameEngine::resources::graphics.loadBitmap(":gameGui:latencyRed.png");	

				font = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",16);
			}
			void entityGUIMainBar::initialize(){
				characterIcon = new character::characterIconRenderer(&myData::cData);

				 SlotArray mainActionBar;
				 for(int i=0; i<10; i++) { //Push 10 empty ("null") actions
					 mainActionBar.slots.push_back(new Slot_ActionBar());
				 }
				mainActionBar.rows = 1;
				mainActionBar.editable = false;
				mainActionBar.relative = true;
				mainActionBar.x = 10;
				mainActionBar.y = -63;
				mainActionBar.rowSpacing = 40;
				mainActionBar.colSpacing = 40;
				ActionBars.push_back(mainActionBar);

				 SlotArray gameActionBar;
					gameActionBar.slots.push_back(new Slot_Action_Character(characterIcon->getIcon()));
					gameActionBar.slots.push_back(new Slot_Action_Inventory());
					gameActionBar.slots.push_back(new Slot_Action_Social());
					gameActionBar.slots.push_back(new Slot_Action_Quest());
					gameActionBar.slots.push_back(new Slot_Action_Skills());
					gameActionBar.slots.push_back(new Slot_Action_Talents());
					gameActionBar.slots.push_back(new Slot_Action_Pvp());
				 gameActionBar.rows = 1;
				 gameActionBar.editable = false;
				 gameActionBar.relative = true;
				 gameActionBar.x = 426;
				 gameActionBar.y = -63;
				 gameActionBar.rowSpacing = 40;
				 gameActionBar.colSpacing = 44;
				 ActionBars.push_back(gameActionBar);


				  SlotArray gameActionBarMenu;
					gameActionBarMenu.slots.push_back(new Slot_Action_Menu());
				 gameActionBarMenu.rows = 1;
				 gameActionBarMenu.editable = false;
				 gameActionBarMenu.relative = true;
				 gameActionBarMenu.x = 755;
				 gameActionBarMenu.y = -63;
				 gameActionBarMenu.rowSpacing = 40;
				 gameActionBarMenu.colSpacing = 44;
				 ActionBars.push_back(gameActionBarMenu);
			}
			void entityGUIMainBar::cleanup(){
				delete characterIcon;
			}
			void entityGUIMainBar::render(float oX,float oY){

				al_draw_bitmap(actionBarBackground,x+1,y-70,0);
				al_draw_bitmap(expBackground,x+1,y-25,0);
				al_draw_bitmap_region(expBar,0,0,799,25,x+1,y-25,0);
				for (unsigned int a = 0; a<ActionBars.size(); a++) { //For each action bar
					ActionBars[a].Render(x,y);
				}

				if (networking::gameServer::getLatency()<=250) {
					al_draw_bitmap(latencyGreen,x+734,y-63,0);
				}
				else if (networking::gameServer::getLatency()<=400 && networking::gameServer::getLatency()>250) {
					al_draw_bitmap(latencyYellow,x+734,y-63,0);
				}
				else if (networking::gameServer::getLatency()>400) {
					al_draw_bitmap(latencyRed,x+734,y-63,0);
				}
				al_draw_text(font,al_map_rgb(88,58,10),x+400+2, y-27,ALLEGRO_ALIGN_CENTRE,"EXP: 1244/1244");
				al_draw_text(font,al_map_rgb(88,58,10),x+400-2, y-27,ALLEGRO_ALIGN_CENTRE,"EXP: 1244/1244");
				al_draw_text(font,al_map_rgb(88,58,10),x+400, y+2-27,ALLEGRO_ALIGN_CENTRE,"EXP: 1244/1244");
				al_draw_text(font,al_map_rgb(88,58,10),x+400, y-2-27,ALLEGRO_ALIGN_CENTRE,"EXP: 1244/1244");
				al_draw_text(font,al_map_rgb(224,228,174),x+400, y-27,ALLEGRO_ALIGN_CENTRE,"EXP: 1244/1244");

				
			}
			void entityGUIMainBar::update(double _timeFactor){

			}
			bool entityGUIMainBar::handleEvent(ALLEGRO_EVENT &e){
				for (short a = 0; a<ActionBars.size(); a++) { //For each action bar
					ActionBars[a].HandleEvent(e,x,y);
				}
				
				return false;
			}


	}

}

