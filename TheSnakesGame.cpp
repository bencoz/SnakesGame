#include "TheSnakesGame.h"
#include "randNum.h"

TheSnakesGame::TheSnakesGame()
{
	s = new Snake*[2];
	s[0] = new Snake(3, Point(10, 9), Color::LIGHTGREEN);
	s[1] = new Snake(3, Point(70, 9), Color::LIGHTBLUE, 2, '#');
	randNumbers = new randNum*[60];
	//s[1] = new Snake (*s[0]);
	//*s[1] = *s[0];
}
TheSnakesGame::~TheSnakesGame()
{
	delete s[0];
	delete s[1];
	delete[] s;
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
		/*if (isRandNum(board[p.getY()][p.getX()]){
			val = getValue(board[p.getY()][p.getX()]);
			if (missionOK(val))
				restart;
		}*/
		return true;
	}
}

void TheSnakesGame::run()
{
	char key = 0;
	int dir,logSize=0, count = 0;
	bool print;
	int num;
	do
	{
		if (_kbhit())
		{
			count++;
			gotoxy(66, 0);
			setTextColor(WHITE);
			cout << count;
			cout.flush();
			if (count % 5 == 0){
				randNumbers[logSize] = new randNum();
				for (int i = 0, print = false; (i < 5) && (print == false); i++)
				{
					if (randNumbers[logSize]->isLocOk(randNumbers[logSize]->getRandX(), randNumbers[logSize]->getNumDig())){
						print = true;
						num = randNumbers[logSize]->getVal();
						if (randNumbers[logSize]->getNumDig() >= 3){
							board[randNumbers[logSize]->getRandY()][randNumbers[logSize]->getRandX()] = (num / 100);
							board[randNumbers[logSize]->getRandY()][randNumbers[logSize]->getRandX() + 1] = (num / 10) % 10;
							board[randNumbers[logSize]->getRandY()][randNumbers[logSize]->getRandX() + 2] = num % 10;
						}
						else if (randNumbers[logSize]->getNumDig() >= 2){
							board[randNumbers[logSize]->getRandY()][randNumbers[logSize]->getRandX()] = (num / 10) % 10;
							board[randNumbers[logSize]->getRandY()][randNumbers[logSize]->getRandX() + 1] = num % 10;
						}
						else
							board[randNumbers[logSize]->getRandY()][randNumbers[logSize]->getRandX()] = num;
						randNumbers[logSize]->draw();
						logSize++;
					}
				}
			}
			key = _getch();
			if ((dir = s[0]->getDirection(key)) != -1)
				s[0]->setDirection(dir);
			else if ((dir = s[1]->getDirection(key)) != -1)
				s[1]->setDirection(dir);
		}
		s[0]->move();
		s[1]->move();
		Sleep(200);
	} while (key != ESC);
}