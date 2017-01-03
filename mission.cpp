#include "mission.h"
#include "TheSnakesGame.h"


Mission::Mission(int num) {
	int newMiss;
	do {
		newMiss = rand() % 7;
	} while (newMiss == num);
	numOfMiss = newMiss;
	if (numOfMiss == 6)
		Exc = new Exercise;
}

Mission::~Mission() {
	
}

char *Mission::missionName(int missionNum) {
	switch (missionNum) {
	case(0) :
		return "Prime_Number";
	case(1) :
		return "Divided_By_4";
	case(2) :
		return "Multiple_By_7";
	case(3) :
		return "Sqaure_Of_Z_Num";
	case(4) :
		return "Rest_Is_3";
	case(5) :
		return "Sqaure_Of_13";
	case(6) :
		return Exc->ExcName();
	default:
		return "ERROR";
	}
}

BOOL Mission::isMissionOK(int missionNum, int num){
	if (missionNum == Prime_Number)
		return isM1(num);
	else if (missionNum == Divided_By_4)
		return isM2(num);
	else if (missionNum == Multiple_By_7)
		return isM3(num);
	else if (missionNum == Square_Of_Z_Num)
		return isM4(num);
	else if (missionNum == Rest_Is_3)
		return isM5(num);
	else if (missionNum == Square_Of_13)
		return isM6(num);
	else if (missionNum == exercise)
		return (Exc->isNumCorrect(num));
	else
		return 0;
}

BOOL Mission::isM1(int num) {
	int i;
	for (i = 2; i <= num / 2; i++)
		if (num % i == 0)
			return 0;
	if (num > 1)
		return 1;
	else
		return 0;
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