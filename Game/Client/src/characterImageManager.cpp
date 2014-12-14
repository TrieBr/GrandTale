
#include "characterImageManager.h"
//#include "characterData.h"
//#include <RakString.h>
namespace character {
		std::map<std::string,characterImageCache*> characterImageManager::cacheList; //List of caches that were created

		void characterImageManager::cleanUpUnusedCache() { //Cleans up the cache. Call this when a renderer changes or is destroyed so we can cleanup unused caches.
			std::vector<std::string> removalKeys;
			for (std::map<std::string,characterImageCache*>::iterator it =characterImageManager::cacheList.begin(); it != characterImageManager::cacheList.end(); ++it) { //For each cached image
				if (it->second->usageCount<=0) {
					std::cout << "Deleting unused cache.." << std::endl;
					al_destroy_bitmap(it->second->image);
					removalKeys.push_back(it->first);
					delete it->second;
				}
			}
			for (unsigned int i=0; i<removalKeys.size(); i++) {
				characterImageManager::cacheList.erase(removalKeys[i]);
			}
		}

		characterImageCache* characterImageManager::cacheImage(std::string imageName, std::string dataName) {
			
			if (characterImageManager::cacheList.find(imageName)==characterImageManager::cacheList.end()) { //Cache was not previously generated, so generate it
				characterImageCache* newCache = new characterImageCache();
				//int oldFlags = al_get_new_bitmap_flags();
				//al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
				newCache->image  = al_load_bitmap_f(gameEngine::resources::graphics.openSubFile(imageName),".png"); //Load the image to cache
				//al_set_new_bitmap_flags(oldFlags);
				ALLEGRO_FILE * imageData = gameEngine::resources::graphics.openSubFile(dataName,false);
				al_fread(imageData,&newCache->imageOriginX,sizeof(unsigned short));
				 al_fread(imageData,&newCache->imageOriginY,sizeof(unsigned short));
				 al_fread(imageData,&newCache->imageRelativeX,sizeof(short));
				 al_fread(imageData,&newCache->imageRelativeY,sizeof(short));



				 al_fclose(imageData);
				newCache->usageCount = 1; //One person is now using it..
				cacheList[imageName] = newCache; //Add the cache to the map to.. cache it :p
				//std::cout << "Loaded image and cached it for first time.." << std::endl;
				return newCache;
			}else{ //Cache already exists, so return the existing one
				//std::cout << "Using previously cached image..." << std::endl;
				characterImageManager::cacheList[imageName]->usageCount ++; //A new renderer is using this cache
				return characterImageManager::cacheList[imageName];
			}
		}

		characterImageCache* characterImageManager::getSkinImage(int raceID, int skinColorID, bodyPart part) { //Returns the specified body part of thr specified skin.
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			switch (part) {
			case BODY_BODY:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:Body.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:Body.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_FACE:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:Face.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:Face.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_FACINGFOOT:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:FacingFoot.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:FacingFoot.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_HEAD:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:Head.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:Head.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_LEFTHAND:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:LeftHand.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:LeftHand.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_RIGHTHAND:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:RightHand.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:RightHand.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_CLOSEDHAND:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:HandClosed.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:HandClosed.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_STRAIGHTFOOT:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:StraightFoot.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:StraightFoot.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
			case BODY_EAR:
				n= sprintf(buffer,":character:race:%i:skinColor:%i:Ear.png",raceID,skinColorID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:race:%i:Ear.raw",raceID);
				dataPath = std::string(buffer,n);
				break;
				
			default: std::cout << "ERROR generating image cache for race. Unknown body part: " << part << std::endl;
			}
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getHairImage(int hairID, int hairColor) { //Returns the hair for the specified gender, hairtype and haircolor
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
				n= sprintf(buffer,":character:hair:%i:%i.png",hairID,hairColor);
				graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:hair:%i:calibration.raw",hairID);
				dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
	
		}

		characterImageCache* characterImageManager::getFacialHairImage(int facialHairID, int facialHairColor) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:facialHair:%i:%i.png",facialHairID,facialHairColor);
				graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:facialHair:%i:calibration.raw",facialHairID);
				dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getEyesImage(int eyesID) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:eyes:%i.png",eyesID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:eyes:%i.raw",eyesID);
			dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getMouthImage(int mouthID) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:mouth:%i.png",mouthID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:mouth:%i.raw",mouthID);
			dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getGloveImage(int gloveID, bool fullGlove) { //Returns the specified face image cache 
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			if (fullGlove) {
				n= sprintf(buffer,":character:equipment:%i-0.png",gloveID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:equipmentSpriteData:%i-0.raw",gloveID);
				dataPath = std::string(buffer,n);
			} else {
				n= sprintf(buffer,":character:equipment:%i-1.png",gloveID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:equipmentSpriteData:%i-1.raw",gloveID);
				dataPath = std::string(buffer,n);
			}
			return cacheImage(graphicPath,dataPath);
		}
		characterImageCache* characterImageManager::getHelmetImage(int helmetID) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:equipment:%i.png",helmetID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:equipmentSpriteData:%i.raw",helmetID);
			dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}
		characterImageCache* characterImageManager::getHeadgearLowerImage(int gearID){ //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:equipment:%i.png",gearID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:equipmentSpriteData:%i.raw",gearID);
			dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}
		characterImageCache* characterImageManager::getShoulderImage(int shoulder, bool front) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			if (front) {
				n= sprintf(buffer,":character:equipment:%i-1.png",shoulder);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:equipmentSpriteData:%i-1.raw",shoulder);
				dataPath = std::string(buffer,n);
			}else{
				n= sprintf(buffer,":character:equipment:%i-0.png",shoulder);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:equipmentSpriteData:%i-0.raw",shoulder);
				dataPath = std::string(buffer,n);
			}
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getBeltImage(int beltID) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:equipment:%i.png",beltID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:equipmentSpriteData:%i.raw",beltID);
			dataPath =std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getShoeImage(int shoeID, bool facing) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			if (facing) {
				n= sprintf(buffer,":character:equipment:%i-1.png",shoeID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:equipmentSpriteData:%i-1.raw",shoeID);
				dataPath = std::string(buffer,n);
			}else{
				n= sprintf(buffer,":character:equipment:%i-0.png",shoeID);
				graphicPath = std::string(buffer,n);
				n= sprintf(buffer,":character:equipmentSpriteData:%i-0.raw",shoeID);
				dataPath = std::string(buffer,n);
			}
			return cacheImage(graphicPath,dataPath);
		}
		
		characterImageCache* characterImageManager::getPantsImage(int pantsID) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:equipment:%i.png",pantsID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:equipmentSpriteData:%i.raw",pantsID);
			dataPath =std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}

		characterImageCache* characterImageManager::getShirtImage(int shirtID) { //Returns the specified face image cache
			std::string graphicPath;
			std::string dataPath;
			char buffer[256];
			int n;
			n= sprintf(buffer,":character:equipment:%i.png",shirtID);
			graphicPath = std::string(buffer,n);
			n= sprintf(buffer,":character:equipmentSpriteData:%i.raw",shirtID);
			dataPath = std::string(buffer,n);
			return cacheImage(graphicPath,dataPath);
		}

		
}