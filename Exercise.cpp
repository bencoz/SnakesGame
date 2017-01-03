#include "Exercise.h"

enum { DECIMAL = 10 };

Exercise::Exercise() {
	int blankSpot;
	do {
		nums[0] = Random();
		nums[1] = Random();
		nums[2] = Random();
		op1 = RandomOp();
		op2 = RandomOp();
		nums[3] = calculateExc(nums[0], nums[1], nums[2], op1, op2);
	} while (nums[3] > 169 || nums[3] < 0);
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

char *Exercise::ExcName() {
	char *res;
	int i, phSize=2, logSize=2,size;
	res = new char[phSize];
	res[0] = '\0';
	for (i = 0; i < 4;i++) {
		if (nums[i] == answer)
		{
			if (phSize == logSize)
			{
				changeSizes(phSize, &logSize, &res);
				phSize++;
				strcat(res, "_");
			}//inner if
			else
				strcat(res, "_");
		}//num==answer
		else
		{
			if (phSize == logSize)
			{
				changeSizes(phSize, &logSize, &res);
				phSize += theSizeOf(nums[i]);
				addNumtoRes(&res, nums[i]);
			}//inner if
			else
			{
				phSize += theSizeOf(nums[i]);
				addNumtoRes(&res, nums[i]);
			}
		}//num!=answer
		if (phSize == logSize)
		{
			changeSizes(phSize, &logSize, &res);
			phSize++;
			addOpToRes(&res, i);
		}
		else 
		{
			phSize++;
			addOpToRes(&res, i);
		}
	}//for
	return res;
}//ExcName

void Exercise::addOpToRes(char **res, int num) {
	if (num == 0)
		strcat(*res, &op1);
	else if (num == 1)
		strcat(*res, &op2);
	else
		strcat(*res, "=");
}

int Exercise::theSizeOf(int num) {
	if (num > 99)
		return 3;
	else if (num > 9)
		return 2;
	else
		return 1;
}

void Exercise::addNumtoRes(char **res, int num) {
	char *copy;
	copy = new char[theSizeOf(num)];
	_itoa(num, copy, DECIMAL);
	strcat(*res, copy);
	delete[]copy;
}

void Exercise::changeSizes(int phSize, int *logSize, char **res) {
	
	int lgSize = *logSize;
	char * copy=new char[phSize];
	strcpy(copy, *res);
	lgSize *= 2;
	delete[] * res;
	*res = new char[lgSize];
	strcpy(*res, copy);
	*logSize = lgSize;
	delete[]copy;
	
}

int Exercise::Random() {
	return rand() % 169;
}

char Exercise::RandomOp() {
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

int Exercise::checkOp(const char& op, const int& num1, const int& num2) {
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

int Exercise::correctOpOrder(const int& num1, const int &num2, const int& num3, const char&op1, const char&op2) {
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