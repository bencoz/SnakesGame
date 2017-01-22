#include "randNum.h"
#include "TheSnakesGame.h"

randNum::randNum(TheSnakesGame* _theGame) {
	val = setValbyProp();
	thegame = _theGame;
	if (val >= 100)
		numOfDig = 3;
	else if (val >= 10)
		numOfDig = 2;
	solve = checkMission();
	loc.set(rand() % 80, rand() % 18 + 5);

	for (int i = 0; (i < 3) && (isLocOnScreenOk(this) == false); i++)  //tring 3 times to find a place on board
		loc.set(rand() % 80, rand() % 18 + 5);
}


randNum::~randNum() {
	if (print){
		thegame->deleteNumFromBoard(loc, numOfDig);
		gotoxy(loc.getX(), loc.getY());
		for (int i = 0; i < numOfDig; i++)
			cout << ' ';
		cout.flush();
	}
}


void randNum::setGame(TheSnakesGame* _theGame) {
	thegame = _theGame;
}

bool randNum::checkMission(){
	Mission* m;
	m = thegame->getMission();
	if (m->isMissionOK(m->getMissionNum(), val)){
		solve = true;
		return true;
	}
	else{
		solve = false;
		return false;
	}
}

void randNum::draw() {
	setTextColor(WHITE);
	gotoxy(loc.getX(), loc.getY());
	cout << val;
	cout.flush();
}

void randNum::flicker() {
	for (int i = 0; i < 2; i++){
		setTextColor(YELLOW);
		gotoxy(loc.getX(), loc.getY());
		cout << val;
		cout.flush();
		Sleep(1000);
		setTextColor(WHITE);
		gotoxy(loc.getX(), loc.getY());
		cout << val;
		cout.flush();
		Sleep(1000);
	}
}
int randNum::setValbyProp(){
	int num;
	num = rand() % 10;
	if (num < 3)
		num = rand() % 26;
	else if (num < 7)
		num = (rand() % 57) + 25;
	else
		num = (rand() % 88) + 82;
	return num;
}
Point& randNum::getPoint(){
	return loc;
}
Point* randNum::getPointPointer(){
	Point* res = new Point(loc);
	return res;
}

bool randNum::isLocOnScreenOk(const randNum* num) {
	if ((loc.getX() > 76) && (numOfDig >= 3))
		return false;
	else if ((loc.getX() > 77) && (numOfDig >= 2))
		return false;
	else
		return true;
}