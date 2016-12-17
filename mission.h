#ifndef _MISSION_H_
#define _MISSION_H_

#include <string.h> 
#include "Point.h"

using namespace std;


class TheSnakesGame;

class Mission {
	enum {PrimeNumber, DividedBy4, MultipleBy7, PowOf_Znum, RestIs3, Num169};
	TheSnakesGame * theGame;
	int numOfMiss;
public:
	Mission(int num);
	Mission() {
		this->numOfMiss = rand() % 5;
	}
	~Mission();
	int getMissionNum() {
		return numOfMiss;
	}
	BOOL isMissionOK(int missionNum, int num);
	BOOL isM1(int num);
	BOOL isM2(int num);
	BOOL isM3(int num);
	BOOL isM4(int num);
	BOOL isM5(int num);
	BOOL isM6(int num);
};
#endif