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
		val = setValbyProp();
		if (val >= 100)
			numOfDig = 3;
		else if (val >= 10)
			numOfDig = 2;
		loc.set((rand() % 80), (rand() % 18) + 5);
		/*setTextColor(WHITE);
		if (isLocOk(loc.getX(), numOfDig))
			loc.draw(val);*/
	}
	int setValbyProp();
	int getRandX() const {
		return loc.getX();
	}
	int getRandY() const {
		return loc.getY();
	}
	int getVal() const {
		return val;
	}
	int getNumDig(){
		return numOfDig;
	}
	void draw() {
		setTextColor(WHITE);
		gotoxy(loc.getX(), loc.getY());
		cout << val;
		cout.flush();
	}
	bool isLocOk(int, int numOfDig);
	void setGame(TheSnakesGame* _theGame) {
		thegame = _theGame;
	}
};

#endif