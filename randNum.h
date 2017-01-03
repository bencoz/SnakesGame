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
	randNum(TheSnakesGame* _theGame = nullptr);
	~randNum();
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
	void draw();
	void flicker();
	bool isLocOnScreenOk(const randNum*);
	void setGame(TheSnakesGame* _theGame);
	Point& getPoint();
};

#endif