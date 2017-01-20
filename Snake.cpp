#include "Snake.h"
#include "TheSnakesGame.h"


//Snake::Snake(int size, const Point& p, Color c, int dir, char sign) {}
/*Snake::Snake(const Snake& s)
{
	stackSize = s.stackSize;
	freeze = s.freeze;
	for (int i = 0; i < 5; i++){
		arrowKeys[i] = s.arrowKeys[i];
	}
}*/
/*Snake::~Snake(){
	for (int i = 0; i < size; i++)
		theGame->printCharOnBoard(body[i], ' ');
	delete[] body;
}*/

randNum* Snake::move(){
	randNum* res = nullptr;
	Point p;
	Point NextP;
	p = getLoc();
	NextP = p.next(BasicOBJ::getDirection());
	if (!(getTheGame()->isSpotFree(NextP))){
		res = getTheGame()->isRandNum(NextP);
		if (res == nullptr)//not a rand number -> its a other snake.
			setDirection(STOP);
	}
	
	if (BasicOBJ::getDirection() != STOP){
		getTail().draw(' ');
		getTheGame()->printCharOnBoard(getTail(), ' ');
		moveBody();
	}
	getLoc().move(BasicOBJ::getDirection());
	setTextColor(getColor());
	getLoc().draw(getSign());
	getTheGame()->printCharOnBoard(getLoc(), getSign());

	return res;
}

void Snake::reload(){
	stackSize++;
}
void Snake::reload(int a){
	stackSize = a;
}
void Snake::setFreeze(int a){
	a > 0 ? freeze = true : freeze = false;
}

bool Snake::shoot(char key){
	if ((key == arrowKeys[4]) && (stackSize > 0) && (BasicOBJ::getDirection() != STOP)){
		stackSize--;
		getTheGame()->shoot(this);
		return true;
	}
	else return false;
}

void Snake::setArrowKeys(const char* keys) {
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}


int Snake::getDirection(char key)
{
	for (int i = 0; i < 4; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}
