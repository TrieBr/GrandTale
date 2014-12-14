#include "itemTooltip.h"
#include "gameEngine.h"
#include "globalData.h"
#include "globalFunctions.h"
#include <characterClass.h>

//If item customization data has the specified stat, draw it
#define draw_stat(stat, name) if (customizationData->getCustomizationData().getBaseStat(stat)!=0 || customizationData->getCustomizationData().getBonusStat(stat)!=0) { \
								yy+=9; \
								al_draw_textf(font,al_map_rgba(textalpha*255,textalpha*153,textalpha*0,textalpha*255),X-width+3,Y+2+yy,0,"%s: %i (+%i)",name,customizationData->getCustomizationData().getBaseStat(stat),customizationData->getCustomizationData().getBonusStat(stat)); \
								}
#define classCanEquip(class) (globalData::getItemManager()->GetItem(item.itemID).classRestrictions & class) == class
itemTooltip::itemTooltip(ItemContainerEntry p) {
	item = p;
}
void itemTooltip::initialize() {
	animationProgress = 0;
	maxWidth = 150;
	maxHeight = 200;
	width = 0;
	height = 0;
	textalpha = 0;
	textisWrapped = false;
	customizationData = itemCusomizationDataFetch::fetchItemCustomization(item.customizationID);
	font = gameEngine::resources::fonts.loadFont(":gameGui:smallPixel.ttf",8);
	fontTitle = gameEngine::resources::fonts.loadFont(":gameGui:smallPixel.ttf",12);
	unsigned int omg = globalData::getItemManager()->GetItem(item.itemID).classRestrictions & character::CLASS_ALL;
	if ((globalData::getItemManager()->GetItem(item.itemID).classRestrictions & character::CLASS_ALL) == character::CLASS_ALL) {
		classRestrictionString = "All Classes";
	}else{
		classRestrictionString = "Classes: ";
		if (classCanEquip(character::CLASS_NOVICE)) classRestrictionString.append("Novice ");
		if (classCanEquip(character::CLASS_MAGE)) classRestrictionString.append("Mage ");
		if (classCanEquip(character::CLASS_HUNTER)) classRestrictionString.append("Hunter ");
	}
	

}
void itemTooltip::cleanup() {
	//al_destroy_font(fontTitle);
	//al_destroy_font(font);
	delete customizationData;
}
void itemTooltip::update(double deltaTime) {
	if (animationProgress<1) {
		animationProgress += 0.15*deltaTime;
	}else { 
		animationProgress = 1;
		if (textalpha<1) {
			textalpha += 0.06*deltaTime;
		}else {
			textalpha = 1;
		}
	}
	width = maxWidth*animationProgress;
	height = maxHeight*animationProgress;

}
void itemTooltip::render(float X, float Y) {
	
	al_draw_filled_rectangle(X-width,Y,X,Y+height,al_map_rgba(0,0,0,210));
	al_draw_rectangle(X-width,Y,X,Y+height,al_map_rgb(255,255,255),2);
	float yy = 0;
	al_draw_text(fontTitle,al_map_rgba(textalpha*163,textalpha*52,textalpha*237,textalpha*255),X-width+3,Y+2,0,globalData::getItemManager()->GetItem(item.itemID).itemName.c_str());
	yy+=14;
	al_draw_text(font,al_map_rgba(textalpha*255,textalpha*255,textalpha*255,textalpha*255),X-width+3,Y+2+yy,0,classRestrictionString.c_str());



	if (customizationData->getStatus()==IC_FETCH_DONE) {
		yy+=9;
		al_draw_textf(font,al_map_rgba(textalpha*255,textalpha*255,textalpha*255,textalpha*255),X-width+3,Y+2+yy,0,"Weapon Damage: %i",customizationData->getCustomizationData().getWeaponDamage());
		 draw_stat(STAT_STR, "Strength");
		 draw_stat(STAT_DEX, "Dexterity");
		 draw_stat(STAT_AGI, "Agility");
		 draw_stat(STAT_VIT, "Vitality");
		 draw_stat(STAT_LUK, "Luck");
		 draw_stat(STAT_INT, "Intellect");
		 draw_stat(STAT_ATK, "Attack");
		 draw_stat(STAT_MAGIC_ATK, "Magic Attack");
		 draw_stat(STAT_DEF, "Defence");
		 draw_stat(STAT_MAGIC_DEF, "Magic Defence");

		 

		 if (!textisWrapped) {
				gameEngine::globalFunctions::preWrapText(font,145,this->wrappedEquipText,std::string("Equip: ").append(customizationData->getCustomizationData().getEquipText()));
				gameEngine::globalFunctions::preWrapText(font,145,this->wrappedActiveText,std::string("Active: ").append(customizationData->getCustomizationData().getActiveText()));

			 
			
			 textisWrapped = true;


		 }

		 if (customizationData->getCustomizationData().hasEquipEffect()) {
			 for (unsigned int i=0; i<wrappedEquipText.size(); i++) {
				 yy+=9; 
					al_draw_textf(font,al_map_rgba(textalpha*102,textalpha*204,textalpha*0,textalpha*255),X-width+3,Y+2+yy,0,wrappedEquipText[i].c_str()); 
			 }
			  for (unsigned int i=0; i<wrappedActiveText.size(); i++) {
				 yy+=9; 
					al_draw_textf(font,al_map_rgba(textalpha*102,textalpha*204,textalpha*0,textalpha*255),X-width+3,Y+2+yy,0,wrappedActiveText[i].c_str()); 
			 }
			 
		 }

	}


}