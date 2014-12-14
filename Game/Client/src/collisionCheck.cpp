#include "collisionCheck.h"
#include <algorithm>
#include <cmath>
#define min(X,Y) (X<Y ? X : Y)
#define max(X,Y) (X>Y ? X : Y)
float Collision::pointLineDistance(Point& point, lineSeg& line) { //Checks distance between point and line
	register float x0,y0,x1,y1,x2,y2,x3,y3,dx,dy,t,segment;
    x1 = line.p1.x;
    y1 = line.p1.y;
    x2 = line.p2.x;
    y2 = line.p2.y;
    x3 = point.x;
    y3 = point.y;
    dx = x2 - x1;
    dy = y2 - y1;
    if ((dx == 0) && (dy == 0)) {
        x0 = x1;
        y0 = y1;
    }else{
        t = ((x3 - x1) * dx + (y3 - y1) * dy) / (dx * dx + dy * dy);
        t = min(max(0.0f,t),1.0f);
        x0 = x1 + t * dx;
        y0 = y1 + t * dy;
    }
    return pow((((x3-x0)*(x3-x0)) + ((y3-y0)*(y3-y0))),0.5f);
}

bool Collision::pointInLine(Point& point, lineSeg& line) { //Checks if given point lies in line segment

    return (pointLineDistance(point,line) < 0.001);
	/*
	static bool ret;
	ret = true;
	if (point.x > std::min(line.p1.x,line.p2.x)+abs(line.p1.x-line.p2.x) || point.x < std::min(line.p1.x,line.p2.x)) {
		ret = false;
	}
	if (point.y > std::min(line.p1.y,line.p2.y)+abs(line.p1.y-line.p2.y) || point.y < std::min(line.p1.y,line.p2.y)) {
		ret = false;
	}

    return ret;
	*/
}

	bool Collision::checkLines(lineSeg &line1, lineSeg &line2) { //Checks collision between two line segments
		static float ud,ua,ub;
		ua = 0;
		ud = (line2.p2.y - line2.p1.y) * (line1.p2.x - line1.p1.x) - (line2.p2.x - line2.p1.x) * (line1.p2.y - line1.p1.y);
		if (ud != 0) {
			ua = ((line2.p2.x - line2.p1.x) * (line1.p1.y - line2.p1.y) - (line2.p2.y - line2.p1.y) * (line1.p1.x - line2.p1.x)) / ud;
				ub = ((line1.p2.x - line1.p1.x) * (line1.p1.y - line2.p1.y) - (line1.p2.y - line1.p1.y) * (line1.p1.x - line2.p1.x)) / ud;
				if (ua < 0 || ua > 1 || ub < 0 || ub > 1) ua = 0;
		}else{ //Slopes are the same, check bounds
			if (pointInLine(line1.p1,line2) || pointInLine(line1.p2,line2)) {
				return true;
			}

		}
		return ua==0 ? false : true;
		
	}

	bool Collision::checkRectangles(Rect &rectangle1, Rect &rectangle2) {  //Checks collision between two rectangles
		return false;
	}

	bool Collision::checkRectangleLine(Rect &rectangle, lineSeg &lineSegment) { //Checks collision between a rectangle and a line

		//If any of the points are INSIDE the rectangle, its a collision
		if (pointInRectangle(lineSegment.p1,rectangle) || pointInRectangle(lineSegment.p2,rectangle)) {
			return true; //One or more ends of the line segment is in the rectangle, so its obviously overlapping
		}
		static lineSeg rectSegments[4];
		rectSegments[0].p1 = rectangle.p1;
		rectSegments[0].p2 = rectangle.p2;
		rectSegments[1].p1 = rectangle.p2;
		rectSegments[1].p2 = rectangle.p3;
		rectSegments[2].p1 = rectangle.p3;
		rectSegments[2].p2 = rectangle.p4;
		rectSegments[3].p1 = rectangle.p1;
		rectSegments[3].p2 = rectangle.p4;
		if (checkLines(rectSegments[0],lineSegment)) {
			return true;
		}
		if (checkLines(rectSegments[1],lineSegment)) {
			return true;
		}
		if (checkLines(rectSegments[2],lineSegment)) {
			return true;
		}
		if (checkLines(rectSegments[3],lineSegment)) {
			return true;
		}
		return false;
	}


	bool Collision::pointInRectangle(Point &point, Rect &rectangle) { //Checks if the specified point is inside the rectangle specified
		return (point.x > rectangle.p1.x && point.x < rectangle.p2.x && point.y > rectangle.p1.y && point.y < rectangle.p3.y);
	}