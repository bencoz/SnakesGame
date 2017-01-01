#include "Exercise.h"

enum { DECIMAL = 10 };

Exercise::Exercise() {
	int blankSpot;
	do {
		num1 = Random();
		num2 = Random();
		num3 = Random();
		op1 = RandomOp();
		op2 = RandomOp();
		num4 = calculateExc(num1, num2, num3, op1, op2);
	} while (answer > 169 || answer < 0);
	blankSpot = rand() % 3;
	if (blankSpot == 0)
		answer = num1;
	else if (blankSpot == 1)
		answer = num2;
	else if (blankSpot == 2)
		answer = num3;
	else
		answer = num4;
}

char *Exercise::ExcName(const int& num1, const int& num2, const int& num3, const int& num4, const char& op1, const char& op2, const int& answer) {
	char *res;
	char *num = new char[2];
	itoa(num1, num, DECIMAL);

	
}

int Random() {
	return rand() % 169;
}

char RandomOp() {
	int op = rand() % 4;
	if (op == 0)
		return '+';
	else if (op == 1)
		return '-';
	else if (op == 2)
		return '*';
	else if (op == 3)
		return '/';
	else
		return '%';
}

int Exercise::calculateExc(const int& num1, const int& num2, const int& num3, const char& op1, const char& op2) {
	int num4 = 0;
	if (op1 == '+' || op1 == '-' && op2 != '+' &&op2 != '-')
	{
		num4 = correctOpOrder(num1, num2, num3, op1, op2);
	}
	else if (op2 == '+' || op2 == '-' && op1 != '+' &&op1 != '-')
	{
		num4 = correctOpOrder(num1, num2, num3, op2, op1);
	}
	else {
		num4 = checkOp(op1, num1, num2);
		num4 = checkOp(op2, num4, num3);
	}
	return num4;
}

int checkOp(const char& op, const int& num1, const int& num2) {
	int res;
	if (op == '+')
		res = num1 + num2;
	else if (op == '-')
		res = num1 - num2;
	else if (op == '*')
		res = num1*num2;
	else if (op == '/')
		res = num1 / num2;
	else if (op == '%')
		res = num1%num2;
	return res;
}

int correctOpOrder(const int& num1, const int &num2, const int& num3, const char&op1, const char&op2) {
	int res;
	if (op2 == '*')
		res = num2*num3;
	else if (op2 == '/')
		res = num2 / num3;
	else
		res = num2%num3;
	if (op1 == '+')
		res += num1;
	else
		res -= num1;
	return res;
}