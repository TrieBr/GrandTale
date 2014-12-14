

#ifndef _H_TOOLTIP
#define _H_TOOLTIP

class tooltip {
public:
	tooltip() {}
	~tooltip() {}
	virtual void initialize() = 0;
	virtual void cleanup() = 0;
	virtual void update(double deltaTime) = 0;
	virtual void render(float X, float Y) = 0;


};

#endif