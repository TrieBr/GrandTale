// ----------------------------------------------------------------------
// characterImageManager.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Manages and caches images for character rendering. When a character renderer is created or changed, it should request caches from the characterImageManager.
	When a charaterRenderer is changed or destroyed, the imageManager also needs to 
*/
// ------------------------------------------------------------------------


#include "gameEngine.h"
#include <map>

#ifndef _H_CHARIMAGEMANAGER
#define _H_CHARIMAGEMANAGER

namespace character {

	enum bodyPart {
		BODY_BODY,
		BODY_FACE,
		BODY_FACINGFOOT,
		BODY_HEAD,
		BODY_LEFTHAND,
		BODY_RIGHTHAND,
		BODY_CLOSEDHAND,
		BODY_STRAIGHTFOOT,
		BODY_EAR
	};

	class characterImageCache {
	public:
		ALLEGRO_BITMAP *image; //Image that has been loaded
		unsigned short imageOriginX; //X origin where it will be rotated, etc
		unsigned short imageOriginY; //Y origin where it will be rotated, etc.
		short imageRelativeX;
		short imageRelativeY;
		int usageCount; //When a renderer is using this cache, increment by one, when the renderer is done, decrement. If it's 0 that means nobody else is using it.
	};

	class characterImageManager { //Stores data for a character
	public:
		static void cleanUpUnusedCache(); //Cleans up the cache. Call this when a renderer changes or is destroyed so we can cleanup unused caches.
		static characterImageCache* getSkinImage(int raceID, int skinColorID, bodyPart part); //Returns the specified body part of thr specified skin.
		static characterImageCache* getHairImage(int hairID, int hairColor); //Returns the hair for the specified gender, hairtype and haircolor
		static characterImageCache* getEyesImage(int eyesID); //Returns the specified feyes image cache
		static characterImageCache* getMouthImage(int mouthID); //Returns the specified feyes image cache
		static characterImageCache* getFacialHairImage(int facialHairID, int facialHairColor); //Returns the specified face image cache
		//Gear..
		static characterImageCache* getGloveImage(int gloveID,bool fullGlove); //Returns the specified face image cache
		static characterImageCache* getHelmetImage(int helmetID); //Returns the specified face image cache
		static characterImageCache* getHeadgearLowerImage(int gearID); //Returns the specified face image cache
		static characterImageCache* getShoulderImage(int shoulder, bool front); //Returns the specified face image cache
		static characterImageCache* getBeltImage(int beltID); //Returns the specified face image cache
		static characterImageCache* getShoeImage(int shoeID, bool facing); //Returns the specified face image cache
		static characterImageCache* getPantsImage(int pantsID); //Returns the specified face image cache
		static characterImageCache* getShirtImage(int shirtID); //Returns the specified face image cache
		
		
	private:
		static std::map<std::string,characterImageCache*> cacheList; //List of caches that were created
		static characterImageCache* cacheImage(std::string imageName, std::string dataName); 

	};
}

#endif