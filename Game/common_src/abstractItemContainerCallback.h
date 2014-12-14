

#ifndef _ITEMCONTAINERCALLBACK
#define _ITEMCONTAINERCALLBACK
class ItemContainer;
class abstractItemContainerCallback {
public:
	virtual void SlotChanged(ItemContainer* containerSrc, int slotNum) = 0;
};

#endif