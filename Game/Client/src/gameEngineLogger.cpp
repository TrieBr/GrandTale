// ----------------------------------------------------------------------
// gameEngineLogger.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
		Used to output errors, information, primarily used by the game engine itself.
*/
// ------------------------------------------------------------------------

#include "gameEngineLogger.h"
#include <sstream>
namespace gameEngine {

	std::stringstream outStream(std::ios::out);
	std::ostream logger::errorStream(outStream.rdbuf());
	std::ostream logger::logStream(outStream.rdbuf());
	std::ostream logger::warningStream(outStream.rdbuf());
	std::ostream logger::debugStream(outStream.rdbuf());

	void logger::initialize(std::ostream &errorS,std::ostream &logS, std::ostream &warningS, std::ostream &debugS) {//Initialize the logger
		logger::errorStream.rdbuf(errorS.rdbuf()); //Set the error stream
		logger::logStream.rdbuf(logS.rdbuf()); //Set the log stream
		logger::warningStream.rdbuf(warningS.rdbuf()); //Set the warning stream
		logger::debugStream.rdbuf(debugS.rdbuf()); //Set the debug stream
	}
}