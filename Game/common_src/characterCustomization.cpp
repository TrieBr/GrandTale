

#include <characterCustomization.h>
namespace character {

		//Set the type of hair for the character
		void characterCustomization::setHairType(unsigned char type) {
			hairType = type;
		}
		//Get hair type
		unsigned char characterCustomization::getHairType() {
			return hairType;
		}
		//Set the hair color for the character
		void characterCustomization::setHairColor(unsigned char color) {
			hairColor = color;
		}
		//Get hair color
		unsigned char characterCustomization::getHairColor() {
			return hairColor;
		}
		//Set the eye type of the character
		void characterCustomization::setEyeType(unsigned char type) {
			eyeType = type;
		}
		//Get eye type
		unsigned char characterCustomization::getEyeType() {
			return eyeType;
		}
		//Set the type of mouth for the character
		void characterCustomization::setMouthType(unsigned char type) {
			mouthType = type;
		}
		//Get type of mouth
		unsigned char characterCustomization::getMouthType() {
			return mouthType;
		}
		//Set type of facial hair
		void characterCustomization::setFacialHairType(unsigned char type) {
			facialHairType = type;
		}
		//Get type of facial hair
		unsigned char characterCustomization::getFacialHairType() {
			return facialHairType;
		}
		//Set color of skin
		void characterCustomization::setSkinColor(unsigned char color) {
			skinColor = color;
		}
		//Get skin color
		unsigned char characterCustomization::getSkinColor() {
			return skinColor;
		}
		//Set race
		void characterCustomization::setRace(unsigned char raceID) {
			race = raceID;
		}
		//Get race
		unsigned char characterCustomization::getRace() {
			return race;
		}
		//Set gender of character
		void characterCustomization::setGender(character::genderType gender) {
			this->gender = gender;
		}
		//Get gender of character
		character::genderType characterCustomization::getGender() {
			return (character::genderType)gender;
		}
		//Set Weather offhand needs to be drawn infront of the hand
		void characterCustomization::setDrawOffHandInFront(bool inFront) {
			drawOffHandInFront = inFront;
		}
		//Get weather or not the offhand needs to be drawn in front of the hand
		bool characterCustomization::getDrawOffHandInFront() {
			return drawOffHandInFront;
		}
		void characterCustomization::setDrawMainHandInFront(bool inFront) {
			drawMainHandInFront = inFront;
		}
		//Get weather or not the mainhand needs to be drawn in front of the hand
		bool characterCustomization::getDrawMainHandInFront() {
			return drawMainHandInFront;
		}
		//Set Equipment for specified slot
		void characterCustomization::setEquipment(equipType type, int itemID) {
			equipment[type] = itemID;
		}
		//Get Equipment for specified slot
		int characterCustomization::getEquipment(equipType type) {
			return equipment[type];
		}


		//Set class
		void characterCustomization::setClass(classType newClass) {
			characterClass = newClass;
		}
		//Get class
		classType characterCustomization::getClass() {
			return (classType)characterClass;
		}

		void characterCustomization::setFaction(faction newFaction) {
			characterFaction = newFaction;
		}
		faction characterCustomization::getFaction(){
			return (faction)characterFaction;
		}
}