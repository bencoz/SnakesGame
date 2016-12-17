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
	int val;
	if (board[p.getY()][p.getX()] == ' ')
		return false;
	else
	{
		/*for (int i = 0; i < randNumSize; i++)
		{
			if ((randNumbers[i]->getRandX() == p.getX()) && (randNumbers[i]->getRandY() == p.getY()))
				return;
		}
		if (isRandNum(board[p.getY()][p.getX()]){
			val = getValue(board[p.getY()][p.getX()]);
			if (missionOK(val))
				restart;
		}*/
		return true;
	}
}

bool TheSnakesGame::printRandNum(randNum* rand) // to board and to console
{
	int i, num;
	bool print = false;
	for (i = 0; (i < 5) && (print == false); i++)
	{
		if (rand->isLocOk(rand->getRandX(), rand->getNumDig())){
			print = true;
			num = rand->getVal();
			if (rand->getNumDig() >= 3){
				board[rand->getRandY()][rand->getRandX()] = (num / 100);
				board[rand->getRandY()][rand->getRandX() + 1] = (num / 10) % 10;
				board[rand->getRandY()][rand->getRandX() + 2] = num % 10;
			}
			else if (rand->getNumDig() >= 2){
				board[rand->getRandY()][rand->getRandX()] = (num / 10) % 10;
				board[rand->getRandY()][rand->getRandX() + 1] = num % 10;
			}
			else
				board[rand->getRandY()][rand->getRandX()] = num;
			rand->draw();
		}
	}
	if (print)
		return true;
	else
		return false;
}


void TheSnakesGame::run()
{
	char key = 0;
	int dir, count =0;
	do
	{
		if (_kbhit())
		{
			printClock();
			if (count % 5 == 0) {
				randNumbers[randNumSize] = new randNum();
				if (TheSnakesGame::printRandNum(randNumbers[randNumSize]))
					randNumSize++;
			}
			count++;
			key = _getch();
			if ((dir = s[0]->getDirection(key)) != -1)
				s[0]->setDirection(dir);
			else if ((dir = s[1]->getDirection(key)) != -1)
				s[1]->setDirection(dir);
		}
		s[0]->move();
		s[1]->move();
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