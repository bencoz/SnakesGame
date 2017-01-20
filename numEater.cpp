#include "Cretures.h"
#include "Snake.h"
#include "TheSnakesGame.h"

randNum* numEater::move(){
	Point *target, **arr = nullptr;
	int arrSize;

	randNum* res = nullptr;
	arr = getSolutions(&arrSize);
	if (arr == nullptr)
		return nullptr;
	target = findClosest(arr, arrSize);
	Point NextP = calcRoute(target);
	Snake *s;
	Point p(getLoc());
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
Point numEater::calcRoute(Point *target){
	Point p;
	return p;
}
Point* numEater::findClosest(Point **arr, int size){
	return nullptr;
}