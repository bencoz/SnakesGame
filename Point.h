#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point {
	int x, y;
public:
	Point(int _x=1, int _y=1) : x(_x), y(_y) {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch) {
		gotoxy(x, y);
		cout << ch;
		cout.flush();
	}
	void draw(int num) {
		gotoxy(x, y);
		cout << num;
		cout.flush();
	}
	void move();
	void move(int direction);
	Point next(int direction) {
		Point next = *this;
		next.move(direction);
		return next;
	}
	bool isSame(const Point& p) const {
		return x == p.x && y == p.y;
	}
};

#endif