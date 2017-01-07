#ifndef _EXERCISE_H_
#define _EXERCISE_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>


using namespace std;

class Exercise {
	int nums[4], answer;
	char op1, op2;
public:
	Exercise();
	void printExc();
	int Random();
	char RandomOp();
	void specialRandom(int&num1, int& num2);
	int calculateExc(const char& op1, const char& op2);
	int checkOp(const char& op, const int& num1, const int& num2);
	int correctOpOrder(const int& num1, const int &num2, const int& num3, const char&op1, const char&op2, bool flag);
	bool isNumCorrect(int num) {
		if (num == answer)
			return true;
		else
			return false;
	}
};


#endif