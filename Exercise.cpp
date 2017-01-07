#include "Exercise.h"

enum { DECIMAL = 10 };

Exercise::Exercise() {
	int blankSpot;
	op1 = RandomOp();
	op2 = RandomOp();
	nums[3] = calculateExc(op1, op2);
	blankSpot = rand() % 3;
	if (blankSpot == 0)
		answer = nums[0];
	else if (blankSpot == 1)
		answer = nums[1];
	else if (blankSpot == 2)
		answer = nums[2];
	else
		answer = nums[3];
}

void Exercise::printExc() {
	if (answer == nums[0])
		cout << "_" << op1 << nums[1] << op2 << nums[2] << "=" << nums[3];
	else if (answer == nums[1])
		cout << nums[0] << op1 << "_" << op2 << nums[2] << "=" << nums[3];
	else if (answer == nums[2])
		cout << nums[0] << op1 << nums[1] << op2 << "_" << "=" << nums[3];
	else
		cout << nums[0] << op1 << nums[1] << op2 << nums[2] << "=" << "_";
}

int Exercise::Random() {
	return (rand() % 169) + 1;
}

char Exercise::RandomOp() {
	int op = rand() % 4;
	if (op == 0)
		return '+';
	else if (op == 1)
		return '-';
	else if (op == 2)
		return '*';
	else
		return '/';
}

void Exercise::specialRandom(int&num1, int& num2) {
	do {
		num2 = (rand() % num1) + 1;
	} while (num1%num2 != 0);
}

int Exercise::calculateExc(const char& op1, const char& op2) {
	int num4 = 0;
	int tmp;
	do {
		nums[0] = Random();
		nums[1] = Random();
		nums[2] = Random();
		if (op1 == '/' && op2 == '/')
		{
			specialRandom(nums[0], nums[1]);
			tmp = nums[0] / nums[1];
			specialRandom(tmp, nums[2]);
		}
		else if (op1 == '/')
			specialRandom(nums[0], nums[1]);
		else if (op2 == '/')
			specialRandom(nums[1], nums[2]);
		if ((op1 == '+' || op1 == '-') && (op2 != '+' && op2 != '-'))
		{
			num4 = correctOpOrder(nums[0], nums[1], nums[2], op1, op2, true);
		}
		else if ((op2 == '+' || op2 == '-') && (op1 != '+' && op1 != '-'))
		{
			num4 = correctOpOrder(nums[2], nums[0], nums[1], op2, op1, false);
		}
		else {
			num4 = checkOp(op1, nums[0], nums[1]);
			num4 = checkOp(op2, num4, nums[2]);
		}
	} while (num4 < 0 || num4>169);
	return num4;
}

int Exercise::checkOp(const char& op, const int& num1, const int& num2) {
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

int Exercise::correctOpOrder(const int& num1, const int &num2, const int& num3, const char&op1, const char&op2, bool flag) {
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