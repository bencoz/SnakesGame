#include "MissionManager.h"
#include "missions.h"

bool biggerThanXandSmallerThanY::isMissionOK(int num) {
	if (num > getX() && num < getY())
		return true;
	else
		return false;
}