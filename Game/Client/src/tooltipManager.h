#include "tooltip.h"
#include "gameEngine.h"


class tooltipManager {
public:
	static void initialize();
	static void cleanup();
	static void setTooltip(tooltip *p, bool deleteOnChange = true);
	static tooltip* getTooltip();
	static void renderTooltip(float X, float Y);
	static void updateTooltip(double delta);

private:
	static tooltip* currentTooltip;
	static bool     deleteOnChange; //Delete the tooltip object when changed


};