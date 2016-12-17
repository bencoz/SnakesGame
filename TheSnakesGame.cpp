#include "TheSnakesGame.h"
#include "randNum.h"

int TheSnakesGame::randNumSize;
unsigned int TheSnakesGame::clock;

TheSnakesGame::TheSnakesGame()
{
	s = new Snake*[2];
	s[0] = new Snake(3, Point(10, 9), Color::LIGHTGREEN);
	s[1] = new Snake(3, Point(70, 9), Color::LIGHTBLUE, 2, '#');
	randNumbers = new randNum*[60];
	screen = new Screen;
	mission = new Mission;
}

TheSnakesGame::~TheSnakesGame()
{
	delete s[0];
	delete s[1];
	delete[] s;
}

void TheSnakesGame::printClock(){
	clock++;
	gotoxy(66, 0);
	setTextColor(WHITE);
	cout << clock;
	cout.flush();
}


void TheSnakesGame::setBoard(const char* boardToCopy[ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}
void TheSnakesGame::init()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << originalBoard[i][j];
			cout.flush();
			board[i][j] = originalBoard[i][j];
		}
		board[i][COLS] = '\0';
	}
	s[0]->setGame(this);
	s[1]->setGame(this);
/*	s[0]->setColor(YELLOW);
	s[1]->setColor(LIGHTBLUE);*/
	s[0]->setArrowKeys("wxad");
	s[1]->setArrowKeys("8246");
}

bool TheSnakesGame::isNotFree(const Point& p)
{
	if (board[p.getY()][p.getX()] == ' ')
		return false;
	else
		return true;
}

randNum* TheSnakesGame::isRandNum(const Point& p) {
	int randNumX, randNumY;
	bool found = false;
	randNum* res;
	for (int i = 0; i < randNumSize && !found; i++)
	{
		randNumX = randNumbers[i]->getRandX();
		randNumY = randNumbers[i]->getRandY();
		for (int j = -1; j < 3; j++) {
			if ((randNumX + j == p.getX()) && (randNumY == p.getY())) {// number is right on spot
				found = true;
				res = randNumbers[i];
			}
		}
	}
	if (found)
		return res;
	else
		return nullptr;
}


bool TheSnakesGame::printRandNum(randNum* rand) //print to board and to console | if fails return false
{
	int num, digNum, i;
	num = rand->getVal();
	digNum = rand->getNumDig();

	for (i = 0; i < digNum; i++) {//check if there is something on board
		if (board[rand->getRandY()][rand->getRandX() + i] != ' ')
			return false;
	}

	if (digNum >= 3) {
		board[rand->getRandY()][rand->getRandX()] = (num / 100);
		board[rand->getRandY()][rand->getRandX() + 1] = (num / 10) % 10;
		board[rand->getRandY()][rand->getRandX() + 2] = num % 10;
	}
	else if (digNum >= 2) {
		board[rand->getRandY()][rand->getRandX()] = (num / 10) % 10;
		board[rand->getRandY()][rand->getRandX() + 1] = num % 10;
	}
	else
		board[rand->getRandY()][rand->getRandX()] = num;
	rand->draw();
	return true;
}

void TheSnakesGame::run()
{
	randNum* CurrNum;
	char key = 0;
	int dir, count =0;
	do
	{
		if (_kbhit())
		{
			printClock();
			if (count % 5 == 0) {
				randNumbers[randNumSize] = new randNum(this);
				if (TheSnakesGame::printRandNum(randNumbers[randNumSize]))
					randNumSize++;
				else
					delete randNumbers[randNumSize];
			}
			count++;
			key = _getch();
			if ((dir = s[0]->getDirection(key)) != -1)
				s[0]->setDirection(dir);
			else if ((dir = s[1]->getDirection(key)) != -1)
				s[1]->setDirection(dir);
		}
		CurrNum = s[0]->move();
		CurrNum = s[1]->move();
		Sleep(200);
		if (key == ESC) {
			switch (screen->Pause_Screen()) {
			case(1) :
				//exit the prog
				break;
			case(2) :
				//go to start menu
				screen->Begin_Screen();
				break;
			case(3) : 
				TheSnakesGame::init();
				TheSnakesGame::run();
				break;
			case(4) :
				//restart current mission

				break;
			case(5) :
				//start new mission

				mission = new Mission(mission->getMissionNum());
				key = 0;
				break;
			case(6) :
				//restart game
				break;
			}//switch
		}//if
	} while (key != ESC);
}