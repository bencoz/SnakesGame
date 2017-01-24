#ifndef _MISSION_MANAGER_H_
#define _MISSION_MANAGER_H_
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
#include <string>
#include <string.h> 
#include <iostream>
#include <fstream>
#include <iomanip>

class MissionManager {
	char *description;
	int X, Y;
public:
	MissionManager(char *_description,int _X, int _Y);
	virtual ~MissionManager() { delete description; };
	int getX() { return X; };
	int getY() { return Y; };
	void setX(int num) { X = num; };
	void setY(int num) { Y = num; };
	virtual void printDescript();
	virtual bool isMissionOK(int num) { return false; };
};

#endif