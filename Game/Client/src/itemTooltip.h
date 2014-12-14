#include "tooltip.h"
#include "item.h"
#include "gameEngine.h"
#include "itemCustomizationDataFetch.h"
#ifndef _H_ITEMTOOLTIP
#define _H_ITEMTOOLTIP

class itemTooltip : public tooltip {
public:
	itemTooltip(ItemContainerEntry p);
	virtual void initialize();
	virtual void cleanup();
	virtual void update(double deltaTime);
	virtual void render(float X, float Y);
private:
	float animationProgress;
	float textalpha;
	float maxWidth;
	float maxHeight;
	float width;
	float height;
	std::vector<std::string> wrappedEquipText;
	std::vector<std::string> wrappedActiveText;
	std::string classRestrictionString;
	bool textisWrapped;
	ItemContainerEntry item;
	ALLEGRO_FONT* font;
	ALLEGRO_FONT* fontTitle;
	itemCustomizationFetchHandle* customizationData;
};
#endif
