#ifndef _SCREEN_H_
#define _SCREEN_H_

using namespace std;

#include "TheSnakesGame.h"

class Screen {
	//enum {Begin_Screen, Pause_Screen, Instructions_Screen};

public:
	int Begin_Screen();
	int Pause_Screen();
	void Instructions_Screen();
	void Clear_Screen();
};


#endif