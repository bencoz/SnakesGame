#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include "BasicObj.h"
class TheSnakesGame;
class randNum;
class BasicOBJ;

class Snake : public BasicOBJ {
	int stackSize = 5;
	char arrowKeys[5];
	bool freeze = false;
public:
	Snake(int size, const Point& p, Color c, int dir, char sign) : BasicOBJ(size, p, c, dir, sign) {}//c'tor
	~Snake(){} //d'tor
	Snake(const Snake& s); //copy c'tor
	virtual randNum* move();
	void setArrowKeys(const char* keys);
	int getDirection(char key);
	void setDirection(int dir) {
		BasicOBJ::setDirection(dir);
	}
	bool shoot(char key);
	void reload();
	void reload(int a);
	void setFreeze(int a);
	bool isFreeze(){
		return freeze;
	}
	void cleanSnakefromGame();
};
#endif