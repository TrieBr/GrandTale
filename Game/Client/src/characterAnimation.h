// ----------------------------------------------------------------------
// characterAnimation.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Represents a sequence of positions for a character
*/
// ------------------------------------------------------------------------


#include <vector>
#include <queue>
#ifndef _H_CHARANIMATION
#define _H_CHARANIMATION

namespace character {
	enum _footState {
		STRAIGHT,
		FACING
	};
	struct bodyPartPosition {
		float x; //X position relative to navel..
		float y; //Y position relavie to navel 
		float rotation; //Rotation in radians..
		_footState footState; //State of tehe foot (front facing, etc)
	};
	struct animationPoint {
		float timeFrame; //Where in the timeframe the point is (between 0 and 1)
		bodyPartPosition Head;
		bodyPartPosition leftHand;
		bodyPartPosition rightHand;
		bodyPartPosition leftFoot;
		bodyPartPosition rightFoot;
		bodyPartPosition body;
	
	};
	/*
	extern animationPoint betweenPoints(const animationPoint &point1,const animationPoint &point2, float percent) {
		animationPoint newPoint;
		newPoint.body.rotation =	point1.body.rotation + ((	point2.body.rotation -	point1.body.rotation)*percent);
		newPoint.body.x =			point1.body.x + ((			point2.body.x -			point1.body.x)*percent);
		newPoint.body.y =			point1.body.y + ((			point2.body.y -			point1.body.y)*percent);

		newPoint.Head.rotation =	point1.Head.rotation + ((	point2.Head.rotation -	point1.Head.rotation)*percent);
		newPoint.Head.x =			point1.Head.x + ((			point2.Head.x -			point1.Head.x)*percent);
		newPoint.Head.y =			point1.Head.y + ((			point2.Head.y -			point1.Head.y)*percent);

		newPoint.leftFoot.rotation =	point1.leftFoot.rotation + ((	point2.leftFoot.rotation -	point1.leftFoot.rotation)*percent);
		newPoint.leftFoot.x =			point1.leftFoot.x + ((			point2.leftFoot.x -			point1.leftFoot.x)*percent);
		newPoint.leftFoot.y =			point1.leftFoot.y + ((			point2.leftFoot.y -			point1.leftFoot.y)*percent);

		newPoint.leftHand.rotation =	point1.leftHand.rotation + ((	point2.leftHand.rotation -	point1.leftHand.rotation)*percent);
		newPoint.leftHand.x =			point1.leftHand.x + ((			point2.leftHand.x -			point1.leftHand.x)*percent);
		newPoint.leftHand.y =			point1.leftHand.y + ((			point2.leftHand.y -			point1.leftHand.y)*percent);

		newPoint.rightFoot.rotation =	point1.rightFoot.rotation + ((	point2.rightFoot.rotation -	point1.rightFoot.rotation)*percent);
		newPoint.rightFoot.x =			point1.rightFoot.x + ((			point2.rightFoot.x -			point1.rightFoot.x)*percent);
		newPoint.rightFoot.y =			point1.rightFoot.y + ((			point2.rightFoot.y -			point1.rightFoot.y)*percent);

		newPoint.rightHand.rotation =	point1.rightHand.rotation + ((	point2.rightHand.rotation -	point1.rightHand.rotation)*percent);
		newPoint.rightHand.x =			point1.rightHand.x + ((			point2.rightHand.x -			point1.rightHand.x)*percent);
		newPoint.rightHand.y =			point1.rightHand.y + ((			point2.rightHand.y -			point1.rightHand.y)*percent);
		return newPoint;
	}
	*/

	enum animationPlayType {
		ANIMATION_PLAY_ONCE,
		ANIMATION_LOOP,
		ANIMATION_SINGLEFRAME
	};
	
	enum animationSegmentType {
		ANIMATION_BOTH,
		ANIMATION_UPPER,
		ANIMATION_LOWER
	};
	/*
	Priorities will be played if they are of higher or equal priority of the current playing animation.
	eg, running could be medium priority and idle is low prioriy, so when the player lands, it will
	*/

	class characterAnimationSequence { //Represents an animation sequence.. Should be only loaded once in the game
	public:
		unsigned short sequenceID;
		void addFrame(animationPoint &pointData);
		std::vector<animationPoint> animationTimeframe;

	};

	struct animationState {
		double animationPosition;
		double animationDuration; //The duration of the animation.
		animationPlayType playType; //The mode to play the animation
		animationPoint bodyPartsState; //The position of the body parts..
		std::vector<animationPoint>::iterator lastPoint; //The last point we were at..
		std::vector<animationPoint>::iterator nextPoint; //The next keyframe we are "interpolating" towards
		characterAnimationSequence *sequence; //The sequence to follow
	};

	struct animationQueueEntry {
		animationState* state;
		animationPlayType playType;
		bool blend;
		float blendAmt;
	};
	class characterAnimation { //Represents an ANIMATOR which essentially "plays" an animation
	public:
		characterAnimation();
		void setAnimation(characterAnimationSequence *animationSequence, animationPlayType playType, bool blend = false, float blendAmt = 0.1, float duration = 0.6);
		void overrideTopAnimation();
		void overrideBottomAnimation();
		characterAnimation* getTopOverrideAnimation() { return topAnimationOverride; }
		characterAnimation* getBottomOverrideAnimation() { return bottomAnimationOverride; }
		animationPoint getCurrentFrame(); //Returns the current position of the body parts..
		
		void stepAnimation(double _timeFactor, float speed = 1); //Steps/u[dates the animation
		animationState& getCurrentState() { return currentState; };
		void setCurrentState(animationState & state) { currentState = state; }
		float getPercent() { return abs(currentState.animationPosition)+abs(currentState.animationPosition); }
		const characterAnimationSequence* getCurrentSequence() { return currentState.sequence; }
		float getCurrentPosition() { return currentState.animationPosition; }
		void setCurrentPosition(float pos) {  currentState.animationPosition = pos; }
		float getLastBlend() { return lastBlend; }
		void queueAnimation(animationQueueEntry entry) { sequenceQueue.push(entry); }
		bool getAnimationFinished() { return animationFinished; }
		void setStopAfterProgress(float progress) { stopAfterProgress = progress; stopAfterProgressEnabled = true; stopProgressAccumulator = 0;}
	private:
		animationState currentState;
		float lastBlend;
		bool animationFinished;
		double stopAfterProgress;
		double stopProgressAccumulator;
		bool stopAfterProgressEnabled;
		
		bool topOverridden, bottomOverridden;
		bool topBlendingBack, bottomBlendingBack;
		characterAnimation *topAnimationOverride; //Playing a seperate animation on the upper body (evetything except feet)
		characterAnimation *bottomAnimationOverride;//Playing a seperate animation on the lower body (just feet)
		std::queue<animationQueueEntry> sequenceQueue; 
	};

};

#endif

