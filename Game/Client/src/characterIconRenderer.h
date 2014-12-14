#include "characterRenderer.h"

namespace character {


class characterIconRenderer : public characterRenderer {
public:
	characterIconRenderer();
	~characterIconRenderer();
	characterIconRenderer(characterCustomization *customization);
	void setCustomization(characterCustomization *customization);
	ALLEGRO_BITMAP* getIcon() { return icon; }

private:
	ALLEGRO_BITMAP* icon;



};


}