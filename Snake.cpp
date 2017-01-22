#include "Snake.h"
#include "TheSnakesGame.h"


randNum* Snake::move(){
	randNum* res = nullptr;
	Point p;
	Point NextP;
	Snake *s = nullptr;
	p = getLoc();
	NextP = p.next(BasicOBJ::getDirection());

	if (!(getTheGame()->isSpotFree(NextP))){
		res = getTheGame()->isRandNum(NextP);
		if (res == nullptr){//not a rand number -> its a other snake.
			s = getTheGame()->checkSnakeOnBoard(NextP);
			if (s != nullptr)
				setDirection(STOP);
			else{ //spot is not free and is not a number and not a snake
				if (getTheGame()->checkShootOnBoard(NextP))
					getTheGame()->setBulletHit(NextP);
				else{
					if (getTheGame()->checkNumEaterOnBoard(NextP)){
						getTheGame()->printNumEaterEnd();
						getTheGame()->refresh();
					}
				}//NumEater
			}//not free, not number, not snake
		}//not free, not number
	}//not free

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
