#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#define _CRT_SECURE_NO_WARNINGS
#include "io_utils.h"
#include "Snake.h"
#include "Screen.h"
#include "missions.h"
#include "MissionManager.h"

class Bullet;
class randNum;
enum { ROWS = 24, COLS = 80 };
enum { ESC = 27 };
class MissionManager;
class Screen;
class Replay;

class TheSnakesGame {
	Replay *rep;
	MissionManager **missions;
	Screen *screen;
	Snake **snakes;
	Bullet **stack;
	randNum** randNumbers;
	BasicOBJ **creatures;
	int gameStackLogSize = 0, gameStackPhSize = 1, missPos = 0, missStackLogSize = 0, missStackPhSize = 1;
	static int randNumSize;
	char difficulty, board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
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
	void printNoTime();
	void printNumEaterEnd();
	void changeMission();
	bool isSnake(const Point& p);
	void clearConsoleAndBoard();
	void printRelevant(int player1=3, int player2=3);
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
	void setBulletHit(Point p,int flag =0);
	bool setCreatureHit(Point p);
	void destroyHitBullets();
	void destroyHitCreatures();
	void reviveCreatures();
	MissionManager* getMission(){
		return missions[missPos];
	}
	void checkSolveForAll();
	void creaturesCreator();
	Point** getSolvers(int *size);
	void realaseSolvers(Point **arr, int size);
	void killAllOBJS();
	void killCreatures();
	bool readingMissions(); 
	void missionCreator(ifstream& file, char identifer,int pos);
	void chooseDifficulty();
	void createSnakes();
	void killSnakes();
	void killMissions();
};

template<class T>
void myswap(T& a, T&b){
	T temp = a;
	a = b;
	b = temp;
}

#endif