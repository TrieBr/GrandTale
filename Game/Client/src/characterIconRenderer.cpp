#include "characterImageManager.h"
#include "characterIconRenderer.h"


namespace character {


characterIconRenderer::characterIconRenderer() : characterRenderer() {
	customizationState = NULL;
	icon = al_create_bitmap(30,30);
}

characterIconRenderer::~characterIconRenderer() {
	al_destroy_bitmap(icon);
}
characterIconRenderer::characterIconRenderer(characterCustomization *customization)  {
	customizationState = NULL;
	icon = al_create_bitmap(30,30);
	setCustomization(customization);
}

void characterIconRenderer::setCustomization(characterCustomization *customization) {
	this->characterRenderer::setCustomization(customization);

	/*
	
	if (customization!=customizationState) {
		customization->registerCallback(this);
		if (customizationState!=NULL) { customizationState->deregisterCallback(this); }
	}
	
	customizationState = customization;
	this->cache_body_body = characterImageManager::getSkinImage(customization->getRace(),customization->getSkinColor(),BODY_BODY); 

	setCustomization_Head(customization); //Pre render the head
	//Everything is pre rendered, so we don't need the cache anymore
	deferefenceCaches(); 
	*/
	
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(icon);
	al_clear_to_color(al_map_rgb(140,140,140));
	al_draw_scaled_bitmap(this->preRender_head->image,this->preRender_head->imgCenterX-10,this->preRender_head->imgCenterY-10,40,40,0,0,30,30,0);
	al_set_target_bitmap(old);
	
}

}
