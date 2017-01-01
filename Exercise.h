#ifndef _EXERCISE_H_
#define _EXERCISE_H_

#include <iostream>
#include <string.h>

using namespace std;

class Exercise {
	int num1, num2, num3, num4, answer;
	char op1, op2;
public:
	Exercise();
	int calculateExc(const int& num1, const int& num2, const int& num3, const char& op1, const char& op2);
	char *ExcName(const int& num1, const int& num2, const int& num3,const int& num4, const char& op1, const char& op2,const int& answer);
	bool isNumCorrect(int num) {
		if (num == answer)
			return true;
		else
			return false;
	}
};


#endif