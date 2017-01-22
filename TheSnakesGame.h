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
class Replay;

class TheSnakesGame {
	Replay* rep;
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
	void deleteHalfofRandNum(randNum**);
	void lookForAns(randNum**);
	void AfterMissionBoard();
	void clearHalfRow();
	void printClock();
	void resetSize();
	void printRandNumers(randNum** arr);
	void printGoodJob();
	void printNumEaterEnd();
	void printNoTime();
	void changeMission();
	bool isSnake(const Point& p);
	void clearConsoleAndBoard();
	void printRelevant(int player1, int player2);
	char BeginScreenSwitch();
	char PauseScreenSwitch();
	void resetPosAndDir();
	void deleteAllRandNum(randNum**);
	BOOL checkLoseOrWin(int size);
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
	void creaturesMove();
	void deleteRandNum(randNum *num);
	Snake *checkSnakeOnBoard(Point);
	void unFreezeSnake(Snake* s);
	void clearBulletsFromGame();
	bool checkShootOnBoard(Point p);
	bool checkNumEaterOnBoard(Point p);
	void setBulletHit(Point p, int flag=0); // if flag > 0 then shooter gets a realod
	bool setCreatureHit(Point p); // returns true if the creature was hit otherwise false.
	void destroyHitBullets();
	void destroyHitCreatures();
	void reviveCreatures();
	Mission* getMission(){
		return mission;
	}
	void checkSolveForAll();
	void creaturesCreator();
	Point** getSolvers(int *size);
	void realaseSolvers(Point **arr, int size);
	void killAllOBJS();
	void killCreatures();
};

template<class T>
void myswap(T& a, T&b){
	T temp = a;
	a = b;
	b = temp;
}

#endif