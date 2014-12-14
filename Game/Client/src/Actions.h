
#include "gameEngine.h"
#include <item.h>
#include "iconManager.h"
#include "gameServer.h"
#include "globalData.h"
#include  "abstractSkillHandler.h"
#include "myData.h"
#include "itemTooltip.h"
/*
An "Action" is assigned to an action bar slot. An action provides an absatract way of getting cooldown, icon, status and more
*/
#ifndef _H_ACTIONS
#define _H_ACTIONS

enum SLOT_TYPE {
	S_UNDEFINED = 0,
	S_EMPTY = 1,
	S_GAMEACTON = 2,
	S_ITEMCONTAINER = 4,
	S_ITEMCONTAINER_REF = 8,
	S_EQUIPSLOT = 16,
	S_ACTIONBAR = 32,
	S_SKILL_REF = 64,
};

class Slot {
public:
	Slot();
	
	virtual ALLEGRO_BITMAP* GetIcon() { return NULL; }
	virtual bool			CanDrag() { return false; }
	virtual double			GetCoolDownTime(){ return 0; }
	virtual float			GetCoolDownPercent(){ return 0; }
	virtual tooltip*		GenerateTooltip() { return NULL; }
	virtual void			ExetuteAction() {}
	void					Render(float x, float y, bool noTint = false, bool highlight = false);
	ALLEGRO_BITMAP*			GetBorder() { return Border; }
	ALLEGRO_BITMAP*			GetExpandedBorder() { return ExpandedBorder; }
	ALLEGRO_BITMAP*			GetBackground() { return Background; }
	virtual bool			SlotDropped(Slot* src) { return false;} //A slot was dropped onto this one
	SLOT_TYPE type;
	int dropTypesAccepted; //Flags of types of slots that can be dropped on this slot
protected:
	ALLEGRO_BITMAP*			Border;	//Border for this slot	
	ALLEGRO_BITMAP*			Background; //Background for this slot
	ALLEGRO_BITMAP*			ExpandedBorder;

};

class SlotController {
public:
	static void			LoadStaticIcons();
	static void			FreeStaticIcons();
	static void			PickupSlot(Slot* slot);
	static Slot*		GetDraggingSlot();
	static bool			IsDraggingSlot();
	static void			CancelPickup();
	//Static icons
	static ALLEGRO_BITMAP* AC_Inventory;
	static ALLEGRO_BITMAP* AC_Social;
	static ALLEGRO_BITMAP* AC_Quest;
	static ALLEGRO_BITMAP* AC_Skills;
	static ALLEGRO_BITMAP* AC_Talents;
	static ALLEGRO_BITMAP* AC_Pvp;
	static ALLEGRO_BITMAP* AC_Menu;
	static ALLEGRO_BITMAP* EquipmentIcons[EQUIP_TYPE_COUNT];
	static ALLEGRO_BITMAP* EquipmentRing2Icon;
	//Borders and Backgrounds for slots
	static ALLEGRO_BITMAP*	SlotBackground;
	static ALLEGRO_BITMAP*  SlotBorder;
	static ALLEGRO_BITMAP*  SlotBorderExpanded;
private:
	static Slot* dragSlot; //Slot source that's currently being dragged
};

class SlotArray {
		public:
			SlotArray() { slotHover = -1; }
			std::vector<Slot*> slots;
			int slotHover; //index of the slot the mouse is hovering (-1 not hovering any)
			short rows; //Number of rows for the actions
			bool relative; //Are the cordinates relative to the main Bar?
			float x; //X position on screen
			float y; //Y Position on screen
			float colSpacing;
			float rowSpacing;
			bool editable;
			void HandleEvent(ALLEGRO_EVENT &e, float relativeX = 0, float relativeY = 0);
			void Render(float relativeX = 0, float relativeY = 0);		
};


class Slot_Empty: public Slot {
public:
	Slot_Empty() : Slot() { Border = SlotController::SlotBorder; Background = SlotController::SlotBackground; type = S_EMPTY;}
	ALLEGRO_BITMAP* GetIcon() { return NULL; }
	virtual void			ExetuteAction() {}
	void					Render(float x, float y, bool noTint = false);
};

class Slot_Action_Character : public Slot {
public:
	Slot_Action_Character(ALLEGRO_BITMAP* icon) { this->icon = icon; }
	ALLEGRO_BITMAP* GetIcon() { return icon; }
	void ExetuteAction();
private:
	ALLEGRO_BITMAP* icon;
};
class Slot_Action_Inventory : public Slot {
public:
	virtual ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Inventory; }
	void ExetuteAction();
};
class Slot_Action_Social : public Slot {
public:
	ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Social; }
};
class Slot_Action_Quest : public Slot {
public:
	ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Quest; }
};
class Slot_Action_Skills : public Slot {
public:
	ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Skills; }
	void ExetuteAction();
};
class Slot_Action_Talents : public Slot {
public:
	ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Talents; }
};
class Slot_Action_Pvp : public Slot {
public:
	ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Pvp; }
};
class Slot_Action_Menu : public Slot {
public:
	ALLEGRO_BITMAP* GetIcon() { return SlotController::AC_Menu; }
};


class Slot_EquipmentSlot: public Slot {
public:
	Slot_EquipmentSlot(equipType etype, ItemContainer *container, int slotNumber) : Slot() {
		_equipType = etype;
		referenceContainer = container;
		referenceSlot = slotNumber;
		this->dropTypesAccepted = S_ITEMCONTAINER;
		this->type = S_EQUIPSLOT;
	}
	ALLEGRO_BITMAP* GetIcon() { 
		if (referenceContainer->getItem(referenceSlot).itemID==-1) {
			return  SlotController::EquipmentIcons[_equipType];
		}
		return iconManager::fetchIcon(referenceContainer->getItem(referenceSlot).iconID);
	}
	tooltip* GenerateTooltip() { return referenceContainer->getItem(referenceSlot).itemID==-1 ?  NULL : new itemTooltip(referenceContainer->getItem(referenceSlot)); }
	bool CanDrag() {
		return (this->referenceContainer->getItem(this->referenceSlot).itemID!=-1);
	}
	bool SlotDropped(Slot* src);
	ItemContainer* referenceContainer;
	int				referenceSlot;
private:
	equipType _equipType;
	
};

class Slot_ItemContainerReference: public Slot {
public:
	Slot_ItemContainerReference(ItemContainer *container, int slotNumber) : Slot(){
		referenceContainer = container;
		referenceSlot = slotNumber;
		type = S_ITEMCONTAINER;
		dropTypesAccepted = S_ITEMCONTAINER | S_EQUIPSLOT;
	}
	ALLEGRO_BITMAP* GetIcon() {
		if (referenceContainer->getItem(referenceSlot).itemID==-1) {
			return NULL;
		}
		return iconManager::fetchIcon(referenceContainer->getItem(referenceSlot).iconID);
	}
	tooltip* GenerateTooltip() { return referenceContainer->getItem(referenceSlot).itemID==-1 ?  NULL : new itemTooltip(referenceContainer->getItem(referenceSlot)); }
	bool CanDrag() {
		return (this->referenceContainer->getItem(this->referenceSlot).itemID!=-1);
	}
	bool SlotDropped(Slot* src){ //A slot was dropped onto this one
		if(src->type==S_ITEMCONTAINER) {
			networking::gameServer::itemContainer_SwapSlots(this->referenceContainer,reinterpret_cast<Slot_ItemContainerReference*>(src)->referenceContainer,this->referenceSlot,reinterpret_cast<Slot_ItemContainerReference*>(src)->referenceSlot);
				return true;
		}
		if(src->type==S_EQUIPSLOT) {
			networking::gameServer::itemContainer_SwapSlots(this->referenceContainer,reinterpret_cast<Slot_EquipmentSlot*>(src)->referenceContainer,this->referenceSlot,reinterpret_cast<Slot_EquipmentSlot*>(src)->referenceSlot);
				return true;
		}
		return false;
	}
	ItemContainer* referenceContainer;
	int				referenceSlot;
private:
	
	
};

class Slot_SkillReference: public Slot {
	public:
	Slot_SkillReference(abstractSkillHandler* skillHandler) : Slot(){
		referenceSkill = skillHandler;
		type = S_SKILL_REF;
		dropTypesAccepted = 0;
	}
	ALLEGRO_BITMAP* GetIcon() {
		return iconManager::fetchIcon(globalData::getSkillManager()->GetSkill(referenceSkill->getSkillID()).iconID);
	}
	bool CanDrag() {
		return true; // TODO: Not implemented
	}
	bool SlotDropped(Slot* src){ //A slot was dropped onto this one
		return false;
	}
	void ExetuteAction() {
		myData::executeSkill(referenceSkill->getUniqueID());
	}
	abstractSkillHandler* referenceSkill;
private:

};

enum ACTIONBAR_REF {
	ABR_ITEMCONTAINER,//Referencing an item container
	ABR_SKILLCONTAINER
};

class Slot_ActionBar : public Slot {
public:
	Slot_ActionBar(){
		type = S_ACTIONBAR;
		dropTypesAccepted = S_ITEMCONTAINER |  S_SKILL_REF;
	}
	ALLEGRO_BITMAP* GetIcon() {
		if (refType==ABR_ITEMCONTAINER) {
			if (referenceItemContainer->getItem(referenceSlot).itemID==-1) {
				return NULL;
			}
			return iconManager::fetchIcon(referenceItemContainer->getItem(referenceSlot).iconID);
		}
		if (refType==ABR_SKILLCONTAINER) {
			return iconManager::fetchIcon(globalData::getSkillManager()->GetSkill(referenceSkill->getSkillID()).iconID);
		}
		return NULL;
	}
	bool SlotDropped(Slot* src){ //A slot was dropped onto this one
		if(src->type==S_ITEMCONTAINER) {
			refType = ABR_ITEMCONTAINER; //Item container reference was dropped on this slot
			referenceItemContainer = reinterpret_cast<Slot_ItemContainerReference*>(src)->referenceContainer;
			referenceSlot = reinterpret_cast<Slot_ItemContainerReference*>(src)->referenceSlot;
				return true;
		}
		if(src->type==S_SKILL_REF) { //We will eventually want to make a different way of referencing. Removing skill will fuck up the action bar references
			refType = ABR_SKILLCONTAINER; //skill container reference was dropped on this slot
			referenceSkill = reinterpret_cast<Slot_SkillReference*>(src)->referenceSkill;
				return true;
		}
		return false;
	}

	ACTIONBAR_REF refType;
	ItemContainer* referenceItemContainer;
	int referenceSlot;

	abstractSkillHandler* referenceSkill;
};


class Slot_ItemContainerItem : public Slot_ItemContainerReference {

};

#endif