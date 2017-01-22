#include "MissionManager.h"
#include "missions.h"

bool divideByXnotByY::isMissionOK(int num) {
	if (num % getX() == 0 && num % getY() != 0)
		return true;
	else
		return false;
}
