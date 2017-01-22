#ifndef _BULLET_H_
#define _BULLET_H_

#include <iostream>
#include "io_utils.h"
class Snake;

class Bullet : public BasicOBJ {
	bool wasHit = false;
	Snake *Shooter = nullptr;
public:
	Bullet() : BasicOBJ(1, { 0, 0 }, LIGHTRED, STOP, '*') {};
	Bullet(Snake *s) : BasicOBJ(1, (s->getLoc()), LIGHTRED, s->BasicOBJ::getDirection(), '*') {
		Shooter = s;
	}
	//~Bullet();
	virtual randNum* move();
	void setHit(bool flag){
		wasHit = flag;
	}
	bool hit(){
		return wasHit;
	}
	Snake* const getShooter(){
		return Shooter;
	}
};


#endif