#include "MissionManager.h"
#include "missions.h"

Equation::Equation(char *_description, int _X, int _Y) : MissionManager(_description, _X, _Y) {
	int i;
	Z = rand() % (_Y - _X) + _X;
	for (i = 0; i < strlen(_description); i++)
		if (_description[i] == '+' || _description[i] == '-' || _description[i] == '*' || _description[i] == '/')
		{
			if (op1 == NULL)
				op1 = _description[i];
			else
			op2 = _description[i];
		}
	answer = calculateEq(op1, op2);
}

void Equation::specialRandom(int num1, int num2) {
	do {
		setY((rand() % num1) + 1);
	} while (getY() % num2 != 0);
}

int Equation::calculateEq(const char& op1, const char& op2) {
	int num4 = 0;
	int tmp;
	while (getX()*getY() > 169)
	{
		setX(rand() % ((getY() - getX()) / 2) + getX() / 2);
		setX(rand() % ((getY() - getX()) / 2) + getX() / 2);
	}
	do {
		if (op1 == '/' && op2 == '/')
		{
			specialRandom(getX(), getY());
			tmp = getX() / getY();
			specialRandom(tmp, Z);
		}
		else if (op1 == '/')
			specialRandom(getX(), getY());
		else if (op2 == '/')
			specialRandom(getY(), Z);
		if ((op1 == '+' || op1 == '-') && (op2 != '+' && op2 != '-'))
		{
			num4 = correctOpOrder(getX(), getY(), Z, op1, op2, true);
		}
		else if ((op2 == '+' || op2 == '-') && (op1 != '+' && op1 != '-'))
		{
			num4 = correctOpOrder(Z, getX(), getY(), op2, op1, false);
		}
		else {
			num4 = checkOp(op1, getX(), getY());
			num4 = checkOp(op2, num4, Z);
		}
	} while (num4 < 0 || num4>169);
	return num4;
}

int Equation::checkOp(const char& op, const int& num1, const int& num2) {
	int res = 0;
	if (op == '+')
		res = num1 + num2;
	else if (op == '-')
		res = num1 - num2;
	else if (op == '*')
		res = num1*num2;
	else
		res = num1 / num2;
	return res;
}

int Equation::correctOpOrder(const int& num1, const int &num2, const int& num3, const char&op1, const char&op2, bool flag) {
	int res = 0;
	if (op2 == '*')
		res = num2*num3;
	else
		res = num2 / num3;
	if (op1 == '+')
		res += num1;
	else
	{
		if (flag)
			res = num1 - res;
		else
			res -= num1;
	}
	return res;
}

bool Equation::isMissionOK(int num) {
	if (num == answer)
		return true;
	else
		return false;
}

void Equation::printDescript() {
	cout << getX() << op1 << getY() << op2 << Z << "=_";
}