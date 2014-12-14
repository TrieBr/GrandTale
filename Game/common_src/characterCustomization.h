// ----------------------------------------------------------------------
// characterCustomization.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	Data for a characters customization including hair type, skin type, etc (basically anything that can be seen)
*/
// ------------------------------------------------------------------------


#ifndef _H_CHARCUSTOMIZATION
#define _H_CHARCUSTOMIZATION
#include <equipmentTypes.h>
#include <raceProperties.h>
#include <vector>
#include <gender.h>
#include <characterClass.h>

namespace RakNet {
class BitStream;
}

namespace character {

		class characterCustomizationChangedCallback {
		public:
			virtual void customizationChanged() = 0;
		};
	class characterCustomization {
	public:
		characterCustomization() {
			//Set default values...
			hairType = 1;
			hairColor = 1;
			eyeType = 1;
			mouthType = 2;
			facialHairType = 0;
			skinColor = 0;
			race = RACE_ELDER;
			gender = MALE;
			drawOffHandInFront = false;
			drawMainHandInFront = true;
			characterClass = CLASS_NOVICE;
			characterFaction = FACTION_GOOD;
			//Equipment types
			equipment[EQUIP_BELT] = 0;
			equipment[EQUIP_GLOVE] = 0;
			equipment[EQUIP_HELMET] = 0;
			equipment[EQUIP_PANTS] = 0;
			equipment[EQUIP_SHIRT] = 0;
			equipment[EQUIP_SHOE] = 0;
			equipment[EQUIP_SHOULDER] = 0;
			equipment[EQUIP_OFFHAND] = 0;
			equipment[EQUIP_RANGED] = 0;
			equipment[EQUIP_RING] = 0;
			equipment[EQUIP_RING2] = 0;
			equipment[EQUIP_MAINHAND] = 0;
			equipment[EQUIP_TRINKET] = 0;
			equipment[EQUIP_WEAPON] = 0;
			equipment[EQUIP_TWOHAND] = 0;
		}
	private:
		unsigned char hairType;
		unsigned char hairColor;
		unsigned char eyeType;
		unsigned char mouthType;
		unsigned char facialHairType;
		unsigned char skinColor;
		unsigned char race;
		unsigned char gender;
		unsigned char characterClass;
		unsigned char characterFaction;
		int equipment[EQUIP_TYPE_COUNT];
		bool drawOffHandInFront, drawMainHandInFront; //These can be removed and done clientside eventually..

		std::vector<characterCustomizationChangedCallback*> callbackList;

	public:
		void readCharacterCustomization(RakNet::BitStream &data);
		void writeCharacterCustomization(RakNet::BitStream &data);

		void registerCallback(characterCustomizationChangedCallback* pCallbackHandler) { callbackList.push_back(pCallbackHandler); }
		void deregisterCallback(characterCustomizationChangedCallback* pCallbackHandler) {
			for (unsigned int i=0; i< callbackList.size(); i++) {
				if (callbackList[i]==pCallbackHandler) {
					callbackList.erase(callbackList.begin()+i);
					break;
				}
			}
		}
		void disbatchCustomizationChange() {
			for (unsigned int i=0; i< callbackList.size(); i++) {
				callbackList[i]->customizationChanged();
			}
		}


		//Set the type of hair for the character
		void setHairType(unsigned char type);
		//Get hair type
		unsigned char getHairType();
		//Set the hair color for the character
		void setHairColor(unsigned char color);
		//Get hair color
		unsigned char getHairColor(); 
		//Set the eye type of the character
		void setEyeType(unsigned char type);
		//Get eye type
		unsigned char getEyeType();
		//Set the type of mouth for the character
		void setMouthType(unsigned char type);
		//Get type of mouth
		unsigned char getMouthType();
		//Set type of facial hair
		void setFacialHairType(unsigned char type);
		//Get type of facial hair
		unsigned char getFacialHairType();
		//Set color of skin
		void setSkinColor(unsigned char color);
		//Get skin color
		unsigned char getSkinColor();
		//Set race
		void setRace(unsigned char raceID);
		//Get race
		unsigned char getRace();
		//Set gender of character
		void setGender(character::genderType gender);
		//Get gender of character
		character::genderType getGender();
		//Set Weather offhand needs to be drawn infront of the hand
		void setDrawOffHandInFront(bool inFront);
		//Get weather or not the offhand needs to be drawn in front of the hand
		bool getDrawOffHandInFront();
		//Set Weather mainhand needs to be drawn infront of the hand
		void setDrawMainHandInFront(bool inFront);
		//Get weather or not the mainhand needs to be drawn in front of the hand
		bool getDrawMainHandInFront();
		//Set Equipment for specified slot
		void setEquipment(equipType type, int itemID);
		//Get Equipment for specified slot
		int getEquipment(equipType type);
		//Set class
		void setClass(classType newClass);
		//Get class
		classType getClass();
		//Set the faction
		void setFaction(faction newFaction);
		//Get the faction
		faction getFaction();
	};

}
#endif 