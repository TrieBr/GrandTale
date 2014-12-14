

#include "mapData.h"

#ifndef _H_PHYSICSCONTROLLER
#define _H_PHYSICSCONTROLLER

struct physicsProperties {
	float Acceleration;
	float Gravity;
	float airResistance;
	float Friction;
};

struct physicsState {

	float hVelocity;
	float vVelocity;
	bool onGround;

	bool left;
	bool right;
	bool up;
	bool down;

	float x;
	float y;
};

class physicsController {
public:
	physicsController(const physicsProperties& properties, mapData* newMapData);
	void setProperties(const physicsProperties& properties);
	~physicsController();
	void setState(physicsState* newState);
	void step(double _timeFactor);
	void setDimensions(int left, int top, int right, int bottom);
	void setDimensions(Rect &rectangle, Point &origin);
	void setMapData(mapData* newMapData);
	physicsState &getState();
	void hop(float power, bool requireOnGround); //Performs a jump/hop with the specified power

private:
	physicsState* currentState;
	physicsProperties properties;
	mapData* mData;

	//Dimentions of the "block"
	int dimensionLeft; //How far away the left side is
	int dimensionTop; //how far away the top is
	int dimensionRight; //how far away right is
	int dimensionBottom; //how far away bottom is

	//Temp variables used in collision checking. 
	lineSeg	boundingBoxBottom;
	lineSeg	boundingBoxLeft;
	lineSeg	boundingBoxTop;
	lineSeg	boundingBoxRight;
public:
	static physicsProperties getDefaultPlayerPhysics();

};

#endif