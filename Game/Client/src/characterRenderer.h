// ----------------------------------------------------------------------
// characterRenderer.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Used for rendering a character. The character must have an associated state (animation) and customisation state (for equipment graphics)
*/
// ------------------------------------------------------------------------


#include "characterCustomization.h"
#include "characterAnimation.h"
#include "raceProperties.h"
#include <allegro5/allegro.h>
#include <characterClass.h>

#ifndef _H_CHARACTERRENDERER
#define _H_CHARACTERRENDERER
namespace character {
class characterImageCache;
class characterImageManager;
}

namespace character {
	class preRenderedBodyPart { //Is a pre rendered body part with the correct skin and equipment already rendered to it.
	public:
		ALLEGRO_BITMAP* image;
		short imgCenterX;
		short imgCenterY;
	};
	struct xyPair {
		float x;
		float y;
	};
	class characterRenderer: public characterCustomizationChangedCallback {
	public:
		characterRenderer();
		~characterRenderer();
		characterRenderer(characterCustomization *customization);
		void initialize(characterCustomization *customization);
		virtual void setCustomization(characterCustomization *customization); //Sets a new customization. This will re cache and re render the image.
		void setCustomization_Head(characterCustomization *customization); //Set the customization for head 
		void setAnimation(characterAnimationSequence *sequence, animationPlayType playType, bool blend = false,float blendAmt = 0.1); //Sets the animation for the player
	
		void render(float x, float y, bool left = false); //Render the player
		void render(float x, float y,character::animationPoint &point, bool left = false);
		characterAnimation animationPlayer; //The animation the player is using
		virtual void customizationChanged() {
			setCustomization(customizationState);
		}

	protected:
		characterCustomization *customizationState; //Stage of viewable customization
		

		//Pre Rendering

		//Used for calculating the size of the bitmap
		void calculateMinMax(characterImageCache* img,short* centerX, short *centerY, short drawPosX, short drawPosY, short *minX, short *maxX, short *minY, short *maxY);

		//These functions are used to pre-render a body part.
		std::vector<preRenderedBodyPart*> preRenderedParts; //Stores a list of pre rendered parts, for garbage collection/cleaning them up
		void cleanupPreRenderedParts(); //Cleans up all of the pre rendered parts in the preRenderedParts List
		preRenderedBodyPart* preRenderHead(characterCustomization *customization);
		preRenderedBodyPart* preRenderBody(characterCustomization *customization);
		preRenderedBodyPart* preRenderLeftHand(characterCustomization *customization);
		preRenderedBodyPart* preRenderRightHand(characterCustomization *customization);
		preRenderedBodyPart* preRenderStraightFoot(characterCustomization *customization);
		preRenderedBodyPart* preRenderFacingFoot(characterCustomization *customization);

		//Pre rendered body parts
		preRenderedBodyPart* preRender_body;
		preRenderedBodyPart* preRender_head;
		preRenderedBodyPart* preRender_leftHand;
		preRenderedBodyPart* preRender_rightHand;
		preRenderedBodyPart* preRender_facingFoot;
		preRenderedBodyPart* preRender_straightFoot;

		void deferefenceCaches(); //Will dereference the caches so the cache manager can clean them up..
		//Image Caches..
		characterImageCache* cache_body_body;
		characterImageCache* cache_body_head;
		characterImageCache* cache_body_ear;
		characterImageCache* cache_body_leftHand;
		characterImageCache* cache_body_handClosed;
		characterImageCache* cache_body_rightHand;
		characterImageCache* cache_body_facingFoot;
		characterImageCache* cache_body_straightFoot;
		//Head equipment
		characterImageCache* cache_head_hair; 
		characterImageCache* cache_head_eyes; 
		characterImageCache* cache_head_mouth; 
		characterImageCache* cache_head_facialHair; 
		//Actual gear..
		characterImageCache* cache_glove_full;
		characterImageCache* cache_glove_fingers;
		characterImageCache* cache_helmet;
		characterImageCache* cache_head_lower;
		characterImageCache* cache_backShoulder;
		characterImageCache* cache_frontShoulder;
		characterImageCache* cache_belt;
		characterImageCache* cache_facingShoe;
		characterImageCache* cache_straightShoe;
		characterImageCache* cache_pants;
		characterImageCache* cache_shirt;
		characterImageCache* cache_mainHand;
		characterImageCache* cache_offHand;

	};

}

#endif 