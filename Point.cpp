#include "Point.h"

void Point::move() {
	int dir = rand() % 4;
	move(dir);
}

void Point::move(int dir) {
	switch (dir) {
	case UP:
		--y;
		if (y < 4) {  //because 4 upper rows are for menu !
			y = 24;
		}
		break;
	case DOWN:
		++y;
		if (y > 24) {
			y = 1;
		}
		break;
	case LEFT:
		--x;
		if (x < 1) {
			x = 79;
		}
		break;
	case RIGHT:
		++x;
		if (x > 79) {
			x = 1;
		}
		break;
	}
}