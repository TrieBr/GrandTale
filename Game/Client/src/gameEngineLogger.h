// ----------------------------------------------------------------------
// gameEngineLogger.h
//     Copyright © Brad Triebwasser 2010
/* Description:
		Used to output errors, information, primarily used by the game engine itself.
*/
// ------------------------------------------------------------------------

#include <iostream>

#ifndef _H_GAMEENGINELOGGER_
#define _H_GAMEENGINELOGGER_

using std::cout;
using std::endl;

namespace gameEngine {
	class logger {
		public:
			static void initialize(std::ostream &errorS = std::cerr,std::ostream &logS = std::clog, std::ostream &warningS = std::cout, std::ostream &debugS = std::cout); //Initialized the logger
			static std::ostream errorStream; //Stream used for error output
			static std::ostream logStream; //Stream used for general information/logging
			static std::ostream warningStream; //Stream used for warnings, not necessarilty crucial
			static std::ostream debugStream; //Stream used for debug messages (typically used for just viewing values)
	};
}


#endif