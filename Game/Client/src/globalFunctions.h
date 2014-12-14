// ----------------------------------------------------------------------
// globalFunctions.h
//     Copyright � Brad Triebwasser 2010
/* Description:
	Global functions for the game. These are generic functions that can be used anywher
*/
// ------------------------------------------------------------------------
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <vector>
#include <string>
#ifndef _H_GAMEENGINEGLOBALFUNCTIONS_
#define _H_GAMEENGINEGLOBALFUNCTIONS_

namespace gameEngine {

	class globalFunctions
	{
	public:
		static bool pointInRegion(int pointCheckX, int pointCheckY, int areaX1, int areaY1, int areaX2, int areaY2); //Checks if the specified point is inside the specified region
		static bool pointInRegion2(int pointCheckX, int pointCheckY, int X, int Y, int width, int height);
		static std::string formatString(char *fmt, ...);
		static int drawTextWrapped(ALLEGRO_FONT* font, float x, float width, float y, float maxHeight, ALLEGRO_COLOR color, int flags, std::string &text, bool dontDraw = false);
		static void preWrapText(ALLEGRO_FONT* font, float width, std::vector<std::string> &output, std::string inputText);

	};
}

#endif