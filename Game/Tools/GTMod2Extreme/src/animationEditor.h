


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <characterCustomization.h>
#include <characterRenderer.h>


#define scrubberLeft 50
#define scrubberWidth 700
#define scrubberTop 264
#define scrubberHeight 36

enum bodyPartEdit {
	HEAD,
	BODY,
	LEFTARM,
	RIGHTARM,
	LEFTFOOT,
	RIGHTFOOT
};

class animationEditor {
public:
	animationEditor();
	ALLEGRO_DISPLAY *display; //Display the the map editor
	void initialize(); 
	void update(double timeStep);
	void render();
	void createRenderer();
	ALLEGRO_EVENT_QUEUE *eventQueue;
private:
	character::characterRenderer	*renderer;
	std::vector<character::animationPoint> animationFrames;
	ALLEGRO_FONT* font;
	character::characterAnimationSequence *aSeq;
	int findAdjacentFrame(bool left, float pos);
	int frameEdit;
	bool draggingPart;
	float dragPartX, dragPartY;
	bodyPartEdit partEdit;
	character::animationPoint *editingPoint;
	bool draggingFramePosition;
	void ApplyChanges();
	void setFrameEdit(int frameNum);
	void SaveAnimation(std::string fName);
	void LoadAnimation(std::string fName);
};