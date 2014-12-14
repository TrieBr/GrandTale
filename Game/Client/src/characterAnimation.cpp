#include "characterAnimation.h"

#ifndef _WIN32
#define abs(x) ((x)<(0) ?  (x*-1) : (x))
#endif


namespace character {
		void characterAnimationSequence::addFrame(animationPoint &pointData) { //Adds a frame to the animation
			this->animationTimeframe.push_back(pointData);
		}


		characterAnimation::characterAnimation() {
			topOverridden = false;
			bottomOverridden = false;
			topAnimationOverride = NULL;
			bottomAnimationOverride = NULL;
			animationFinished = true;
			topBlendingBack = false;
			bottomBlendingBack = false;
			stopAfterProgress = -1;
			stopProgressAccumulator = 0;
			stopAfterProgressEnabled = false;
		}
		void characterAnimation::setAnimation(characterAnimationSequence *animationSequence, animationPlayType playType, bool blend, float blendAmt, float duration) {
			animationFinished = false;
			if (blend) {
				lastBlend = blendAmt;
			}else{
				lastBlend = 0;
			}
			currentState.sequence = animationSequence; //Set the sequence
			currentState.animationDuration = duration; //Animation duration is one second..
			if (blend) {
				currentState.animationPosition = -blendAmt; //Start at the beginning...
			}else{
				currentState.animationPosition = 0; //Start at the beginning...
			}
			if (!blend) {
				currentState.bodyPartsState = animationSequence->animationTimeframe[0]; //Set the first keyframe
				currentState.lastPoint = animationSequence->animationTimeframe.begin(); //Set the first keyframe
			}

			if (!blend) {
				if (animationSequence->animationTimeframe.size()>1) {
					currentState.nextPoint = animationSequence->animationTimeframe.begin()+1; //Set the next keyframe to interpolate to
				}else{
					currentState.nextPoint = animationSequence->animationTimeframe.begin(); //Set the next keyframe to interpolate to
				}
			}else{
					currentState.nextPoint = animationSequence->animationTimeframe.begin();
			}

			currentState.playType = playType;
			if (playType==ANIMATION_SINGLEFRAME) { //We only want a single frame
				currentState.bodyPartsState = currentState.sequence->animationTimeframe[0];
			}
		}

		void  characterAnimation::overrideTopAnimation() {
			if (topOverridden==false) {
				if (topAnimationOverride==NULL) {
					topAnimationOverride = new characterAnimation();
				}
				topOverridden = true;
				topBlendingBack = false;
			}
		}
		void characterAnimation::overrideBottomAnimation() {
			if (bottomOverridden==false) {
				if (bottomAnimationOverride==NULL) {
					bottomAnimationOverride = new characterAnimation();
				}
				bottomOverridden = true;
				bottomBlendingBack = false;
			}
		}
		animationPoint characterAnimation::getCurrentFrame() { //Returns the current position of the body parts..
			animationPoint newState = currentState.bodyPartsState;
			if (topOverridden==true) {
				animationPoint topAnimationPoint = topAnimationOverride->getCurrentFrame();
				newState.body = topAnimationPoint.body;
				newState.Head = topAnimationPoint.Head;
				newState.leftHand = topAnimationPoint.leftHand;
				newState.rightHand = topAnimationPoint.rightHand;
				
			}
			if (bottomOverridden==true) {
				animationPoint bottomAnimationPoint;
				bottomAnimationPoint = bottomAnimationOverride->getCurrentFrame();
				newState.leftFoot =  bottomAnimationPoint.leftFoot;
				newState.rightFoot = bottomAnimationPoint.rightFoot;
			}
			
			return newState; //Return the current state of the body parts
		}
		void characterAnimation::stepAnimation(double _timeFactor, float speed){ //Steps/u[dates the animation
			
			if (topOverridden==true) {	
				topAnimationOverride->stepAnimation(_timeFactor,speed);
				if (topAnimationOverride->getAnimationFinished()) {
						currentState.bodyPartsState.body = topAnimationOverride->getCurrentState().bodyPartsState.body;
						currentState.bodyPartsState.Head = topAnimationOverride->getCurrentState().bodyPartsState.Head;
						currentState.bodyPartsState.leftHand = topAnimationOverride->getCurrentState().bodyPartsState.leftHand;
						currentState.bodyPartsState.rightHand = topAnimationOverride->getCurrentState().bodyPartsState.rightHand;
						topOverridden = false;
				}
				
			}
			if (bottomOverridden==true) {
				bottomAnimationOverride->stepAnimation(_timeFactor,speed);
				if (bottomAnimationOverride->getAnimationFinished()) {
						currentState.bodyPartsState.leftFoot= topAnimationOverride->getCurrentState().bodyPartsState.leftFoot;
						currentState.bodyPartsState.rightFoot = topAnimationOverride->getCurrentState().bodyPartsState.rightFoot;
						bottomOverridden = false;
				}
			}

			if (currentState.animationPosition<=1) {

				if (currentState.animationPosition>=currentState.nextPoint->timeFrame) { //We are at the keyframe.. Advance..
					currentState.lastPoint = currentState.nextPoint; //Set the last point to the point we just arrived at..
					currentState.nextPoint++; //Advance the frame..
					if (currentState.nextPoint==currentState.sequence->animationTimeframe.end()) { //We are at the end of the sequence..
						if (currentState.playType==ANIMATION_LOOP) { //If we are looping..
							currentState.nextPoint = currentState.sequence->animationTimeframe.begin(); //Start at the beginning
							currentState.animationPosition = (1-(currentState.animationPosition))*-1;
							if (abs(currentState.animationPosition)==0) {
								currentState.lastPoint = currentState.sequence->animationTimeframe.begin(); //Start at the beginning
								if (currentState.sequence->animationTimeframe.size()>1) {
									currentState.nextPoint = currentState.sequence->animationTimeframe.begin()+1; //Set the next keyframe to interpolate to
								}else{
									currentState.nextPoint = currentState.sequence->animationTimeframe.begin(); //Set the next keyframe to interpolate to
								}
								currentState.animationPosition = 0;
								currentState.bodyPartsState = *currentState.lastPoint;
							}

						}else{
							if (getAnimationFinished()==false) {
								currentState.lastPoint--;
								currentState.nextPoint--;
								animationFinished = true;
							}
							return; //We aren't looping, so break
						}
					}
				}

				double timeDifference = abs((currentState.animationDuration * currentState.nextPoint->timeFrame) - (currentState.animationDuration * currentState.animationPosition));
				double frames = timeDifference/_timeFactor;
				currentState.bodyPartsState.Head.y += ((currentState.nextPoint->Head.y-currentState.bodyPartsState.Head.y)/frames) * _timeFactor;
				currentState.bodyPartsState.Head.x += ((currentState.nextPoint->Head.x-currentState.bodyPartsState.Head.x)/frames) * _timeFactor;
				currentState.bodyPartsState.Head.rotation += ((currentState.nextPoint->Head.rotation-currentState.bodyPartsState.Head.rotation)/frames) * _timeFactor;

				currentState.bodyPartsState.body.y += ((currentState.nextPoint->body.y-currentState.bodyPartsState.body.y)/frames) * _timeFactor;
				currentState.bodyPartsState.body.x += ((currentState.nextPoint->body.x-currentState.bodyPartsState.body.x)/frames) * _timeFactor;
				currentState.bodyPartsState.body.rotation += ((currentState.nextPoint->body.rotation-currentState.bodyPartsState.body.rotation)/frames) * _timeFactor;


				currentState.bodyPartsState.leftHand.y += ((currentState.nextPoint->leftHand.y-currentState.bodyPartsState.leftHand.y)/frames) * _timeFactor;
				currentState.bodyPartsState.leftHand.x += ((currentState.nextPoint->leftHand.x-currentState.bodyPartsState.leftHand.x)/frames) * _timeFactor;
				currentState.bodyPartsState.leftHand.rotation += ((currentState.nextPoint->leftHand.rotation-currentState.bodyPartsState.leftHand.rotation)/frames) * _timeFactor;

				currentState.bodyPartsState.rightHand.y += ((currentState.nextPoint->rightHand.y-currentState.bodyPartsState.rightHand.y)/frames) * _timeFactor;
				currentState.bodyPartsState.rightHand.x += ((currentState.nextPoint->rightHand.x-currentState.bodyPartsState.rightHand.x)/frames) * _timeFactor;
				currentState.bodyPartsState.rightHand.rotation += ((currentState.nextPoint->rightHand.rotation-currentState.bodyPartsState.rightHand.rotation)/frames) * _timeFactor;

				currentState.bodyPartsState.leftFoot.y += ((currentState.nextPoint->leftFoot.y-currentState.bodyPartsState.leftFoot.y)/frames) * _timeFactor;
				currentState.bodyPartsState.leftFoot.x += ((currentState.nextPoint->leftFoot.x-currentState.bodyPartsState.leftFoot.x)/frames) * _timeFactor;
				currentState.bodyPartsState.leftFoot.rotation += ((currentState.nextPoint->leftFoot.rotation-currentState.bodyPartsState.leftFoot.rotation)/frames) * _timeFactor;
				currentState.bodyPartsState.leftFoot.footState = currentState.lastPoint->leftFoot.footState;

				currentState.bodyPartsState.rightFoot.y += ((currentState.nextPoint->rightFoot.y-currentState.bodyPartsState.rightFoot.y)/frames) * _timeFactor;
				currentState.bodyPartsState.rightFoot.x += ((currentState.nextPoint->rightFoot.x-currentState.bodyPartsState.rightFoot.x)/frames) * _timeFactor;
				currentState.bodyPartsState.rightFoot.rotation += ((currentState.nextPoint->rightFoot.rotation-currentState.bodyPartsState.rightFoot.rotation)/frames) * _timeFactor;
				currentState.bodyPartsState.rightFoot.footState = currentState.lastPoint->rightFoot.footState;

				currentState.animationPosition += (_timeFactor/currentState.animationDuration) *_timeFactor;
			}
			if (currentState.animationPosition>1) {
				currentState.animationPosition=1;
			}
			
		}

};