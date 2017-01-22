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
	bool print = false;
	bool solve = false;
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
	void setSolve(int a){
		a > 0 ? solve = true : solve = false;
	}
	bool* const getSolve(){
		return &solve;
	}
	void draw();
	void flicker();
	bool isLocOnScreenOk(const randNum*);
	void setGame(TheSnakesGame* _theGame);
	Point& getPoint();
	Point* getPointPointer();
	void setPrint(){
		print = true;
	}
	bool checkMission();
};

#endif