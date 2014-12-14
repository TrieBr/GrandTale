#include <string>
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include "gameEngineResources.h"


#ifndef _H_PLAYERSPEECHBUBBLE
#define  _H_PLAYERSPEECHBUBBLE



class playerSpeechBubble {
public:
	playerSpeechBubble(); //Initializaton
	~playerSpeechBubble();
	void displayText(std::string textToDisplay, bool animate = true);
	void update(double _timeFactor); //Update the speech bubble
	void render(float X, float Y); //Render the speech bubble at specified position?
	void renderBubble(float X, float Y, std::string stringDisplay);
private:
	float alpha;
	unsigned char animationProgress;
	double timeStarted;

	//Image resources
	ALLEGRO_BITMAP *bubbleSliceNW, *bubbleSliceN, *bubbleSliceNE, *bubbleSliceE, *bubbleSliceSE, *bubbleSliceS, *bubbleSliceSW, *bubbleSliceW, *speechPoint;

	short rectangleWidth;
	short rectangleHeight;
	short surfaceWidth;
	short surfaceHeight;
	float scale;
	ALLEGRO_BITMAP* bubbleBitmap;
	ALLEGRO_FONT* textFont;
};

#endif