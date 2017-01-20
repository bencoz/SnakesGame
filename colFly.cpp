#include "Cretures.h"
#include "Snake.h"
#include "TheSnakesGame.h"

randNum* colFly::move(){
	randNum* res = nullptr;
	Snake *s;
	Point p(getLoc());
	Point NextP(nextPointX(), nextPointY());
	if (!wallMover){
		if (NextP.getY() == 23){
			NextP.set(NextP.getX(), 5);
			this->setDirection(DOWN);
		}
		else if (NextP.getY() == 4){
			NextP.set(NextP.getX(), 22);
			this->setDirection(UP);
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
				if (getTheGame()->checkShootOnBoard(NextP)){
					wasHit = true;
					getTheGame()->setBulletHit(NextP);
				}
				/*else{
				getTheGame()->checkCreatureOnBoard(NextP);
				}*/
			}
		}
	}
	getTheGame()->printCharOnBoard(p, ' ');
	p.draw(' ');

	p.move(getDirection());
	setTextColor(WHITE);
	p.draw(getSign());
	getTheGame()->printCharOnBoard(p, getSign());
	setPosition(p);
	return res;
}