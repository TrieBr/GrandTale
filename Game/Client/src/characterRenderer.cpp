#include "characterImageManager.h"
#include "characterRenderer.h"

namespace character {

	characterRenderer::characterRenderer() {
		customizationState = NULL;
	}


	void characterRenderer::initialize(characterCustomization *customization) {
		 setCustomization(customization); //Set the customization and cache images...
	}

	characterRenderer::characterRenderer(characterCustomization *customization) {
		customizationState = NULL;
		initialize(customization);
	}

	void characterRenderer::setCustomization(characterCustomization *customization) { //Set a new customization for this renderer

			
			if (customization!=customizationState) {
				customization->registerCallback(this);
				if (customizationState!=NULL) { customizationState->deregisterCallback(this); }
			}
			customizationState = customization;
		//Load the images from the image cache manager.
		this->cache_body_body = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_BODY); //Cache the body (torso)
		

		this->cache_body_leftHand = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_LEFTHAND); //Cache the head 
		this->cache_body_rightHand = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_RIGHTHAND); //Cache the head 
		this->cache_body_handClosed = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_CLOSEDHAND); //Cache the head 
		this->cache_body_facingFoot = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_FACINGFOOT); //Cache the head 
		this->cache_body_straightFoot = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_STRAIGHTFOOT); //Cache the head 

		//Head stuff
		

		//The actual gear..

		int defaultClassGlove = defaultClassEquipment::GetDefaultID(EQUIP_GLOVE,customization->getGender(),customization->getClass(),customization->getFaction());
		if (defaultClassGlove>0)  { this->cache_glove_full = characterImageManager::getGloveImage(defaultClassGlove, true); this->cache_glove_fingers= characterImageManager::getGloveImage(defaultClassGlove, false); }
		else {
			if (customization->getEquipment(EQUIP_GLOVE)>0) {	this->cache_glove_full = characterImageManager::getGloveImage(customization->getEquipment(EQUIP_GLOVE),true); }else { this->cache_glove_full = NULL; }
			if (customization->getEquipment(EQUIP_GLOVE)>0) {	this->cache_glove_fingers = characterImageManager::getGloveImage(customization->getEquipment(EQUIP_GLOVE),false); }else { this->cache_glove_fingers = NULL; }
		}

		if (customization->getEquipment(EQUIP_HELMET)>0 ) {	this->cache_helmet = characterImageManager::getHelmetImage(customization->getEquipment(EQUIP_HELMET)); }else { this->cache_helmet = NULL; }
		
		

		if (customization->getEquipment(EQUIP_SHOULDER)>0) {this->cache_backShoulder = characterImageManager::getShoulderImage(customization->getEquipment(EQUIP_SHOULDER),false); }else { this->cache_backShoulder = NULL; }
		if (customization->getEquipment(EQUIP_SHOULDER)>0) {this->cache_frontShoulder = characterImageManager::getShoulderImage(customization->getEquipment(EQUIP_SHOULDER),true); }else { this->cache_frontShoulder = NULL; }
		if (customization->getEquipment(EQUIP_BELT)>0) {	this->cache_belt = characterImageManager::getBeltImage(customization->getEquipment(EQUIP_BELT)); }else { this->cache_belt = NULL; }


		int defaultClassShoe = defaultClassEquipment::GetDefaultID(EQUIP_SHOE,customization->getGender(),customization->getClass(),customization->getFaction());
		if (defaultClassShoe>0)  { this->cache_facingShoe = characterImageManager::getShoeImage(defaultClassShoe, true); this->cache_straightShoe = characterImageManager::getShoeImage(defaultClassShoe, false);}
		else {
			if (customization->getEquipment(EQUIP_SHOE)>0) {	this->cache_facingShoe = characterImageManager::getShoeImage(customization->getEquipment(EQUIP_SHOE),true); }else { this->cache_facingShoe = NULL; }
			if (customization->getEquipment(EQUIP_SHOE)>0) {	this->cache_straightShoe = characterImageManager::getShoeImage(customization->getEquipment(EQUIP_SHOE),false); }else { this->cache_straightShoe = NULL; }
		}


		if (customization->getEquipment(EQUIP_PANTS)>0) {	this->cache_pants = characterImageManager::getPantsImage(customization->getEquipment(EQUIP_PANTS)); }else { this->cache_pants = NULL; }

		int defaultClassShirt = defaultClassEquipment::GetDefaultID(EQUIP_SHIRT,customization->getGender(),customization->getClass(),customization->getFaction());
			if (defaultClassShirt>0)  { this->cache_shirt = characterImageManager::getShirtImage(defaultClassShirt); } 
		else { 
			if (customization->getEquipment(EQUIP_SHIRT)>0) { this->cache_shirt = characterImageManager::getShirtImage(customization->getEquipment(EQUIP_SHIRT)); }else { this->cache_shirt = NULL; }
		}

		if (customization->getEquipment(EQUIP_OFFHAND)>0) {	this->cache_offHand = characterImageManager::getShirtImage(customization->getEquipment(EQUIP_OFFHAND)); }else { this->cache_offHand = NULL; }
		if (customization->getEquipment(EQUIP_MAINHAND)>0) {	this->cache_mainHand = characterImageManager::getShirtImage(customization->getEquipment(EQUIP_MAINHAND)); }
		else if (customization->getEquipment(EQUIP_RANGED)>0) {	this->cache_mainHand = characterImageManager::getShirtImage(customization->getEquipment(EQUIP_RANGED)); }else { this->cache_mainHand = NULL; }

		//Pre render the body parts
		
		preRender_body = preRenderBody(customization); //Pre render the body
		preRender_leftHand = preRenderLeftHand(customization); //Pre render the left hand
		preRender_rightHand = preRenderRightHand(customization); //Pre render the right hand
		preRender_facingFoot  =preRenderFacingFoot(customization); //Pre render the facing food
		preRender_straightFoot= preRenderStraightFoot(customization); //PRe render the straight foot

		setCustomization_Head(customization); //Pre render the head
		//Everything is pre rendered, so we don't need the cache anymore
		deferefenceCaches(); 
		
	}

	void characterRenderer::setCustomization_Head(characterCustomization *customization) { //Set the customization for head 
		this->cache_body_head = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_HEAD); //Cache the head 
		if (raceProperties::requiresEar((RACE)customization->getRace())) {
			this->cache_body_ear = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_EAR); //Cache the head 
		}else{
			this->cache_body_ear = NULL;
		}
		if (customization->getHairType()>0) {
			this->cache_head_hair = characterImageManager::getHairImage(customization->getHairType(),customization->getHairColor());
		}else { this->cache_head_hair=NULL; }
		if (customization->getEyeType()>0) {
			cache_head_eyes = characterImageManager::getEyesImage(customization->getEyeType());
		}else { this->cache_head_eyes=NULL; }
		if (customization->getMouthType()>0) {
			cache_head_mouth = characterImageManager::getMouthImage(customization->getMouthType());
		}else { this->cache_head_mouth=NULL; }
		if (customization->getFacialHairType()>0) {
			this->cache_head_facialHair= characterImageManager::getFacialHairImage(customization->getFacialHairType(),customization->getHairColor());
		}else { this->cache_head_facialHair=NULL; }

		if (customization->getEquipment(EQUIP_HEAD_LOWER)>0) {	this->cache_head_lower = characterImageManager::getHeadgearLowerImage(customization->getEquipment(EQUIP_HEAD_LOWER)); }else { this->cache_head_lower = NULL; }

		preRender_head = preRenderHead(customization); //Pre render the head
	}

	void characterRenderer::deferefenceCaches() { //Will dereference the caches so the cache manager can clean them up..

		if (this->cache_body_body!=NULL) { this->cache_body_body->usageCount--; } //Subtract the number of users
		if (this->cache_body_ear!=NULL) { this->cache_body_ear->usageCount--; } //Subtract the number of users
		if (this->cache_body_head!=NULL) { this->cache_body_head->usageCount--; } //Subtract the number of users
		if (this->cache_body_leftHand!=NULL) { this->cache_body_leftHand->usageCount--; } //subtract the number of users
		if (this->cache_body_rightHand!=NULL) { this->cache_body_rightHand->usageCount--; } //Subtract the number of users 
		if (this->cache_body_handClosed!=NULL) { this->cache_body_handClosed->usageCount--; }; //Subtract usage count
		if (this->cache_body_facingFoot!=NULL) { this->cache_body_facingFoot->usageCount--; } //Subtract usage count
		if (this->cache_body_straightFoot!=NULL) { this->cache_body_straightFoot->usageCount--; } //Subtract usage count
		//Head stuff..
		if (this->cache_head_hair!=NULL) { this->cache_head_hair->usageCount--; } //Decrement the usage count
		if (this->cache_head_facialHair!=NULL) { this->cache_head_facialHair->usageCount--; }
		if (this->cache_head_eyes!=NULL) { this->cache_head_eyes->usageCount--; } //Decrease usage count
		if (this->cache_head_mouth!=NULL) { this->cache_head_mouth->usageCount--; } //Decrease usage count
		//The actual gear..
		if (this->cache_glove_full!=NULL) { this->cache_glove_full->usageCount--; }
		if (this->cache_glove_fingers!=NULL) { this->cache_glove_fingers->usageCount--; }
		if (this->cache_helmet!=NULL) { this->cache_helmet->usageCount--; }
		if (this->cache_backShoulder!=NULL) { this->cache_backShoulder->usageCount--; }
		if (this->cache_frontShoulder!=NULL) { this->cache_frontShoulder->usageCount--; }
		if (this->cache_belt!=NULL) { this->cache_belt->usageCount--; }
		if (this->cache_facingShoe!=NULL) { this->cache_facingShoe->usageCount--; }
		if (this->cache_straightShoe!=NULL) { this->cache_straightShoe->usageCount--; }
		if (this->cache_pants!=NULL) { this->cache_pants->usageCount--; }
		if (this->cache_shirt!=NULL) { this->cache_shirt->usageCount--; }
		characterImageManager::cleanUpUnusedCache(); //Clean up unused cache
	}
	void characterRenderer::cleanupPreRenderedParts() { //Cleans up all of the pre rendered parts in the preRenderedParts List
		for (unsigned int i=0; i<preRenderedParts.size(); i++) {
			al_destroy_bitmap(preRenderedParts[i]->image); //Delete the bitmap
			delete preRenderedParts[i]; //Delete the object
		}
		preRenderedParts.clear(); //Clear the list
	}

	characterRenderer::~characterRenderer() { //Destroy the renderer
		if (customizationState!=NULL) { customizationState->deregisterCallback(this); }
		cleanupPreRenderedParts();
	}


	preRenderedBodyPart* characterRenderer::preRenderHead(characterCustomization *customization) {
		short			centerX = 0;
		short			centerY = 0;
		short			minX = 0;
		short			maxX = 0;
		short			minY = 0;
		short			maxY = 0;
		ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();

		//Calculate the size of the bitmap
		calculateMinMax(cache_body_head, &centerX, &centerY, 0, 0, &minX, &maxX, &minY, &maxY) ;
		if (customization->getEyeType()>0) {
		calculateMinMax(cache_head_eyes,&centerX, &centerY, cache_head_eyes->imageRelativeX, cache_head_eyes->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		if (customization->getMouthType()>0) {
		calculateMinMax(cache_head_mouth,&centerX, &centerY, cache_head_mouth->imageRelativeX, cache_head_mouth->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		if (customization->getHairType()>0) {
		calculateMinMax(cache_head_hair,&centerX, &centerY, cache_head_hair->imageRelativeX, cache_head_hair->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		if (customization->getFacialHairType()>0) {
		calculateMinMax(cache_head_facialHair,&centerX, &centerY, cache_head_facialHair->imageRelativeX, cache_head_facialHair->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		if (raceProperties::requiresEar((RACE)customization->getRace())) {
		calculateMinMax(cache_body_ear,&centerX, &centerY, cache_body_ear->imageRelativeX, cache_body_ear->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		if (customization->getEquipment(EQUIP_HELMET)>0) {
		calculateMinMax(cache_helmet,&centerX, &centerY, cache_helmet->imageRelativeX, cache_helmet->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		if (this->cache_head_lower!=NULL) {
		calculateMinMax(this->cache_head_lower,&centerX, &centerY, this->cache_head_lower->imageRelativeX, this->cache_head_lower->imageRelativeY, &minX, &maxX, &minY, &maxY) ;
		}
		

		//Create the bitmap
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(abs(maxX-minX)+2,abs(maxY-minY)+2);
		centerX+=1;
		centerY+=1;
		
		al_set_target_bitmap(newBitmap); //Set the bitmap as the target
		al_draw_filled_rectangle(0,0,abs(maxX-minX)+2,abs(maxY-minY)+2,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(newBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta

		al_draw_bitmap(this->cache_body_head->image,centerX-this->cache_body_head->imageOriginX ,centerY-this->cache_body_head->imageOriginY,0); //Draw the head
		if (customization->getEyeType()>0) {
			al_draw_bitmap(this->cache_head_eyes->image,centerX+cache_head_eyes->imageRelativeX-cache_head_eyes->imageOriginX,centerY+cache_head_eyes->imageRelativeY-cache_head_eyes->imageOriginY,0); //Draw the face
		}
		if (customization->getMouthType()>0) {
			al_draw_bitmap(this->cache_head_mouth->image,centerX+cache_head_mouth->imageRelativeX-cache_head_mouth->imageOriginX,centerY+cache_head_mouth->imageRelativeY-cache_head_mouth->imageOriginY,0); //Draw the face
		}

		if (this->cache_head_lower!=NULL) {
			al_draw_bitmap(this->cache_head_lower->image,centerX+cache_head_lower->imageRelativeX-cache_head_lower->imageOriginX,centerY+cache_head_lower->imageRelativeY-cache_head_lower->imageOriginY,0); //Draw the hair
		}

		if (customization->getHairType()>0) {
			al_draw_bitmap(this->cache_head_hair->image,centerX+cache_head_hair->imageRelativeX-cache_head_hair->imageOriginX,centerY+cache_head_hair->imageRelativeY-cache_head_hair->imageOriginY,0); //Draw the hair
		}
		if (customization->getFacialHairType()>0) {
			al_draw_bitmap(this->cache_head_facialHair->image,centerX+cache_head_facialHair->imageRelativeX-cache_head_facialHair->imageOriginX,centerY+cache_head_facialHair->imageRelativeY-cache_head_facialHair->imageOriginY,0); //Draw the hair
		}
		if (raceProperties::requiresEar((RACE)customization->getRace())) {
			al_draw_bitmap(this->cache_body_ear->image,centerX+cache_body_ear->imageRelativeX-cache_body_ear->imageOriginX,centerY+cache_body_ear->imageRelativeY-cache_body_ear->imageOriginY,0); //Draw the hair
		}
		if (customization->getEquipment(EQUIP_HELMET)>0) {
			al_draw_bitmap(this->cache_helmet->image,centerX+cache_helmet->imageRelativeX-cache_helmet->imageOriginX,centerY+cache_helmet->imageRelativeY-cache_helmet->imageOriginY,0); //Draw the hair
		}
		al_set_target_bitmap(oldTarget); //Reset the target

		preRenderedBodyPart* preRender = new preRenderedBodyPart;
		preRender->image = newBitmap;
		preRender->imgCenterX = centerX;
		preRender->imgCenterY = centerY;
		preRenderedParts.push_back(preRender);
		return preRender;
	}


	preRenderedBodyPart* characterRenderer::preRenderBody(characterCustomization *customization) { 
		short			centerX = 0;
		short			centerY = 0;
		short			minX = 0;
		short			maxX = 0;
		short			minY = 0;
		short			maxY = 0;
		ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();

		//Calculate the size of the bitmap
		calculateMinMax(cache_body_body, &centerX, &centerY, 0, 0, &minX, &maxX, &minY, &maxY) ;
		if (customization->getEquipment(EQUIP_SHOULDER)>0) {
		calculateMinMax(cache_backShoulder,&centerX, &centerY, cache_backShoulder->imageRelativeX, cache_backShoulder->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}
		if (cache_shirt!=NULL) {
		calculateMinMax(cache_shirt,&centerX, &centerY, cache_shirt->imageRelativeX, cache_shirt->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}
		if (customization->getEquipment(EQUIP_PANTS)>0) {
		calculateMinMax(cache_pants,&centerX, &centerY, cache_pants->imageRelativeX, cache_pants->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}
		if (customization->getEquipment(EQUIP_BELT)>0) {
		calculateMinMax(cache_belt,&centerX, &centerY, cache_belt->imageRelativeX, cache_belt->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}
		if (customization->getEquipment(EQUIP_SHOULDER)>0) {
		calculateMinMax(cache_frontShoulder,&centerX, &centerY, cache_frontShoulder->imageRelativeX, cache_frontShoulder->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}

		//Create the bitmap
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(abs(maxX-minX)+2,abs(maxY-minY)+2);
		centerX+=1;
		centerY+=1;
		
		al_set_target_bitmap(newBitmap); //Set the bitmap as the target
		al_draw_filled_rectangle(0,0,abs(maxX-minX)+2,abs(maxY-minY)+2,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(newBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta
		if (customization->getEquipment(EQUIP_SHOULDER)>0) {
		al_draw_bitmap(this->cache_backShoulder->image,centerX+this->cache_backShoulder->imageRelativeX-this->cache_backShoulder->imageOriginX,centerY+this->cache_backShoulder->imageRelativeY-this->cache_backShoulder->imageOriginY,0); //Draw the shirt
		}
		al_draw_bitmap(this->cache_body_body->image,centerX-this->cache_body_body->imageOriginX ,centerY-this->cache_body_body->imageOriginY,0); //Draw the body
		
		if (customization->getEquipment(EQUIP_PANTS)>0) {
		al_draw_bitmap(this->cache_pants->image,centerX+this->cache_pants->imageRelativeX-this->cache_pants->imageOriginX,centerY+this->cache_pants->imageRelativeY-this->cache_pants->imageOriginY,0); //Draw the [ants
		}
		if (this->cache_shirt!=NULL) {
		al_draw_bitmap(this->cache_shirt->image,centerX+this->cache_shirt->imageRelativeX-this->cache_shirt->imageOriginX,centerY+this->cache_shirt->imageRelativeY-this->cache_shirt->imageOriginY,0); //Draw the shirt
		}
		if (customization->getEquipment(EQUIP_BELT)>0) {
		al_draw_bitmap(this->cache_belt->image,centerX+this->cache_belt->imageRelativeX-this->cache_belt->imageOriginX,centerY+this->cache_belt->imageRelativeY-this->cache_belt->imageOriginY,0); //Draw the belt
		}
		if (customization->getEquipment(EQUIP_SHOULDER)>0) {
		al_draw_bitmap(this->cache_frontShoulder->image,centerX+this->cache_frontShoulder->imageRelativeX-this->cache_frontShoulder->imageOriginX,centerY+this->cache_frontShoulder->imageRelativeY-this->cache_frontShoulder->imageOriginY,0); //Draw front shoulder
		}
		al_set_target_bitmap(oldTarget); //Reset the target

		preRenderedBodyPart* preRender = new preRenderedBodyPart;
		preRender->image = newBitmap;
		preRender->imgCenterX = centerX;
		preRender->imgCenterY = centerY;
		preRenderedParts.push_back(preRender);
		return preRender;
	}
	preRenderedBodyPart* characterRenderer::preRenderLeftHand(characterCustomization *customization) { //Offhand
		short			centerX = 0;
		short			centerY = 0;
		short			minX = 0;
		short			maxX = 0;
		short			minY = 0;
		short			maxY = 0;
		ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();

		//Calculate the size of the bitmap
		calculateMinMax(cache_body_leftHand, &centerX, &centerY, 0, 0, &minX, &maxX, &minY, &maxY) ;
		if (cache_glove_full!=NULL) {
		calculateMinMax(cache_glove_full,&centerX, &centerY, cache_glove_full->imageRelativeX, cache_glove_full->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}
		if ((customization->getEquipment(EQUIP_OFFHAND)>0))  {
			calculateMinMax(this->cache_offHand,&centerX, &centerY, cache_offHand->imageRelativeX, cache_offHand->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}

		//Create the bitmap
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(abs(maxX-minX)+2,abs(maxY-minY)+2);
		centerX+=1;
		centerY+=1;
		
		
		al_set_target_bitmap(newBitmap); //Set the bitmap as the target
		al_draw_filled_rectangle(0,0,abs(maxX-minX)+2,abs(maxY-minY)+2,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(newBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta


		if (!this->customizationState->getDrawOffHandInFront()) {
			if ((customization->getEquipment(EQUIP_OFFHAND)>0))  {
				al_draw_bitmap(this->cache_offHand->image,centerX+this->cache_offHand->imageRelativeX-this->cache_offHand->imageOriginX,centerY+this->cache_offHand->imageRelativeY-this->cache_offHand->imageOriginY,0); //Draw the shirt
			}
		}
		

		al_draw_bitmap(this->cache_body_leftHand->image,centerX-this->cache_body_leftHand->imageOriginX ,centerY-this->cache_body_leftHand->imageOriginY,0); //Draw the body

		if (this->cache_glove_full!=NULL) {
			al_draw_bitmap(this->cache_glove_full->image,centerX+this->cache_glove_full->imageRelativeX-this->cache_glove_full->imageOriginX,centerY+this->cache_glove_full->imageRelativeY-this->cache_glove_full->imageOriginY,0); //Draw the shirt
		}

		if (this->customizationState->getDrawOffHandInFront()) {
			if ((customization->getEquipment(EQUIP_OFFHAND)>0))  {
				al_draw_bitmap(this->cache_offHand->image,centerX+this->cache_offHand->imageRelativeX-this->cache_offHand->imageOriginX,centerY+this->cache_offHand->imageRelativeY-this->cache_offHand->imageOriginY,0); //Draw the shirt
			}
		}



		al_set_target_bitmap(oldTarget); //Reset the target

		preRenderedBodyPart* preRender = new preRenderedBodyPart;
		preRender->image = newBitmap;
		preRender->imgCenterX = centerX;
		preRender->imgCenterY = centerY;
		preRenderedParts.push_back(preRender);
		return preRender;
	}

	preRenderedBodyPart* characterRenderer::preRenderRightHand(characterCustomization *customization) { //Main hand
		short			centerX = 0;
		short			centerY = 0;
		short			minX = 0;
		short			maxX = 0;
		short			minY = 0;
		short			maxY = 0;
		ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();

		//Calculate the size of the bitmap
		calculateMinMax(cache_body_leftHand, &centerX, &centerY, 0, 0, &minX, &maxX, &minY, &maxY) ;
		//if (customization->getEquipment(EQUIP_GLOVE]>0) {
		//calculateMinMax(cache_glove_full,&centerX, &centerY, cache_shirt->imageRelativeX, cache_shirt->imageRelativeY, &minX, &maxX, &minY, &maxY);
		//}
		//Weapon here..
		if (cache_glove_fingers!=NULL) {
		calculateMinMax(cache_glove_fingers,&centerX, &centerY, cache_glove_fingers->imageRelativeX, cache_glove_fingers->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}

		if ((customization->getEquipment(EQUIP_MAINHAND)>0) || (customization->getEquipment(EQUIP_RANGED)>0))  {
			calculateMinMax(this->cache_mainHand,&centerX, &centerY, cache_mainHand->imageRelativeX, cache_mainHand->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}

		//Create the bitmap
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(abs(maxX-minX)+2,abs(maxY-minY)+2);
		centerX+=1;
		centerY+=1;
		al_set_target_bitmap(newBitmap); //Set the bitmap as the target
		al_draw_filled_rectangle(0,0,abs(maxX-minX)+2,abs(maxY-minY)+2,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(newBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta

		if (!this->customizationState->getDrawMainHandInFront()) {
			if ((customization->getEquipment(EQUIP_MAINHAND)>0) || (customization->getEquipment(EQUIP_RANGED)>0))  {
				al_draw_bitmap(this->cache_mainHand->image,centerX+this->cache_mainHand->imageRelativeX-this->cache_mainHand->imageOriginX,centerY+this->cache_mainHand->imageRelativeY-this->cache_mainHand->imageOriginY,0); //Draw the shirt
			}
		}

		al_draw_bitmap(this->cache_body_leftHand->image,centerX-this->cache_body_leftHand->imageOriginX ,centerY-this->cache_body_leftHand->imageOriginY,0); //Draw the body



		if (this->cache_glove_fingers!=NULL) {
		al_draw_bitmap(this->cache_glove_fingers->image,centerX+this->cache_glove_fingers->imageRelativeX-this->cache_glove_fingers->imageOriginX,centerY+this->cache_glove_fingers->imageRelativeY-this->cache_glove_fingers->imageOriginY,0); //Draw the shirt
		}

		
		al_draw_bitmap(this->cache_body_handClosed->image,centerX-this->cache_body_handClosed->imageOriginX ,centerY-this->cache_body_handClosed->imageOriginY,0); //Draw the body
		if (this->customizationState->getDrawMainHandInFront()) {
			if ((customization->getEquipment(EQUIP_MAINHAND)>0) || (customization->getEquipment(EQUIP_RANGED)>0))  {
				al_draw_bitmap(this->cache_mainHand->image,centerX+this->cache_mainHand->imageRelativeX-this->cache_mainHand->imageOriginX,centerY+this->cache_mainHand->imageRelativeY-this->cache_mainHand->imageOriginY,0); //Draw the shirt
			}
		}


		al_set_target_bitmap(oldTarget); //Reset the target

		preRenderedBodyPart* preRender = new preRenderedBodyPart;
		preRender->image = newBitmap;
		preRender->imgCenterX = centerX;
		preRender->imgCenterY = centerY;
		preRenderedParts.push_back(preRender);
		return preRender;
	}
	preRenderedBodyPart* characterRenderer::preRenderStraightFoot(characterCustomization *customization) {
		short			centerX = 0;
		short			centerY = 0;
		short			minX = 0;
		short			maxX = 0;
		short			minY = 0;
		short			maxY = 0;
		ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();

		//Calculate the size of the bitmap
		calculateMinMax(cache_body_straightFoot, &centerX, &centerY, 0, 0, &minX, &maxX, &minY, &maxY) ;
		if (cache_straightShoe!=NULL) {
			//calculateMinMax(cache_straightShoe,&centerX, &centerY, cache_straightShoe->imageRelativeX, cache_straightShoe->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}
		//Create the bitmap
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(abs(maxX-minX)+2,abs(maxY-minY)+2);
		centerX+=1;
		centerY+=1;

		al_set_target_bitmap(newBitmap); //Set the bitmap as the target
		al_draw_filled_rectangle(0,0,abs(maxX-minX)+2,abs(maxY-minY)+2,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(newBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta

		al_draw_bitmap(this->cache_body_straightFoot->image,centerX-this->cache_body_straightFoot->imageOriginX ,centerY-this->cache_body_straightFoot->imageOriginY,0); //Draw the body
		if (this->cache_straightShoe!=NULL) {
		al_draw_bitmap(this->cache_straightShoe->image,centerX+this->cache_straightShoe->imageRelativeX-this->cache_straightShoe->imageOriginX,centerY+this->cache_straightShoe->imageRelativeY-this->cache_straightShoe->imageOriginY,0); //Draw the shirt
		}


		al_set_target_bitmap(oldTarget); //Reset the target

		preRenderedBodyPart* preRender = new preRenderedBodyPart;
		preRender->image = newBitmap;
		preRender->imgCenterX = centerX;
		preRender->imgCenterY = centerY;
		preRenderedParts.push_back(preRender);
		return preRender;
	}
	preRenderedBodyPart* characterRenderer::preRenderFacingFoot(characterCustomization *customization) {
		short			centerX = 0;
		short			centerY = 0;
		short			minX = 0;
		short			maxX = 0;
		short			minY = 0;
		short			maxY = 0;
		ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();

		//Calculate the size of the bitmap
		calculateMinMax(cache_body_facingFoot, &centerX, &centerY, 0, 0, &minX, &maxX, &minY, &maxY) ;
		if (cache_facingShoe!=NULL) {
			//calculateMinMax(cache_facingShoe,&centerX, &centerY, cache_facingShoe->imageRelativeX, cache_facingShoe->imageRelativeY, &minX, &maxX, &minY, &maxY);
		}


		//Create the bitmap
		ALLEGRO_BITMAP* newBitmap = al_create_bitmap(abs(maxX-minX)+2,abs(maxY-minY)+2);
		centerX+=1;
		centerY+=1;

		al_set_target_bitmap(newBitmap); //Set the bitmap as the target
		al_draw_filled_rectangle(0,0,abs(maxX-minX)+2,abs(maxY-minY)+2,al_map_rgb(255,0,255)); //Draw magic magenta on it
		al_convert_mask_to_alpha(newBitmap,al_map_rgb(255,0,255)); //Key out the magic magenta

		al_draw_bitmap(this->cache_body_facingFoot->image,centerX-this->cache_body_facingFoot->imageOriginX ,centerY-this->cache_body_facingFoot->imageOriginY,0); //Draw the body
		if (this->cache_facingShoe!=NULL) {
		al_draw_bitmap(this->cache_facingShoe->image,centerX+this->cache_facingShoe->imageRelativeX-this->cache_facingShoe->imageOriginX,centerY+this->cache_facingShoe->imageRelativeY-this->cache_facingShoe->imageOriginY,0); //Draw the shirt
		}


		al_set_target_bitmap(oldTarget); //Reset the target

		preRenderedBodyPart* preRender = new preRenderedBodyPart;
		preRender->image = newBitmap;
		preRender->imgCenterX = centerX;
		preRender->imgCenterY = centerY;
		preRenderedParts.push_back(preRender);
		return preRender;
	}

	void characterRenderer::calculateMinMax(characterImageCache* img,short* centerX, short *centerY,  short drawPosX, short drawPosY, short *minX, short *maxX, short *minY, short *maxY) {
		

		if (drawPosX+(al_get_bitmap_width(img->image)-img->imageOriginX)>*maxX) {
			*maxX = drawPosX+(al_get_bitmap_width(img->image)-img->imageOriginX);
			//*centerX = abs(*maxX-*minX)/2;
		}

		if (drawPosX-img->imageOriginX<*minX) {
			*minX = drawPosX-img->imageOriginX;
			*centerX = abs(drawPosX-img->imageOriginX);
		}

		if (drawPosY+(al_get_bitmap_height(img->image)-img->imageOriginY)>*maxY) {
			*maxY = drawPosY+(al_get_bitmap_height(img->image)-img->imageOriginY);
			//*centerY = abs(*maxY-*minY)/2;
		}

		if (drawPosY-img->imageOriginY<*minY) {
			*minY = drawPosY-img->imageOriginY;
			*centerY = abs(drawPosY-img->imageOriginY);
		}

	}

	void characterRenderer::render(float x, float y, bool left) { //Render the character

		//this->render(x,y,animationPlayer.getCurrentFrame(),left);


	}

	void characterRenderer::render(float x, float y,character::animationPoint &point, bool left){
		int flip = left==true ? -1 : 1;

		character::animationPoint &currentFrameData = point; 

		al_draw_scaled_rotated_bitmap(preRender_rightHand->image,preRender_rightHand->imgCenterX,preRender_rightHand->imgCenterY,(x+(currentFrameData.rightHand.x*flip)),(y+currentFrameData.rightHand.y),flip,1,currentFrameData.rightHand.rotation*flip,0);

		if (currentFrameData.rightFoot.footState==STRAIGHT) {
			al_draw_scaled_rotated_bitmap(preRender_straightFoot->image,preRender_straightFoot->imgCenterX,preRender_straightFoot->imgCenterY,(x+(currentFrameData.rightFoot.x*flip)),(y+currentFrameData.rightFoot.y),flip,1,currentFrameData.rightFoot.rotation*flip,0);
		}else{
			al_draw_scaled_rotated_bitmap(preRender_facingFoot->image,preRender_facingFoot->imgCenterX,preRender_straightFoot->imgCenterY,(x+(currentFrameData.rightFoot.x*flip)),(y+currentFrameData.rightFoot.y),flip,1,currentFrameData.rightFoot.rotation*flip,0);
		}

		al_draw_scaled_rotated_bitmap(preRender_body->image,preRender_body->imgCenterX,preRender_body->imgCenterY,(x+(currentFrameData.body.x*flip)),(y+currentFrameData.body.y),flip,1,currentFrameData.body.rotation*flip,0);

		al_draw_scaled_rotated_bitmap(preRender_head->image,preRender_head->imgCenterX,preRender_head->imgCenterY,(x+(currentFrameData.Head.x*flip)),(y+currentFrameData.Head.y),flip,1,currentFrameData.Head.rotation*flip,0);

		

		if (currentFrameData.leftFoot.footState==STRAIGHT) {
			al_draw_scaled_rotated_bitmap(preRender_straightFoot->image,preRender_straightFoot->imgCenterX,preRender_straightFoot->imgCenterY,(x+(currentFrameData.leftFoot.x*flip)),(y+currentFrameData.leftFoot.y),flip,1,currentFrameData.leftFoot.rotation*flip,0);
		}else{
			al_draw_scaled_rotated_bitmap(preRender_facingFoot->image,preRender_facingFoot->imgCenterX,preRender_facingFoot->imgCenterY,(x+(currentFrameData.leftFoot.x*flip)),(y+currentFrameData.leftFoot.y),flip,1,currentFrameData.leftFoot.rotation*flip,0);
		}

		
		al_draw_scaled_rotated_bitmap(preRender_leftHand->image,preRender_leftHand->imgCenterX,preRender_leftHand->imgCenterY,(x+(currentFrameData.leftHand.x*flip)),(y+currentFrameData.leftHand.y),flip,1,currentFrameData.leftHand.rotation*flip,0);
	}

	void characterRenderer::setAnimation(characterAnimationSequence *sequence,animationPlayType playType, bool blend,float blendAmt) {
		this->animationPlayer.setAnimation(sequence,playType,blend,blendAmt); //Set the animation
	}


}