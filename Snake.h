#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"

class TheSnakesGame;
class randNum;


class Snake {
	char sign;
	int size;
	Point* body;
	int direction;
	char arrowKeys[4];
	Color color;
	TheSnakesGame* theGame;
public:
	Snake(int size, const Point& position, Color c, int dir = 3, char symb = '@');//c'tor
	~Snake(){ delete[] body; } //d'tor
	Snake(const Snake& s); //copy c'tor

	void setGame(TheSnakesGame* _theGame){
		theGame = _theGame;
	}
	void setPosition(int y, int x);
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}
	void setColor(Color c) {
		color = c;
	}
	void setSign(char c) {
		sign = c;
	}
	randNum* move();
	int getDirection(char key);
	void setDirection(int dir) {
		direction = dir;
	}
	char getSign();
};

#endif