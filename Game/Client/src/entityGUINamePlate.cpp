
#include "entityGUINamePlate.h"
#include "myData.h"

namespace entities
{
	namespace GameGUI
	{

			entityGUINamePlate::entityGUINamePlate(){
				background = gameEngine::resources::graphics.loadBitmap(":gameGui:namePlate-bg.png");
				levelBackground = gameEngine::resources::graphics.loadBitmap(":gameGui:namePlate-bg-levelBG.png");
				barBackground = gameEngine::resources::graphics.loadBitmap(":gameGui:barBackground.png");
				healthBar = gameEngine::resources::graphics.loadBitmap(":gameGui:healthBar.png");
				manaBar = gameEngine::resources::graphics.loadBitmap(":gameGui:manaBar.png");
				nameFont = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",16);
			}
			void entityGUINamePlate::initialize(){

			}
			void entityGUINamePlate::cleanup(){

			}
			void entityGUINamePlate::render(float oX,float oY){
				al_draw_bitmap(background,x,y,0);
				al_draw_bitmap(levelBackground,x+5,y+5,0);

				al_draw_text(nameFont,al_map_rgb(44,17,20),x+131,y+1,ALLEGRO_ALIGN_CENTRE,"[No Guild]");
				al_draw_text(nameFont,al_map_rgb(44,17,20),x+131,y+20,ALLEGRO_ALIGN_CENTRE,myData::cData.getCharacterName().c_str());


				al_draw_bitmap(barBackground,x+245, y+6,0);
				al_draw_bitmap_region(healthBar,0,0,171*((float)myData::myCombatEntity.getCurrentHealth()/(float)myData::myCombatEntity.getTotalStat(STAT_HP)),19,x+245, y+6,0);
				al_draw_bitmap(barBackground,x+245, y+28,0);
				al_draw_bitmap_region(manaBar,0,0,171*((float)myData::myCombatEntity.getCurrentMana()/(float)myData::myCombatEntity.getTotalStat(STAT_HP)),19,x+245, y+28,0);


				// TODO: CACHE THIS ON A SURFACE
				
				al_draw_textf(nameFont,al_map_rgb(101,5,5),x+245+(171/2)+2, y+1,ALLEGRO_ALIGN_CENTRE,"HP: %d/%d", myData::myCombatEntity.getCurrentHealth(),myData::myCombatEntity.getTotalStat(STAT_HP));
				al_draw_textf(nameFont,al_map_rgb(101,5,5),x+245+(171/2)-2, y+1,ALLEGRO_ALIGN_CENTRE,"HP: %d/%d", myData::myCombatEntity.getCurrentHealth(),myData::myCombatEntity.getTotalStat(STAT_HP));
				al_draw_textf(nameFont,al_map_rgb(101,5,5),x+245+(171/2), y+2+1,ALLEGRO_ALIGN_CENTRE,"HP: %d/%d", myData::myCombatEntity.getCurrentHealth(),myData::myCombatEntity.getTotalStat(STAT_HP));
				al_draw_textf(nameFont,al_map_rgb(101,5,5),x+245+(171/2), y-2+1,ALLEGRO_ALIGN_CENTRE,"HP: %d/%d", myData::myCombatEntity.getCurrentHealth(),myData::myCombatEntity.getTotalStat(STAT_HP));
				al_draw_textf(nameFont,al_map_rgb(250,173,173),x+245+(171/2), y+1,ALLEGRO_ALIGN_CENTRE,"HP: %d/%d", myData::myCombatEntity.getCurrentHealth(),myData::myCombatEntity.getTotalStat(STAT_HP));

				al_draw_text(nameFont,al_map_rgb(26,49,58),x+245+(171/2)+2, y+23,ALLEGRO_ALIGN_CENTRE,"MANA: 100/100");
				al_draw_text(nameFont,al_map_rgb(26,49,58),x+245+(171/2)-2, y+23,ALLEGRO_ALIGN_CENTRE,"MANA: 100/100");
				al_draw_text(nameFont,al_map_rgb(26,49,58),x+245+(171/2), y+2+23,ALLEGRO_ALIGN_CENTRE,"MANA: 100/100");
				al_draw_text(nameFont,al_map_rgb(26,49,58),x+245+(171/2), y-2+23,ALLEGRO_ALIGN_CENTRE,"MANA: 100/100");
				al_draw_text(nameFont,al_map_rgb(173,204,218),x+245+(171/2), y+23,ALLEGRO_ALIGN_CENTRE,"MANA: 100/100");

			}
			void entityGUINamePlate::update(double _timeFactor){

			}
			bool entityGUINamePlate::handleEvent(ALLEGRO_EVENT &e){
				return false;
			}


	}

}

