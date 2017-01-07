#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"

class TheSnakesGame;
class randNum;


class Snake {
	char sign;
	int size;
	int stackSize = 5;
	Point* body;
	int direction;
	char arrowKeys[5];
	Color color;
	TheSnakesGame* theGame;
	bool freeze = false;
public:
	Snake(int size, const Point& position, Color c, int dir = 3, char symb = '@');//c'tor
	~Snake(){ delete[] body; } //d'tor
	Snake(const Snake& s); //copy c'tor

	void setGame(TheSnakesGame* _theGame){
		theGame = _theGame;
	}
	void setPosition(int x, int y);
	void setPosition(Point p);
	void setArrowKeys(const char* keys);
	void setColor(Color c) {
		color = c;
	}
	void setSign(char c) {
		sign = c;
	}
	randNum* move();
	int getDirection(char key);
	int getDirection();
	void setDirection(int dir) {
		direction = dir;
	}
	char getSign();
	int getSize();
	void setSize(int _size);
	int nextPointY();
	int nextPointX();
	void changeSize(int a);
	bool shoot(char key);
	TheSnakesGame *getGame();
	Point& getLoc();
	void setLoc(Point p);
	void reload();
	void reload(int a);
	void setFreeze(int a);
	bool isFreeze(){
		return freeze;
	}
	void cleanSnakefromGame();
};
#endif