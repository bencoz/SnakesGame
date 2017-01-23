#include "MissionManager.h"

class divideByXnotByY : public MissionManager {
public:
	divideByXnotByY(char *_description, int _X, int _Y) : MissionManager(_description, _X, _Y) {
		while (getX() % getY() == 0)
			setY(rand() % (_Y - _X) + _X);
	};
	virtual bool isMissionOK(int num);
};

class biggerThanXandSmallerThanY : public MissionManager {
public:
	biggerThanXandSmallerThanY(char *_description, int _X, int _Y) : MissionManager(_description, _X, _Y) {
		if (getX() > getY())
		{
			int tmp = getX();
			setX(getY());
			setY(tmp);
		}
	};
	virtual bool isMissionOK(int num);
};

class dividedByX : public MissionManager {
public:
	dividedByX(char *_description, int _X, int _Y) : MissionManager(_description, _X, _Y) {};
	virtual bool isMissionOK(int num);
};

class Equation : public MissionManager {
	int Z, answer;
	char op1 = NULL, op2 = NULL;
public:
	Equation(char *_description, int _X, int _Y);
	int correctOpOrder(const int& num1, const int &num2, const int& num3, const char&op1, const char&op2, bool flag);
	int checkOp(const char& op, const int& num1, const int& num2);
	int calculateEq(const char& op1, const char& op2);
	void specialRandom(int num1, int num2);
	virtual bool isMissionOK(int num);
	virtual void printDescript();
};

class SquareOfX : public MissionManager {
public:
	SquareOfX(char *_description, int _X, int _Y) : MissionManager(_description, _X, _Y) {};
	virtual bool isMissionOK(int num);

};
