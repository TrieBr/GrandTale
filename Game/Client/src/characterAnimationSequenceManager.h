// ----------------------------------------------------------------------
// characterAnimationSequenceManager.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Used for loading all of the animation sequences, indexing them and allowing other classes to grab and use them. Also in charge of unloading them all..
*/
// ------------------------------------------------------------------------



#include <map>
#include "characterAnimation.h"

#ifndef _H_CHARANIMATIONSEQUENCEMANAGER
#define _H_CHARANIMATIONSEQUENCEMANAGER


enum SEQUENCES {
	SEQ_IDLE = 0
};

namespace character {
	class characterAnimationSequenceManager {
		static std::map<int,characterAnimationSequence*> sequenceList;
		static characterAnimationSequence* loadSequence(int sequenceID);
	public: 
		static void preloadAllSequences(); //Preloads all sequences
		static characterAnimationSequence* getSequence(int sequenceID); //Get a sequence
	};

}

#endif

