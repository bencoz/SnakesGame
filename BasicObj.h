#ifndef _BASICOBJ_H_
#define _BASICOBJ_H_
#include "randNum.h"
#include "Point.h"
class TheSnakesGame;

class BasicOBJ {
	char sign;
	int size;
	int direction;
	Point* body;
	Color color;
	TheSnakesGame* theGame;
public:
	BasicOBJ(int _size = 1, const Point& position = { 0, 5 }, Color c = BROWN, int dir = 3, char symb = '@');//c'tor
	virtual ~BasicOBJ(){ delete[] body; } //d'tor
	BasicOBJ(const BasicOBJ& obj); //copy c'tor
	virtual randNum* move() = 0;
	void setGame(TheSnakesGame* _theGame){
		theGame = _theGame;
	}
	int getDirection();
	void setDirection(int dir) {
		direction = dir;
	}
	void setColor(Color c) {
		color = c;
	}
	Color getColor(){
		return color;
	}
	char getSign();
	void setSign(char c) {
		sign = c;
	}
	void setPosition(int x, int y);
	void setPosition(Point p);
	Point& getLoc();
	Point& getTail();
	int getSize();
	void setSize(int _size);
	int nextPointY();
	int nextPointX();
	void changeSize(int a);
	void moveBody();
	void cleanOBJfromGame();
	TheSnakesGame* getTheGame(){ return theGame; }
	//virtual void move();
};


#endif