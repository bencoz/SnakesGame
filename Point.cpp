#include "Point.h"

void Point::move() {
	int dir = rand() % 4;
	move(dir);
}
void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch;
	cout.flush();
}
void Point::draw(int num) {
	gotoxy(x, y);
	cout << num;
	cout.flush();
}
Point Point::next(int direction) {
	Point next = *this;
	next.move(direction);
	return next;
}
void Point::move(int dir) {
	switch (dir) {
	case UP:
		--y;
		if (y < 4) {  //because 4 upper rows are for menu !
			y = 23;
		}
		break;
	case DOWN:
		++y;
		if (y > 23) {
			y = 4;
		}
		break;
	case LEFT:
		--x;
		if (x < 0) {
			x = 79;
		}
		break;
	case RIGHT:
		++x;
		if (x > 79) {
			x = 0;
		}
		break;
	}
}