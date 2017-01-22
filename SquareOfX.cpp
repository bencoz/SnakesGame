#include "MissionManager.h"
#include "missions.h"

bool SquareOfX::isMissionOK(int num) {
	if (num == getX()*getX())
		return true;
	else
		return false;
}