


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <characterCustomization.h>
#include <characterImageManager.h>


//A Body parts
struct bodyPart {
	character::characterImageCache *bodyPartImage; //The image of the body part, loaded from the assets
};

struct alignmentPiece {
	short originX; //Rotation point/center point of equipment
	short originY; //Rotation point/center point of equipment
	short offsetX; //Ofset to the center of the body part
	short offsetY; //Offset to the center of the body part
};

class equipAligner {
public:
	equipAligner();
	ALLEGRO_DISPLAY *display; //Display the the map editor
	void initialize(); 
	void update(double timeStep);
	void render();
	void pickAlignmentPiece();
	void saveAlignmentPieceData();
	ALLEGRO_EVENT_QUEUE *eventQueue;
private:
	ALLEGRO_FONT* font;
	std::vector<bodyPart> availableBodyParts;
	int selectedBodyPart;
	ALLEGRO_BITMAP* aligningImage;
	alignmentPiece	aligningImageProperties;

	 character::characterImageCache* cache_head_eyes;
	 character::characterImageCache* cache_head_mouth;

	float imageAlignAlpha;
};