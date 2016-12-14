#include "randNum.h"


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
bool randNum::isLocOk(int x, int numOfDig) {
	if ((numOfDig >= 3) && (x > 76))
		return false;
	else if ((numOfDig >= 2) && (x > 77))
		return false;
	else
		return true;
}
