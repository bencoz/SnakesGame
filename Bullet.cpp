#include "Snake.h"
#include "TheSnakesGame.h"
#include "Bullet.h"

randNum* Bullet::move(){
	randNum* res = nullptr;
	Snake *s;
	Point p(getLoc());
	Point NextP(nextPointX(), nextPointY());

	if (!(getTheGame()->isSpotFree(NextP))){
		wasHit = true;
		res = getTheGame()->isRandNum(NextP);
		if (res == nullptr){//not a rand number -> its a other snake.
			s = getTheGame()->checkSnakeOnBoard(NextP);
			if (s != nullptr){
				if (s != Shooter)
					Shooter->reload();
				s->setFreeze(true);
				s->cleanOBJfromGame();
			}
			else { //spot is not free and is not a number and not a snake -> its another bullet
				if (getTheGame()->checkShootOnBoard(NextP))
					getTheGame()->setBulletHit(NextP);
				else{
					if(getTheGame()->setCreatureHit(NextP))
						Shooter->reload();
				}
			}
		}
	}
	if (Shooter->getLoc() != p){
		getTheGame()->printCharOnBoard(p, ' ');
		p.draw(' ');
	}

	p.move(getDirection());
	setTextColor(LIGHTRED);
	p.draw(getSign());
	getTheGame()->printCharOnBoard(p, getSign());
	setPosition(p);
	return res;
}