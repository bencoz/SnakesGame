#include "Cretures.h"
#include "Snake.h"
#include "TheSnakesGame.h"

randNum* numEater::move(){
	Point *target, **arr = nullptr;
	int arrSize;
	randNum* res = nullptr;

	Point p(getLoc());
	arr = getSolutions(&arrSize);

	if (arr == nullptr){// no solutions just draw and return
		getTheGame()->printCharOnBoard(p, getSign());
		setTextColor(YELLOW);
		p.draw(getSign());
		return nullptr;
	}
	if (*hit())
		return nullptr;

	target = findClosest(arr, arrSize);
	setDirection(calcRoute(target));

	Point NextP(nextPointX(), nextPointY());
	Snake *s;
	if (!(getTheGame()->isSpotFree(NextP))){
		res = getTheGame()->isRandNum(NextP);
		if (res == nullptr){//not a rand number -> its a other snake.
			s = getTheGame()->checkSnakeOnBoard(NextP);
			if (s != nullptr){
				getTheGame()->printNumEaterEnd();
				getTheGame()->refresh();
			}
			else { //spot is not free and is not a number and not a snake -> its a bullet
				if (getTheGame()->checkShootOnBoard(NextP)){
					wasHit = true;
					getTheGame()->setBulletHit(NextP,1);
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
	setTextColor(YELLOW);
	p.draw(getSign());
	getTheGame()->printCharOnBoard(p, getSign());
	setPosition(p);
	return res;
}

Point** numEater::getSolutions(int *size){
	Point **res;
	res = getTheGame()->getSolvers(size);
	return res;
}
Direction numEater::calcRoute(Point *target){
	int x1, x2, x3, y1, y2, y3, minx,miny;
	Direction res;
	x1 = abs(target->getX() - getLoc().getX());
	x2 = abs(getLoc().getX() + 79 - target->getX());
	x3 = abs(79 - getLoc().getX() + target->getX());
	y1 = abs(target->getY() - getLoc().getY());
	y2 = abs(getLoc().getY() - 4 + 23 - target->getY());
	y3 = abs(23 - getLoc().getY() + target->getY());
	minx = min(min(x1, x2), x3);
	miny = min(min(y1, y2), y3);
	if (minx > miny){ // 
		if (minx == x1){ // going in x filed
			if (target->getX() - getLoc().getX() > 0)
				res = RIGHT;
			else
				res = LEFT;
		}
		if (minx == x2)
			res = LEFT;
		if (minx == x3)
			res = RIGHT;
	}
	else{ /// going in y field
		if (miny == y1){
			if (target->getY() - getLoc().getY() > 0)
				res = DOWN;
			else
				res = UP;
		}
		if (miny == y2)
			res = UP;
		if (miny == y3)
			res = DOWN;
	}
	delete target;
	return res;
}

Point* numEater::findClosest(Point **arr, int size){
	int x1, x2, x3, y1, y2, y3, minx, miny, newx, newy, loc = 0;
	Point *res;
	x1 = abs(arr[0]->getX() - getLoc().getX());
	x2 = abs(getLoc().getX() + 79 - arr[0]->getX());
	x3 = abs(79 - getLoc().getX() + arr[0]->getX());
	y1 = abs(arr[0]->getY() - getLoc().getY());
	y2 = abs(getLoc().getY()-4 + 23 - arr[0]->getY());
	y3 = abs(23 - getLoc().getY() + arr[0]->getY());
	minx = min(min(x1, x2), x3);
	miny = min(min(y1, y2), y3);
	for (int i = 0; i < size; i++){
		x1 = abs(arr[i]->getX() - getLoc().getX());
		x2 = abs(getLoc().getX() + 79 - arr[i]->getX());
		x3 = abs(79 - getLoc().getX() + arr[i]->getX());
		y1 = abs(arr[i]->getY() - getLoc().getY());
		y2 = abs(getLoc().getY() - 4 + 23 - arr[i]->getY());
		y3 = abs(23 - getLoc().getY() + arr[i]->getY());
		newx = min(min(x1, x2), x3);
		newy = min(min(y1, y2), y3);
		if (miny + minx > newx + newy){
			miny = newy;
			minx = newx;
			loc = i;
		}
	}
	res = new Point(*arr[loc]);
	getTheGame()->realaseSolvers(arr, size);
	return res;
}