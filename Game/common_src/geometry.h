
#ifndef _H_GEOMETRY
#define _H_GEOMETRY

class Point {
public:
	float x;
	float y;
	  bool operator==(const Point &other) const {
		return (other.x==this->x && other.y==this->y);
	  }

};

struct Rect {
	Point p1, p2, p3, p4;
};

struct lineSeg {
	Point p1, p2;
};

#endif