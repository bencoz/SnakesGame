#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;
enum { UP=0, DOWN=1, LEFT=2, RIGHT=3 };

class Point {
	int x, y;
public:
	Point(int _x=1, int _y=1) : x(_x), y(_y) {}

	int getX() const {
		return x;
	}
	int getY() const{
		return y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch);
	void draw(int num);
	Point next(int direction);

	void move();
	void move(int direction);

	bool isSame(const Point& p) const {
		return x == p.x && y == p.y;
	}
};

#endif