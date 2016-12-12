#ifndef _INTEGER_H_
#define _INTEGER_H_

#include <iostream>
#include <random>
#include "io_utils.h"
#include "point.h"
class TheSnakesGame;
class Point;

class randNum{
	int val;
	int numOfDig = 1;
	Point loc;
	TheSnakesGame* thegame;
public:
	randNum() {
		loc.set((rand() % 81),(rand() % 21) + 5);
		val = setProp();
		if (val >= 100)
			numOfDig = 3;
		else if (val >= 10)
			numOfDig = 2;
		/*if (isLocOk(loc.getX, numOfDig))
			loc.draw(val);*/
	}
	int setProp();
	bool isLocOk(int, int numOfDig);
	void setGame(TheSnakesGame* _theGame) {
		thegame = _theGame;
	}
};

#endif