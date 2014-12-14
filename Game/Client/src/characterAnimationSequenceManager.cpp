#include "gameEngine.h"
#include "characterAnimationSequenceManager.h"
#include <sstream>


namespace character {
		std::map<int,characterAnimationSequence*> characterAnimationSequenceManager::sequenceList;
		characterAnimationSequence* characterAnimationSequenceManager::loadSequence(int sequenceID) {
			std::stringstream Formatter;
			Formatter << ":character:animationSequences:" << sequenceID << ".anim";
			ALLEGRO_FILE* sequenceFile = gameEngine::resources::data.openSubFile(Formatter.str(),false); //Open the animation sequence file
			characterAnimationSequence* newSequence = new characterAnimationSequence();
			newSequence->sequenceID = sequenceID;
			float numberOfKeyframes;
			al_fread(sequenceFile,&numberOfKeyframes,sizeof(float)); //Read number of keyframes
			for(int i=0; i<(int)numberOfKeyframes; i++) { //For each keyframe
					animationPoint newPoint;

				al_fread(sequenceFile,&newPoint.timeFrame,sizeof(float));

				al_fread(sequenceFile,&newPoint.Head.x,sizeof(float));
				al_fread(sequenceFile,&newPoint.Head.y,sizeof(float));
				al_fread(sequenceFile,&newPoint.Head.rotation,sizeof(float));

				al_fread(sequenceFile,&newPoint.body.x,sizeof(float));
				al_fread(sequenceFile,&newPoint.body.y,sizeof(float));
				al_fread(sequenceFile,&newPoint.body.rotation,sizeof(float));
				
				al_fread(sequenceFile,&newPoint.leftHand.x,sizeof(float));
				al_fread(sequenceFile,&newPoint.leftHand.y,sizeof(float));
				al_fread(sequenceFile,&newPoint.leftHand.rotation,sizeof(float));

				al_fread(sequenceFile,&newPoint.rightHand.x,sizeof(float));
				al_fread(sequenceFile,&newPoint.rightHand.y,sizeof(float));
				al_fread(sequenceFile,&newPoint.rightHand.rotation,sizeof(float));

				al_fread(sequenceFile,&newPoint.leftFoot.x,sizeof(float));
				al_fread(sequenceFile,&newPoint.leftFoot.y,sizeof(float));
				al_fread(sequenceFile,&newPoint.leftFoot.rotation,sizeof(float));
				float footType;
				al_fread(sequenceFile,&footType,sizeof(float));
				newPoint.leftFoot.footState = (character::_footState)(int)footType;

				al_fread(sequenceFile,&newPoint.rightFoot.x,sizeof(float));
				al_fread(sequenceFile,&newPoint.rightFoot.y,sizeof(float));
				al_fread(sequenceFile,&newPoint.rightFoot.rotation,sizeof(float));
				al_fread(sequenceFile,&footType,sizeof(float));
				newPoint.rightFoot.footState = (character::_footState)(int)footType;

				newSequence->addFrame(newPoint);
			}
			al_fclose(sequenceFile);
			sequenceList[sequenceID] = newSequence;
			return newSequence;
		}

		void characterAnimationSequenceManager::preloadAllSequences() { //Preloads all sequences
			//TODO: PReload sequences here... Otherwise they are loaded on demand which may be slow
		}

		characterAnimationSequence* characterAnimationSequenceManager::getSequence(int sequenceID) { //Get a sequence
			if (sequenceList.find(sequenceID)==sequenceList.end()) { //If the sequence isn't loaded.. Load on demand
				return loadSequence(sequenceID); //Load on demand and return the sequence
			}else{
				return sequenceList[sequenceID]; //Return the preloaded sequence.
			}
		}
}