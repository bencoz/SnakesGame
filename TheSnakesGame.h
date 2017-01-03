#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#define _CRT_SECURE_NO_WARNINGS
#include "io_utils.h"
#include "Snake.h"
#include "Screen.h"
#include "mission.h"


class randNum;
enum { ROWS = 24, COLS = 80 };
enum { ESC = 27 };
class Mission;
class Screen;

class TheSnakesGame {
	Screen *screen;
	Mission *mission;
	Snake** s;
	randNum** randNumbers;
	static int randNumSize;
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	static unsigned int clock;
public:
	TheSnakesGame();
	~TheSnakesGame();
	bool isNotFree(const Point& p);
	void setBoard(const char* boardToCopy[ROWS]);
	void init();
	void run();
	bool printRandNum(randNum* s);
	void deleteNumFromBoard(int x, int y, int len);
	void printSnakeOnBoard(int x, int y, char ch);
	void deleteHalfofRandNum(randNum**);
	void lookForAns(randNum**);
	void swapRandNum(randNum** arr, int a, int b);
	void TheSnakesGame::AfterMissionBoard();
	void TheSnakesGame::clearHalfRow();
	void printClock();
	void TheSnakesGame::resetSize();
	void printRandNumers(randNum** arr);
	void printGoodJob();
	void printNoTime();
	void changeMission();
	bool isSnake(const Point& p);
	void clearConsoleAndBoard();
	void swapRandNum(randNum a, randNum b);
	void printRelevant(char *MissionName, int player1, int player2);
	char TheSnakesGame::BeginScreenSwitch();
	char TheSnakesGame::PauseScreenSwitch();
	void TheSnakesGame::resetPosAndDir();
	void deleteAllRandNum(randNum**);
	BOOL TheSnakesGame::checkLoseOrWin(int size);
	void restartClock(){
		gotoxy(66,0);
		cout << "    ";
		clock = 0;
		
	}
	randNum* isRandNum(const Point& p);
};

#endif