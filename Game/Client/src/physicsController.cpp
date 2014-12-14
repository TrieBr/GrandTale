

#include "physicsController.h"
#include <cmath>
#include "collisionCheck.h"


physicsController::physicsController(const physicsProperties& properties, mapData* newMapData) {
	currentState = new physicsState();
	currentState->vVelocity = 0;
	currentState->hVelocity = 0;
	currentState->left = false;
	currentState->right = false;
	currentState->up = false;
	currentState->down = false;
	currentState->x = 0;
	currentState->y = 0;

	this->mData = newMapData;
	setProperties(properties);
}

physicsController::~physicsController() {

	if (currentState!=0x00) {
		delete currentState;
	}
}

void physicsController::setProperties(const physicsProperties& properties) {
	this->properties = properties;
}

void physicsController::setState(physicsState* newState) {
		delete currentState; //Delete the old state
	currentState = newState;
}

void physicsController::setMapData(mapData* newMapData){
	mData = newMapData;
}

void physicsController::step(double _timeFactor) {

	//Increase velocity from Gravity.
	this->currentState->vVelocity += this->properties.Gravity*_timeFactor;
	if (this->currentState->left) {
	this->currentState->hVelocity -=this->properties.Acceleration*_timeFactor;
	}
	if (this->currentState->right) {
	this->currentState->hVelocity += this->properties.Acceleration*_timeFactor;
	}

	this->currentState->hVelocity /= 1+0.8*_timeFactor;
	
	static double verticalPx, horizontalPx; //How many pixels do we want to move?
	verticalPx = this->currentState->vVelocity*_timeFactor; //Distance we want to move up or down 
	horizontalPx = this->currentState->hVelocity*_timeFactor; //Distance we want to move left or right

	boundingBoxBottom.p1.x = currentState->x-dimensionLeft;
	boundingBoxBottom.p1.y = ceil(currentState->y+dimensionBottom);
	boundingBoxBottom.p2.x = currentState->x+dimensionRight;
	boundingBoxBottom.p2.y = ceil(currentState->y+dimensionBottom);

	boundingBoxTop.p1.x = currentState->x-dimensionLeft;
	boundingBoxTop.p1.y = floor(currentState->y-dimensionTop);
	boundingBoxTop.p2.x = currentState->x+dimensionRight;
	boundingBoxTop.p2.y = floor(currentState->y-dimensionTop);

	boundingBoxRight.p1.x = ceil(currentState->x+dimensionRight);
	boundingBoxRight.p1.y = currentState->y-dimensionTop;
	boundingBoxRight.p2.x = ceil(currentState->x+dimensionRight);
	boundingBoxRight.p2.y = currentState->y+dimensionBottom;

	boundingBoxLeft.p1.x = floor(currentState->x-dimensionLeft);
	boundingBoxLeft.p1.y = currentState->y-dimensionTop;
	boundingBoxLeft.p2.x = floor(currentState->x-dimensionLeft);
	boundingBoxLeft.p2.y = currentState->y+dimensionBottom;

	static collisionLine* cBuffer;
	static bool vCollision;
	static bool hCollision;

	vCollision = false;
	hCollision = false;
		for (collisionLineListNode* i = this->mData->getRootCollisionLine(); i!=NULL; i=i->next) {
			cBuffer = i->line;
			if (verticalPx>0 && vCollision==false) { //Moving down
				if (Collision::checkLines(boundingBoxBottom,*cBuffer)) {
					vCollision = true;
				}
			} else if (verticalPx<0  && vCollision==false  && cBuffer->jumpthrough==false) { //Moving up
				if (Collision::checkLines(boundingBoxTop,*cBuffer)) {
					vCollision = true;
				}
			}
			if (cBuffer->jumpthrough==false) {
				if (horizontalPx>0 && hCollision==false) { //Moving right
					if (Collision::checkLines(boundingBoxRight,*cBuffer)) {
						hCollision = true;
					}
				}else if (horizontalPx<0 && hCollision==false) { //Moving left
					if (Collision::checkLines(boundingBoxLeft,*cBuffer)) {
						hCollision = true;
					}
				}
			}
			if (hCollision&&vCollision) { break; }
		}

	

	if (vCollision) {
		if (this->currentState->vVelocity>0) {
			this->currentState->onGround = true;
		}

		this->currentState->vVelocity = 0.00f;
	}


	if (vCollision==false) { currentState->y+= this->currentState->vVelocity*_timeFactor; }
	if (hCollision==false) { currentState->x+= horizontalPx; }else{
		this->currentState->hVelocity = 0;
	}

	

	/*
if (this->currentState->left)
{
this->currentState->hVelocity -=this->properties.Acceleration*_timeFactor;
}
if (this->currentState->right)
{
this->currentState->hVelocity += this->properties.Acceleration*_timeFactor;
}

this->currentState->hVelocity /= 1+0.8*_timeFactor;

collided = false;

newRect.p1.x = currentState->x-dimensionLeft;
	newRect.p1.x = currentState->x-dimensionLeft - this->currentState->hVelocity*_timeFactor;
	newRect.p1.y = currentState->y - dimensionTop;
	newRect.p2.x = currentState->x+dimensionRight + this->currentState->hVelocity*_timeFactor;
	newRect.p2.y = currentState->y - dimensionTop;
	newRect.p3.x = currentState->x+dimensionRight + this->currentState->hVelocity*_timeFactor;
	newRect.p3.y = currentState->y+dimensionBottom;
	newRect.p4.x = currentState->x - dimensionLeft - this->currentState->hVelocity*_timeFactor;
	newRect.p4.y = currentState->y+dimensionBottom;

	newRectJumpThrough.p1.x = currentState->x-dimensionLeft;
	newRectJumpThrough.p1.x = currentState->x-dimensionLeft - abs(this->currentState->hVelocity*_timeFactor);
	newRectJumpThrough.p1.y = currentState->y + dimensionBottom;
	newRectJumpThrough.p2.x = currentState->x+dimensionRight + abs(this->currentState->hVelocity*_timeFactor);
	newRectJumpThrough.p2.y = currentState->y + dimensionBottom;
	newRectJumpThrough.p3.x = currentState->x+dimensionRight + abs(this->currentState->hVelocity*_timeFactor);
	newRectJumpThrough.p3.y = currentState->y+dimensionBottom;
	newRectJumpThrough.p4.x = currentState->x - dimensionLeft - abs(this->currentState->hVelocity*_timeFactor);
	newRectJumpThrough.p4.y = currentState->y+dimensionBottom;

	for (register int i = 0; i<this->mData->getCollisionLineCount(); i++) {
		cBuffer = this->mData->getCollisionLine(i);
		bool col = false;
		if (cBuffer->jumpthrough) { //If this platform is jumpthrough
			//col = Collision::checkRectangleLine(newRect,*this->mData->getCollisionLine(i));
		}else{
			col = Collision::checkRectangleLine(newRect,*cBuffer);
			collided = col;
			break;
		}
	}

	if (collided==false) { currentState->x+= this->currentState->hVelocity*_timeFactor;  }

	if (collided) {
		this->currentState->hVelocity = 0x00;
	}
	
	*/

}

physicsState &physicsController::getState() {
	return *currentState;
}

void physicsController::hop(float power, bool requireOnGround) { //Performs a jump/hop with the specified power
   if (requireOnGround==true) {
	if (this->currentState->onGround ==true)
    {
		this->currentState->vVelocity = -power;
		this->currentState->onGround = false;
    }
   }else{
		this->currentState->vVelocity = -power;
		this->currentState->onGround = false;
   }
}

void physicsController::setDimensions(int left, int top, int right, int bottom) {
	dimensionLeft = left;
	dimensionTop = top;
	dimensionRight = right;
	dimensionBottom =bottom;
}

void physicsController::setDimensions(Rect &rectangle, Point &origin) {
	setDimensions(origin.x-rectangle.p1.x,origin.y-rectangle.p1.y,rectangle.p2.x-origin.x,rectangle.p3.y-origin.y);
}


physicsProperties physicsController::getDefaultPlayerPhysics() {
	physicsProperties pp;
	pp.Acceleration = 4;
	pp.Gravity = 2;
	pp.airResistance =1.5;
	pp.Friction = 2;
	return pp;
}