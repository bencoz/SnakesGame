#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#define _CRT_SECURE_NO_WARNINGS
#include "io_utils.h"
#include "Snake.h"
#include "Screen.h"
#include "mission.h"

class Bullet;
class randNum;
enum { ROWS = 24, COLS = 80 };
enum { ESC = 27 };
class Mission;
class Screen;

class TheSnakesGame {
	Screen *screen;
	Mission *mission;
	Snake **snakes;
	Bullet **stack;
	randNum** randNumbers;
	BasicOBJ **creatures;
	int gameStackLogSize=0, gameStackPhSize=1;
	static int randNumSize;
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	static unsigned int clock;
public:
	TheSnakesGame();
	~TheSnakesGame();
	bool isSpotFree(const Point& p);
	void setBoard(const char* boardToCopy[ROWS]);
	void init();
	void run();
	bool printRandNum(randNum* s);
	void deleteNumFromBoard(Point& p, int len);
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
	void printRelevant(int player1, int player2);
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
	void refresh(); // this function changes mission, deleting half of the rand nums, cleaning board and reprinting.
	void printCharOnBoard(const Point& p, char ch);
	void printCharOnConsole(const Point& p, char ch);
	void shoot(Snake *s);
	void shootsMove();
	void deleteRandNum(randNum *num);
	void swapBulletinStack(int a, int b);
	Snake *checkSnakeOnBoard(Point);
	void unFreezeSnake(Snake* s);
	void clearBulletsFromGame();
	bool checkShootOnBoard(Point p);
	void setBulletHit(Point p);
	void destroyHitBullets();
	Mission* getMission(){
		return mission;
	}
	void checkSolveForAll();
	void creaturesCreator();
	Point** getSolvers(int *size);
};

template<class T>
void myswap(T& a, T&b){
	T temp = a;
	a = b;
	b = temp;
}

#endif