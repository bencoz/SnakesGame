#ifndef _MISSION_H_
#define _MISSION_H_
#define _CRT_SECURE_NO_WARNINGS

#include <string.h> 
#include "Point.h"
#include "Exercise.h"

using namespace std;


class TheSnakesGame;
class Exercise;

class Mission {
	enum {Prime_Number, Divided_By_4, Multiple_By_7, Square_Of_Z_Num, Rest_Is_3, Square_Of_13, exercise};
	TheSnakesGame * theGame;
	int numOfMiss;
	Exercise *Exc;
public:
	Mission(int num);
	Mission() {
		numOfMiss = rand() % 7;
		if (numOfMiss == 6)
			Exc = new Exercise;
	}
	~Mission();
	int getMissionNum() {
		return numOfMiss;
	}
	char * missionName(int missionNum);
	BOOL isMissionOK(int missionNum, int num);
	BOOL isM1(int num);
	BOOL isM2(int num);
	BOOL isM3(int num);
	BOOL isM4(int num);
	BOOL isM5(int num);
	BOOL isM6(int num);
};
#endif