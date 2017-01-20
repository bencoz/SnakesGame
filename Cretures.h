#ifndef _CRETURES_H_
#define _CRETURES_H_
#include "randNum.h"
#include "BasicOBJ.h"

class numEater : public BasicOBJ {
	bool wasHit = false;

public:
	numEater(Point p = { 10, 19 }, int dir = STOP) : BasicOBJ(1, p, YELLOW, dir, '%'){};
	virtual randNum* move();
	Point** getSolutions(int *size);
	Point calcRoute(Point *target);
	Point* findClosest(Point **arr, int size);
};

class rowFly : public BasicOBJ {
	bool wallMover = false;
public:
	rowFly(Point p = { 30, 23 }, int dir = STOP, bool flag = false) : BasicOBJ(1, p, GREEN, dir, '!'){ wallMover = flag; };
	virtual randNum* move();
	void setWallMove(int a){
		a > 0 ? wallMover = true : wallMover = false;
	}
	bool getWallMove(){
		return wallMover;
	}
};

class colFly : public BasicOBJ {
	bool wallMover = false;
	bool wasHit=false;

public:
	colFly(Point p = { 45, 23 }, int dir = STOP, bool flag = false) : BasicOBJ(1, p, WHITE, dir, '$'){ wallMover = flag; };
	virtual randNum* move();
	void setWallMove(int a){
		a > 0 ? wallMover = true : wallMover = false;
	}
	bool getWallMove(){
		return wallMover;
	}
};
#endif