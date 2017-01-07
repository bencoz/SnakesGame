#include "Snake.h"
#include "TheSnakesGame.h"
#include "Bullet.h"


randNum* Bullet::move(){
	randNum* res = nullptr;
	Snake *s;
	Point p(Snake::getLoc());
	Point NextP(Snake::nextPointX(), Snake::nextPointY());

	if (!(theGame->isSpotFree(NextP))){
		wasHit = true;
		res = theGame->isRandNum(NextP);
		if (res == nullptr){//not a rand number -> its a other snake.
			s = theGame->checkSnakeOnBoard(NextP);
			if (s != nullptr){
				if (s != Shooter)
					Shooter->reload();
				s->setFreeze(true);
				s->cleanSnakefromGame();
			}
			else { //spot is not free and is not a number and not a snake -> its another bullet
				if (theGame->checkShootOnBoard(NextP))
					theGame->setBulletHit(NextP);
			}
		}
	}

	theGame->printCharOnBoard(p, ' ');
	p.draw(' ');


	p.move(Snake::getDirection());
	setTextColor(LIGHTRED);
	p.draw(Snake::getSign());
	theGame->printCharOnBoard(p, Snake::getSign());
	Snake::setPosition(p);
	return res;
}