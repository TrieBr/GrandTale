#include "item.h"

bool ItemContainer::SwapSlot(ItemContainer* container, int slot1, int slot2) {
	ItemContainerEntry buffer = container->Items[slot1];
	container->Items[slot1] = Items[slot2];
	Items[slot2] = buffer;
	return true;
}