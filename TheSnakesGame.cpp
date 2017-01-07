#include "TheSnakesGame.h"
#include "randNum.h"

int TheSnakesGame::randNumSize;
unsigned int TheSnakesGame::clock;

TheSnakesGame::TheSnakesGame() //c'tor
{
	s = new Snake*[2];
	s[0] = new Snake(3, Point(10, 9), Color::LIGHTGREEN);
	s[1] = new Snake(3, Point(70, 9), Color::LIGHTBLUE, 2, '#');
	randNumbers = new randNum*[60];
	screen = new Screen;
	mission = new Mission;
}

TheSnakesGame::~TheSnakesGame() //d'tor
{
	delete s[0];
	delete s[1];
	delete[] s;
	delete screen;
	delete mission;
	delete[] randNumbers;
}

void TheSnakesGame::printClock(){
	clock++;
	gotoxy(66, 0);
	setTextColor(WHITE);
	cout << clock;
	cout.flush();
}

void TheSnakesGame::clearHalfRow() {
	for (int i = 0; i < COLS / 2; i++)
	{
		cout << " ";
	}
}

void TheSnakesGame::AfterMissionBoard() { 
	gotoxy(0, 0);
	clearHalfRow();
	clearConsoleAndBoard();
	printRelevant(s[0]->getSize(), s[1]->getSize());
	cout.flush();
	s[0]->setPosition(10, 9);
	s[1]->setPosition(70, 9);
	s[0]->setDirection(3);
	s[1]->setDirection(2);
}

void TheSnakesGame::setBoard(const char* boardToCopy[ROWS])
{
	setTextColor(WHITE);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = boardToCopy[i][j];
			originalBoard[i][j] = board[i][j];
		}
		board[i][COLS] = '\0';
	}
	/*char *missionName;
	missionName = new char[ROWS];
	missionName = mission->missionName(mission->getMissionNum());
	strcpy(board[0], missionName);*/
}
void TheSnakesGame::init()
{
	gotoxy(0, 0);
	mission->printMissionName(mission->getMissionNum())
;	for (int i = 1; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << board[i][j];
			cout.flush();
		}
		board[i][COLS] = '\0';
	}
	s[0]->setGame(this);
	s[1]->setGame(this);
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

void TheSnakesGame::resetSize() {
	s[0]->setSize(3);
	s[1]->setSize(3);
}

void TheSnakesGame::resetPosAndDir() {
	s[0]->setPosition(10, 9);
	s[0]->setDirection(3);
	s[1]->setPosition(70, 9);
	s[1]->setDirection(2);
	s[0]->setGame(this);
	s[1]->setGame(this);
}
randNum* TheSnakesGame::isRandNum(const Point& p) {
	int randNumX, randNumY;
	bool found = false;
	randNum* res = nullptr;
	for (int i = 0; i < randNumSize && !found; i++)
	{
		randNumX = randNumbers[i]->getRandX();
		randNumY = randNumbers[i]->getRandY();
		for (int j = -1; j < 3; j++) {
			if ((randNumX + j == p.getX()) && (randNumY == p.getY())) {// number is on spot
				found = true;
				res = randNumbers[i];
			}
		}
	}
	return res;
}

bool TheSnakesGame::isSnake(const Point& p) {
	if (board[p.getY()][p.getX()] == '@' || board[p.getY()][p.getX()] == '#')
		return true;
	else
		return false;
}

void TheSnakesGame::clearConsoleAndBoard() {
	gotoxy(0, 2);//clears text message and score
	for (int i = 0; i < COLS; i++)
		cout << ' ';
	for (int i = 4; i < ROWS; i++)// clear board and console
	{
		gotoxy(0, i);
		for (int j = 0; j < COLS; j++) {
			cout << ' ';
			board[i][j] = ' ';
		}
	}
}

void TheSnakesGame::swapRandNum(randNum a, randNum b)
{
	randNum temp(a);
	a = b;
	b = temp;
}

void TheSnakesGame::printRandNumers(randNum** arr) {
	for (int i = 0; i < randNumSize; i++)
		printRandNum(arr[i]);
}



void TheSnakesGame::printRelevant(int player1, int player2) {
	setTextColor(WHITE);
	gotoxy(0, 0);
	clearHalfRow();
	gotoxy(0, 0);
	mission->printMissionName(mission->getMissionNum());
	gotoxy(0, 1);
	clearHalfRow();
	gotoxy(0, 1);
	cout << "Press ESC to menu";
	gotoxy(61, 0);
	cout << "TIME:   ";
	gotoxy(66, 0);
	cout << clock;
	gotoxy(56, 1);
	cout << "Player1";
	cout << " | ";
	cout << "Player2";
	gotoxy(59, 2);
	cout << player1;
	gotoxy(69, 2);
	cout << player2;
	gotoxy(0, 3);
	for (int i = 0; i < COLS; i++)
		cout << '+';
}
void TheSnakesGame::printGoodJob() {
	gotoxy(0, 2);
	setTextColor(LIGHTMAGENTA);
	cout << "Good Job !!!";
	Sleep(1000);
}

void TheSnakesGame::printNoTime() {
	gotoxy(0, 2);
	setTextColor(LIGHTMAGENTA);
	cout << "Ran out of time!!!";
	Sleep(1000);
}

void TheSnakesGame::changeMission() {
	int lastMissionNum = mission->getMissionNum();
	delete mission;
	mission = new Mission(lastMissionNum);
}

void TheSnakesGame::swapRandNum(randNum** arr, int a, int b)
{
	randNum* temp;
	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
void TheSnakesGame::deleteHalfofRandNum(randNum** arr)
{
	int del, size = randNumSize / 2;
	for (int i = 0; i < size; i++, randNumSize--)
	{
		del = rand() % randNumSize;
		swapRandNum(arr, randNumSize - 1, del);
		randNumbers[randNumSize - 1]->~randNum();
		delete randNumbers[randNumSize - 1];
	}
}

void TheSnakesGame::deleteAllRandNum(randNum** arr)
{
	int size = randNumSize;
	for (int i = 0; i < size; i++)
	{
		randNumbers[i]->~randNum();
		delete randNumbers[i];
	}
	randNumSize = 0;
}

bool TheSnakesGame::printRandNum(randNum* rand) //print to board and to console | if fails return false
{
	int num, digNum, i;
	num = rand->getVal();
	digNum = rand->getNumDig();
	for (i = -1; i < digNum + 1; i++) //check if there is something(snake/randNum) close (to the left or to the right) on board
	{
		if (board[rand->getRandY()][rand->getRandX() + i] != ' ')
			return false;
	}
	if (digNum == 3) {
		board[rand->getRandY()][rand->getRandX()] = (char)('0' + (num / 100));
		board[rand->getRandY()][rand->getRandX() + 1] = (char)('0'+((num / 10) % 10));
		board[rand->getRandY()][rand->getRandX() + 2] = (char)('0'+(num % 10));
	}
	else if (digNum == 2) {
		board[rand->getRandY()][rand->getRandX()] = (char)('0'+((num / 10) % 10));
		board[rand->getRandY()][rand->getRandX() + 1] = (char)('0'+(num % 10));
	}
	else
		board[rand->getRandY()][rand->getRandX()] = (char)('0'+num);
	rand->draw();
	return true;
}
void TheSnakesGame::printSnakeOnBoard(int x, int y, char ch)
{
	board[y][x] = ch;
}
void TheSnakesGame::deleteNumFromBoard(int x, int y, int len) {
	for (int i = 0; i < len; i++)
		board[y][x + i] = ' ';
}
void TheSnakesGame::lookForAns(randNum** arr)
{
	bool found = false;
	for (int i = 0; i < randNumSize && !found; i++)
	{
		if (mission->isMissionOK(mission->getMissionNum(), arr[i]->getVal()))
		{
			found = true;
			arr[i]->flicker();
		}
	}
	if (!found) {
		gotoxy(0, 2);
		setTextColor(LIGHTMAGENTA);
		cout << "Nice effort but, No solution on screen";
		Sleep(1000);
	}
}



void TheSnakesGame::run()
{
	BOOL finishGame = FALSE;
	randNum* CurrNum;
	char key = 0;
	int dir, count = 0;
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
		if (randNumSize == 60) {
			printNoTime();
			lookForAns(randNumbers);
			changeMission();
			deleteHalfofRandNum(randNumbers);
			AfterMissionBoard();
			printRandNumers(randNumbers);
			key = 0;
		}
		CurrNum = s[0]->move();
		if (CurrNum != nullptr) {
			if (mission->isMissionOK(mission->getMissionNum(), CurrNum->getVal())) {
				printGoodJob();
				s[0]->changeSize(1);
			}
			else {
				s[1]->changeSize(1);
				lookForAns(randNumbers);
			}
			deleteHalfofRandNum(randNumbers);
			changeMission();
			AfterMissionBoard();
			printRandNumers(randNumbers);
			key = 0;
		}
		CurrNum = s[1]->move();
		if (CurrNum != nullptr) {
			if (mission->isMissionOK(mission->getMissionNum(), CurrNum->getVal())) {
				printGoodJob();
				s[1]->changeSize(1);
			}
			else {
				lookForAns(randNumbers);
				s[0]->changeSize(1);
			}
			deleteHalfofRandNum(randNumbers);
			changeMission();
			AfterMissionBoard();
			printRandNumers(randNumbers);
			key = 0;
		}
		if (s[0]->getSize() == 12 || s[0]->getSize() == 0)
		{
			gotoxy(0, 2);
			cout << "Player1 ";
			finishGame = checkLoseOrWin(s[0]->getSize());
			Sleep(1000);
			key = BeginScreenSwitch();
		}
		else if (s[1]->getSize() == 12 || s[1]->getSize() == 0)
		{
			gotoxy(0, 2);
			cout << "Player2 ";
			finishGame = checkLoseOrWin(s[1]->getSize());
			Sleep(1000);
			key = BeginScreenSwitch();
		}
		Sleep(100);
		if (key == ESC && finishGame == FALSE) {
			key = PauseScreenSwitch();
		}//if
		if (key == 1)
		{
			restartClock();
			finishGame = FALSE;
		}
	} while (key != ESC);
}

BOOL TheSnakesGame::checkLoseOrWin(int size) {
	if (size == 0)
		cout << "has Lost! Good Game";
	else
		cout << "has Won! Good Game";
	Sleep(1000);
	return TRUE;
}
char TheSnakesGame::PauseScreenSwitch() {
	char key;
	switch (screen->Pause_Screen()) {
	case(1) :
		//exit the prog
		return ESC;
		break;
	case(2) :
		//BeginScreenMenu
		key = BeginScreenSwitch();
		break;
	case(3) :
		//resume game
		clearConsoleAndBoard();
		printRelevant(s[0]->getSize(), s[1]->getSize());
		printRandNumers(randNumbers);
		key = 0;
		break;
	case(4) :
		//restart current mission
		clearConsoleAndBoard();
		resetPosAndDir();
		printRelevant(s[0]->getSize(), s[1]->getSize());
		restartClock();
		key = 0;
		break;
	case(5) :
		//start new mission
		clearConsoleAndBoard();
		changeMission();
		resetPosAndDir();
		printRelevant(s[0]->getSize(), s[1]->getSize());
		key = 0;
		break;
	case(6) :
		//restart game
		clearConsoleAndBoard();
		deleteAllRandNum(randNumbers);
		resetSize();
		resetPosAndDir();
		printRelevant(3, 3);
		key = 1;
		break;
	}//switch
	return key;
}

char TheSnakesGame::BeginScreenSwitch() {
	char key;
	do {
		switch (screen->Begin_Screen()) {
		case(1) :
			//show instructions
			screen->Instructions_Screen();
			key = 0;
			break;
		case(2) :
			//start new game
			clearConsoleAndBoard();
			deleteAllRandNum(randNumbers);
			restartClock();
			resetSize();
			resetPosAndDir();
			printRelevant(3, 3);
			key = 1;
			break;
		case(9) :
			//Exit game
			key = ESC;
			break;
		}
	} while (key == 0);
	return key;
}