#include "mission.h"
#include "TheSnakesGame.h"

Mission::Mission(int num) {
	int newMiss;
	do {
		newMiss = rand() % 5;
	} while (newMiss == num);
	this->numOfMiss = newMiss;
}

Mission::~Mission() {
	
}
BOOL Mission::isMissionOK(int missionNum, int num){
	if (missionNum == PrimeNumber)
		return Mission::isM1(num);
	else if (missionNum == DividedBy4)
		return Mission::isM2(num);
	else if (missionNum == MultipleBy7)
		return Mission::isM3(num);
	else if (missionNum == PowOf_Znum)
		return Mission::isM4(num);
	else if (missionNum == RestIs3)
		return Mission::isM5(num);
	else if (missionNum == Num169)
		return Mission::isM6(num);
	else
		return 0;
}

BOOL Mission::isM1(int num) {
	int i;
	for (i = 2; i <= num / 2; i++)
		if (num % i == 0)
			return 0;
	return 1;
}

BOOL Mission::isM3(int num) {
	if (num % 7 == 0)
		return 1;
	else 
		return 0;
}

BOOL Mission::isM4(int num) {
	if (num == (int)(sqrt(num)*(int)(sqrt(num))))
		return 1;
	else
		return 0;
}

BOOL Mission::isM2(int num) {
	if (num % 4 == 0)
		return 1;
	else
		return 0;
}

BOOL Mission::isM5(int num) {
	if (num % 7 == 3)
		return 1;
	else
		return 0;
}

BOOL Mission::isM6(int num) {
	if (num == 169)
		return 1;
	else
		return 0;
}