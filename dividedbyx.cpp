#include "MissionManager.h"
#include "missions.h"

bool dividedByX::isMissionOK(int num) {
	if (num % getX() == 0)
		return true;
	else
		return false;
}