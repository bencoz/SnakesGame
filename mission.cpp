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

void Mission::printMissionName(int missionNum) {
	switch (missionNum) {
	case(0) :
		cout << "Prime_Number";
		break;
	case(1) :
		cout << "Divided_By_4";
		break;
	case(2) :
		cout << "Multiple_By_7";
		break;
	case(3) :
		cout << "Sqaure_Of_Z_Num";
		break;
	case(4) :
		cout << "Rest_Is_3";
		break;
	case(5) :
		cout << "Sqaure_Of_13";
		break;
	case(6) :
		Exc->printExc();
		break;
	default:
		cout << "ERROR";
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