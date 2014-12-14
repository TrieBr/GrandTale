

#include "geometry.h"

class Collision {
public:
	static bool checkLines(lineSeg &line1, lineSeg &line2); //Checks collision between two line segments
	static bool checkRectangles(Rect &rectangle1, Rect &rectangle2); //Checks collision between two rectangles
	static bool checkRectangleLine(Rect &rectangle, lineSeg &lineSegment); //Checks collision between a rectangle and a line
	static bool pointInLine(Point& point, lineSeg& line); //Checks if given point lies in line segment
private:
	static bool pointInRectangle(Point &point, Rect &rectangle); //Checks if the specified point is inside the rectangle specified
	
	static float pointLineDistance(Point& point, lineSeg& line); //Checks distance between point and line
};