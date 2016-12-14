#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "io_utils.h"
#include "Snake.h"
class randNum;
enum { ROWS = 24, COLS = 80 };

class TheSnakesGame {
	enum {ESC = 27};
	Snake** s;
	randNum** randNumbers;
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
public:
	TheSnakesGame();
	~TheSnakesGame();
	bool isNotFree(const Point& p);
	void setBoard(const char* boardToCopy[ROWS]);
	void init();
	void run();
};

#endif