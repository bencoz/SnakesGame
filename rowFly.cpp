#include "Cretures.h"
#include "Snake.h"
#include "TheSnakesGame.h"

randNum* rowFly::move(){
	randNum* res = nullptr;
	Snake *s;
	Point p(getLoc());
	Point NextP(nextPointX(), nextPointY());
	if (!wallMover){
		if (NextP.getX() == 79){
			NextP.set(1, NextP.getY());
			this->setDirection(RIGHT);
		}
		else if (NextP.getX() == 0){
			NextP.set(78, NextP.getY());
			this->setDirection(LEFT);
		}
	}
	if (!(getTheGame()->isSpotFree(NextP))){
		res = getTheGame()->isRandNum(NextP);
		if (res == nullptr){//not a rand number -> its a other snake.
			s = getTheGame()->checkSnakeOnBoard(NextP);
			if (s != nullptr){
				s->setFreeze(true);
				s->cleanOBJfromGame();
			}
			else { //spot is not free and is not a number and not a snake -> its a bullet
				if (getTheGame()->checkShootOnBoard(NextP))
					getTheGame()->setBulletHit(NextP);
				/*else{
					getTheGame()->checkCreatureOnBoard(NextP);
				}*/
			}
		}
	}
	getTheGame()->printCharOnBoard(p, ' ');
	p.draw(' ');

	p.move(getDirection());
	setTextColor(GREEN);
	p.draw(getSign());
	getTheGame()->printCharOnBoard(p, getSign());
	setPosition(p);
	return res;
}