#ifndef _BULLET_H_
#define _BULLET_H_

#include <iostream>
#include "io_utils.h"
class Snake;

class Bullet : public Snake {
	bool wasHit = false;
	Snake *Shooter = nullptr;
	TheSnakesGame *theGame = nullptr;
public:
	Bullet() : Snake(1, { 0, 0 }, LIGHTRED, STOP, '*') {};
	Bullet(Snake *s) : Snake(1, (s->getLoc()).next(s->getDirection()), LIGHTRED, s->getDirection(), '*') {
		Shooter = s;
		theGame = s->getGame();
	}
	//~Bullet();
	randNum* move();
	void setHit(bool flag){
		wasHit = flag;
	}
	bool hit(){
		return wasHit;
	}
};


#endif