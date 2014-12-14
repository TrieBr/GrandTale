// ----------------------------------------------------------------------
// entityCharacterCreation.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:

*/
// ------------------------------------------------------------------------

#include "entityCharacterCreation.h"
#include "worldMainMenu.h"
#include "loginServer.h"
#include "characterAnimationSequenceManager.h"
#include <sstream>
#include "characterCustomization.h"
#define max(a,b) (a>b) ? a : b
#define min(a,b) (a<b) ? a : b

namespace entities
{
	namespace mainMenu
	{
			void entityCharacterCreation::initialize() {
				//Load all the images
				panelBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBGLargeCharCreate.png");
				panelBGCracks = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBGCracks.png");
				buttonLeftImage  = gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonLeft.png");
				buttonRightImage  = gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonRight.png");
				backButtonImage  = gameEngine::resources::graphics.loadBitmap(":loadScreen:backButton.png");
				createCharacterImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:buttonCreateCharacter.png");
				textboxBackground = gameEngine::resources::graphics.loadBitmap(":loadScreen:textbox180x26.png");

				raceElderImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:raceElder.png");
				raceNorelfImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:raceNorelf.png");
				raceOorkaImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:raceOorka.png");
				raceUndeadImage = gameEngine::resources::graphics.loadBitmap(":loadScreen:raceUndead.png");

				mainFont = gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);


				//Set position of the panel..
				x = 107;
				y= 279;

				
				backButton  = new GUI::widgets::button(backButtonImage,GUI::widgets::HOVER_HIGHLIGHT); //Create the back button

				//All the buttons for creating a character
				hairStyleLeft = new GUI::widgets::button(buttonLeftImage,GUI::widgets::HOVER_HIGHLIGHT);
				hairStyleRight = new GUI::widgets::button(buttonRightImage,GUI::widgets::HOVER_HIGHLIGHT);
				facialFeatureLeft = new GUI::widgets::button(buttonLeftImage,GUI::widgets::HOVER_HIGHLIGHT);
				facialFeatureRight = new GUI::widgets::button(buttonRightImage,GUI::widgets::HOVER_HIGHLIGHT);
				hairColorLeft = new GUI::widgets::button(buttonLeftImage,GUI::widgets::HOVER_HIGHLIGHT);
				hairColorRight = new GUI::widgets::button(buttonRightImage,GUI::widgets::HOVER_HIGHLIGHT);
				skinColorLeft = new GUI::widgets::button(buttonLeftImage,GUI::widgets::HOVER_HIGHLIGHT);
				skinColorRight = new GUI::widgets::button(buttonRightImage,GUI::widgets::HOVER_HIGHLIGHT);
				genderLeft = new GUI::widgets::button(buttonLeftImage,GUI::widgets::HOVER_HIGHLIGHT);
				genderRight = new GUI::widgets::button(buttonRightImage,GUI::widgets::HOVER_HIGHLIGHT);

				createButton = new GUI::widgets::button(createCharacterImage,GUI::widgets::HOVER_HIGHLIGHT);
				raceHuman = new GUI::widgets::button(backButtonImage,GUI::widgets::HOVER_HIGHLIGHT);

				raceElder = new GUI::widgets::button(raceElderImage,GUI::widgets::HOVER_HIGHLIGHT);
				raceNorelf = new GUI::widgets::button(raceNorelfImage,GUI::widgets::HOVER_HIGHLIGHT);
				raceOorka = new GUI::widgets::button(raceOorkaImage,GUI::widgets::HOVER_HIGHLIGHT);
				raceUndead = new GUI::widgets::button(raceUndeadImage,GUI::widgets::HOVER_HIGHLIGHT);

				class1 = new GUI::widgets::button(backButtonImage,GUI::widgets::HOVER_HIGHLIGHT);

				//Textbox for entering the name
				characterNameTextBox = new GUI::widgets::textbox(textboxBackground,mainFont,al_map_rgb(45,17,21));

				customization = new character::characterCustomization();
				
				characterRenderer = new character::characterRenderer(customization);
				characterRenderer->setAnimation(character::characterAnimationSequenceManager::getSequence(0),character::ANIMATION_LOOP);


			selectableHairStylesMale.push_back(0);
			selectableHairStylesMale.push_back(1);
			selectableHairStylesMale.push_back(2);
			selectableHairStylesMale.push_back(3);
			selectableHairStylesMale.push_back(4);
			//selectableHairStylesFemale;
			selectableFacialFeatureMale.push_back(0);
			selectableFacialFeatureMale.push_back(1);
			selectableFacialFeatureMale.push_back(2);
			selectableFacialFeatureMale.push_back(3);
			selectableFacialFeatureMale.push_back(4);

			//selectableFacialFeatureFemale;
			selectableHairColor.push_back(0);
			selectableHairColor.push_back(1);
			selectableHairColor.push_back(2);
			selectableHairColor.push_back(3);
			selectableHairColor.push_back(4);
			selectableHairColor.push_back(5);
			selectableHairColor.push_back(6);
			selectableHairColor.push_back(7);

			selectableskinColor.push_back(0);
			selectableskinColor.push_back(1);
			selectableskinColor.push_back(2);
			selectableskinColor.push_back(3);

			selectedHairMale = 0;
			selectedHairFemale = 0;
			selectedFacialFeatureMale = 0;
			selectedFacialFeatureFemale = 0;
			selectedSkinColor = 0;
			selectedHairColor = 0;
			selectedGender = character::MALE;
			selectedRace = RACE_ELDER;
			selectedEyes = 1;
			selectedMouth = 2;
			refreshCustomization();


			}
			void entityCharacterCreation::cleanup() {

				
				delete backButton;

				delete hairStyleLeft;
				delete hairStyleRight;
				delete facialFeatureLeft;
				delete facialFeatureRight;
				delete hairColorLeft;
				delete hairColorRight;
				delete skinColorLeft;
				delete skinColorRight;
				delete genderLeft;
				delete genderRight;
				delete createButton;
				delete raceHuman;
				delete class1;
				delete raceElder;
				delete raceNorelf;
				delete raceOorka;
				delete raceUndead;

				delete customization;
				delete characterRenderer;

				delete characterNameTextBox;
			}
			void entityCharacterCreation::render(float oX,float oY) {
				//al_draw_tinted_bitmap(panelBGCracks,al_map_rgba_f(1*cracksAlpha,1*cracksAlpha,1*cracksAlpha,cracksAlpha),x-56,y-48,0);
				al_draw_bitmap(panelBG,x,y,0);
				backButton->render(x+554,y+19,1);

				hairStyleLeft->render(x+20,y+51,1);
				hairStyleRight->render(x+174,y+51,1);
				facialFeatureLeft->render(x+20,y+85,1);
				facialFeatureRight->render(x+174,y+85,1);
				hairColorLeft->render(x+20,y+119,1);
				hairColorRight->render(x+174,y+119,1);
				skinColorLeft->render(x+20,y+153,1);
				skinColorRight->render(x+174,y+153,1);
				genderLeft->render(x+20,y+187,1);
				genderRight->render(x+174,y+187,1);
				createButton->render(x+204,y+224,1);

				raceElder->render(x+392,y+46,1);
				raceNorelf->render(x+439,y+46,1);
				raceOorka->render(x+486,y+46,1);
				raceUndead->render(x+534,y+46,1);

				//raceHuman->render(x+23,y+24,1);
				//class1->render(x+23,y+24,1);

				characterNameTextBox->render(x+204,y+190);
				characterRenderer->render(x+297,y+150);
				std::stringstream stringFormat;


		
		


				stringFormat.str("");
				if (selectedGender==character::MALE) {
					stringFormat << "Hair Style: " << selectedHairMale;
				}else{
					stringFormat << "Hair Style: " << selectedFacialFeatureFemale;
				}
				al_draw_text(mainFont,al_map_rgb(45,17,21),x+103,y+48,ALLEGRO_ALIGN_CENTRE,stringFormat.str().c_str());
				

				stringFormat.str("");
				if (selectedGender==character::MALE) {
					stringFormat << "Facial Feature: " << selectedFacialFeatureMale;
				}else{
					stringFormat << "Facial Feature: " << selectedFacialFeatureFemale;
				}
				al_draw_text(mainFont,al_map_rgb(45,17,21),x+103,y+82,ALLEGRO_ALIGN_CENTRE,stringFormat.str().c_str());

				stringFormat.str("");
				stringFormat << "Hair Color: " << selectedHairColor;
				al_draw_text(mainFont,al_map_rgb(45,17,21),x+103,y+116,ALLEGRO_ALIGN_CENTRE,stringFormat.str().c_str());

				stringFormat.str("");
				stringFormat << "Skin Color: " << selectedSkinColor;
				al_draw_text(mainFont,al_map_rgb(45,17,21),x+103,y+150,ALLEGRO_ALIGN_CENTRE,stringFormat.str().c_str());

				stringFormat.str("");
				if (selectedGender==character::MALE) {
					stringFormat << "Gender: " << "Male";
				}else{
					stringFormat << "Gender: " << "Female";
				}
				al_draw_text(mainFont,al_map_rgb(45,17,21),x+103,y+184,ALLEGRO_ALIGN_CENTRE,stringFormat.str().c_str());

			}

			void entityCharacterCreation::update(double _timeFactor) {

				if (this->panelTransition.isTransitioning) {
					this->panelTransition.update(&x,&cracksAlpha, _timeFactor);
				}
				backButton ->update(x+554,y+19);
				if (backButton->fullClicked()) {
					this->getParentWorld<worlds::worldMainMenu>()->charCreateToCharSelect(); //Go back to character select
				}


				hairStyleLeft->update(x+20,y+51);
				if (hairStyleLeft->fullClicked()) {
					if (selectedGender==character::MALE) {
						selectedHairMale = max(0,(selectedHairMale-1));
					}else{
						selectedHairFemale = max(0,(selectedHairFemale-1));
					}
					refreshCustomization();
				}

				hairStyleRight->update(x+174,y+51);
				if (hairStyleRight->fullClicked()) {
					if (selectedGender==character::MALE) {
						selectedHairMale = min(selectableHairStylesMale.size()-1,(selectedHairMale+1));
					}else{
						selectedHairFemale = min(selectableHairStylesFemale.size()-1,(selectedHairFemale+1));
					}
					refreshCustomization();
				}

				facialFeatureLeft->update(x+20,y+85);
				if (facialFeatureLeft->fullClicked()) {
					if (selectedGender==character::MALE) {
						selectedFacialFeatureMale = max(0,(selectedFacialFeatureMale-1));
					}else{
						selectedFacialFeatureFemale = max(0,(selectedFacialFeatureFemale-1));
					}
					refreshCustomization();
				}

				facialFeatureRight->update(x+174,y+85);
				if (facialFeatureRight->fullClicked()) {
					if (selectedGender==character::MALE) {
						selectedFacialFeatureMale = min(selectableFacialFeatureMale.size()-1,(selectedFacialFeatureMale+1));
					}else{
						selectedFacialFeatureFemale = min(selectableFacialFeatureFemale.size()-1,(selectedFacialFeatureFemale+1));
					}
					refreshCustomization();
				}
				hairColorLeft->update(x+20,y+119);
				if (hairColorLeft->fullClicked()) {
						selectedHairColor = max(0,(selectedHairColor-1));
					refreshCustomization();
				}
				hairColorRight->update(x+174,y+119);
				if (hairColorRight->fullClicked()) {
						selectedHairColor = min(selectableHairColor.size()-1,(selectedHairColor+1));
					refreshCustomization();
				}

				skinColorLeft->update(x+20,y+153);
				if (skinColorLeft->fullClicked()) {
						selectedSkinColor = max(0,(selectedSkinColor-1));
					refreshCustomization();
				}
				skinColorRight->update(x+174,y+153);
				if (skinColorRight->fullClicked()) {
						selectedSkinColor = min(selectableskinColor.size()-1,(selectedSkinColor+1));
					refreshCustomization();
				}

				genderLeft->update(x+20,y+187);
				if (genderLeft->fullClicked()) {
					selectedGender = character::MALE;
					refreshCustomization();
				}
				genderRight->update(x+174,y+187);
				if (genderRight->fullClicked()) {
					//selectedGender = character::FEMALE;
					refreshCustomization();
				}


				
				createButton->update(x+204,y+224);
				if (createButton->fullClicked()) {
					networking::loginServer::createCharacter(customization,this->characterNameTextBox->Text);
					this->getParentWorld<worlds::worldMainMenu>()->charCreateToCharSelect();
				}

				raceElder->update(x+392,y+46);
				if (raceElder->fullClicked()) {
					selectedRace = RACE_ELDER;
					selectedEyes = 1;
					selectedMouth = 2;
					refreshCustomization();
				}
				raceNorelf->update(x+439,y+46);
				if (raceNorelf->fullClicked()) {
					selectedRace = RACE_NORELF;
					selectedEyes = 2;
					selectedMouth = 2;
					refreshCustomization();
				}
				raceOorka->update(x+486,y+46);
				if (raceOorka->fullClicked()) {
					selectedRace = RACE_OORKA;
					selectedEyes = 3;
					selectedMouth = 1;
					refreshCustomization();
				}
				raceUndead->update(x+534,y+46);
				if (raceUndead->fullClicked()) {
					selectedRace = RACE_UNDEAD;
					selectedEyes = 4;
					selectedMouth = 0;
					refreshCustomization();
				}


				

				//raceHuman->update(x+23,y+24);
				//class1->update(x+23,y+24);

				characterNameTextBox->update();

				characterRenderer->animationPlayer.stepAnimation(_timeFactor);

			}

			bool entityCharacterCreation::handleEvent(ALLEGRO_EVENT &e) { 

				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{//Mouse was pressed
					if (e.mouse.button==1)
					{//Left clicked
						if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+204,y+190,x+204+180,y+190+26)) {//Mouse in region of username Box
							characterNameTextBox->focus(true);
						}else{
							characterNameTextBox->focus(false);
						}
					}

				}
				return true;
			}

			void entityCharacterCreation::refreshCustomization() {
				delete customization;
				customization = new character::characterCustomization();
				customization->setEquipment(EQUIP_BELT,8);
				customization->setEquipment(EQUIP_GLOVE,9);
				customization->setEquipment(EQUIP_HELMET,0);
				customization->setEquipment(EQUIP_PANTS,13);
				customization->setEquipment(EQUIP_SHIRT,10);
				customization->setEquipment(EQUIP_SHOE,11);
				customization->setEquipment(EQUIP_SHOULDER,12);

				customization->setGender((character::genderType)selectedGender);
				if (selectedGender==character::MALE) {
					customization->setFacialHairType(selectableFacialFeatureMale[selectedFacialFeatureMale]);
				}else{
					customization->setFacialHairType(selectableFacialFeatureFemale[selectedFacialFeatureFemale]);
				}

				if (selectedGender==character::MALE) {
					customization->setHairType(selectableHairStylesMale[selectedHairMale]);
				}else{
					customization->setHairType(selectableHairStylesFemale[selectedHairFemale]);
				}
				customization->setSkinColor(selectableskinColor[selectedSkinColor]);
				customization->setHairColor(selectableHairColor[selectedHairColor]);
				customization->setRace(selectedRace);
				customization->setEyeType(selectedEyes);
				customization->setMouthType(selectedMouth);
				characterRenderer->setCustomization(customization);
			}
	}

}