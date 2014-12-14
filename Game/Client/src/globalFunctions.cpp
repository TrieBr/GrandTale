// ----------------------------------------------------------------------
// globalFunctions.cpp
//     Copyright � Brad Triebwasser 2010
/* Description:
	Provides generic functions for use throughout the game
*/

#include "globalFunctions.h"
#include <stdarg.h>
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <RakString.h>
namespace gameEngine
{
	bool globalFunctions::pointInRegion(int pointCheckX, int pointCheckY, int areaX1, int areaY1, int areaX2, int areaY2) { //Checks if the specified point is inside the specified region
		if (pointCheckX>=areaX1 && pointCheckX<=areaX2 && pointCheckY>=areaY1 && pointCheckY<=areaY2)
		{//The point is in the region
			return true;
		}else{
			//Point is not in the region, return false
			return false;
		}
	}

	bool globalFunctions::pointInRegion2(int pointCheckX, int pointCheckY, int X, int Y, int width, int height) { //Checks if the specified point is inside the specified region
		return pointInRegion(pointCheckX, pointCheckY, X, Y, X+width,Y+height);
	}
	
	std::string globalFunctions::formatString(char *fmt, ...) {
		//FIXME: Uses raknet string.. Make custom function
		va_list ap; 
		va_start(ap,fmt); 
		std::string ret = RakNet::RakString(fmt,ap).C_String();
		 va_end(ap);
		return ret;
	}
	int globalFunctions::drawTextWrapped(ALLEGRO_FONT* font, float x, float width, float y, float maxHeight, ALLEGRO_COLOR color, int flags, std::string &text, bool dontDraw) {
		std::string lineDraw;
		std::string textBuffer = text;
		float yy = 0;
		int splitString = -1;
		while (1) {
			size_t space = textBuffer.find(" ");
			std::string nextWord;
			if (splitString!=-1) {
				nextWord = textBuffer.substr(0,splitString);
				textBuffer.erase(0,splitString);
			}
			else if (space!=textBuffer.npos) {
				nextWord = textBuffer.substr(0,space+1);
				textBuffer.erase(0,space+1);
			}else{
				nextWord = textBuffer.substr(0, textBuffer.length());
				textBuffer.erase(0,textBuffer.length());
			}
			if (al_get_text_width(font,std::string(lineDraw).append(nextWord).c_str())<width) {
				lineDraw.append(nextWord);
				splitString = -1;
			}else{
				if (dontDraw==false) {
					al_draw_text(font,color,x,y+yy,flags,lineDraw.c_str());
				}
				lineDraw = "";
				textBuffer.insert(0,nextWord); //Re append it
				if (al_get_text_width(font,nextWord.c_str())>width) {
					if (splitString!=-1) {
						splitString--;
					}else{
						splitString  = 25;
					}
				}
				
				yy+=al_get_font_line_height(font);
			}
			if (textBuffer.length()==0) {
				al_draw_text(font,color,x,y+yy,flags,lineDraw.c_str());
				break;
			}
		}
		return yy+al_get_font_line_height(font);
	}

	void globalFunctions::preWrapText(ALLEGRO_FONT* font, float width, std::vector<std::string> &output, std::string inputText) {

			size_t off =0;
			 size_t  lastSeg = 0;
			  std::string temp = "";
			 while ( true ) {
				  size_t lastOff = off;
				  off = inputText.find_first_of(' ',off+1);
				  
				  if (off==std::string::npos) off = inputText.length();
				  std::string oldTemp = temp;
				  temp = inputText.substr(lastSeg,off-lastSeg);
				  if (al_get_text_width(font,temp.c_str()) > width) {
					  output.push_back(oldTemp);
						off = lastOff;
						lastSeg = off;

				  }
				  if (off == inputText.length()) { 
					  output.push_back(temp);
					  break;
				  }

			 }

	}
	
}