#include "TheSnakesGame.h"
#include "randNum.h"
#include "Bullet.h"
#include "Cretures.h"

int TheSnakesGame::randNumSize;
unsigned int TheSnakesGame::clock;

TheSnakesGame::TheSnakesGame() //c'tor
{
	snakes = new Snake*[2];
	snakes[0] = new Snake(3, { 10, 9 }, Color::LIGHTGREEN,3,'@');
	snakes[1] = new Snake(3, { 70, 9 }, Color::LIGHTBLUE, 2, '#');
	randNumbers = new randNum*[60];
	stack = new Bullet*[gameStackPhSize];
	creatures = new BasicOBJ*[5];
	screen = new Screen;
	mission = new Mission;
}

TheSnakesGame::~TheSnakesGame() //d'tor
{
	delete snakes[0];
	delete snakes[1];
	delete[] snakes;
	delete screen;
	delete mission;
	delete[] randNumbers;
	delete[] stack;
	delete[] creatures;
}

void TheSnakesGame::checkSolveForAll(){
	for (int i = 0; i < randNumSize; i++){
		if (randNumbers[i]->checkMission())
			randNumbers[i]->setSolve(true);
		else
			randNumbers[i]->setSolve(false);
	}
}

Point** TheSnakesGame::getSolvers(int *size){
	Point **res;
	size = 0;
	for (int i = 0; i < randNumSize; i++){
		if (randNumbers[i]->getSolve()){
			size++;
			//res = new Point*[size]
		}
	}
	return res;
}

void TheSnakesGame::printCharOnBoard(const Point& p, char ch){
	board[p.getY()][p.getX()] = ch;
}
void TheSnakesGame::printCharOnConsole(const Point& p, char ch){
	gotoxy(p.getX(), p.getY());
	cout << ch;
	cout.flush();
}
void TheSnakesGame::deleteRandNum(randNum *num){
	bool found = false;
	for (int i = 0; i < 60 && !found; i++){
		if (randNumbers[i] == num){
			found = true;
			myswap(randNumbers[randNumSize - 1], randNumbers[i]);
			randNumbers[randNumSize - 1]->~randNum();
			delete randNumbers[randNumSize - 1];
			randNumSize--;
		}
	}
}

void TheSnakesGame::clearBulletsFromGame(){
	for (int i = 0; i < gameStackLogSize; i++){
		stack[i]->cleanOBJfromGame();
		delete stack[i];
	}
	gameStackLogSize = 0;
}
void TheSnakesGame::swapBulletinStack(int a, int b){
	Bullet *temp;
	temp = stack[a];
	stack[a] = stack[b];
	stack[b] = temp;
}
void TheSnakesGame::shootsMove(){
	randNum* num = nullptr;
	for (int j = 0; j < 2; j++){
		for (int i = 0; i < gameStackLogSize; i++){
			num = stack[i]->move();
			if (stack[i]->hit()){
				if (num != nullptr){
					deleteRandNum(num);
					num = nullptr;
				}
				stack[i]->cleanOBJfromGame();
				myswap(stack[i], stack[gameStackLogSize - 1]);
				delete stack[gameStackLogSize - 1];
				gameStackLogSize--;

			}
		}
	}
}

void TheSnakesGame::shoot(Snake *s){
	Bullet **newstack;
	if (gameStackLogSize == gameStackPhSize){
		gameStackPhSize *= 2;
		newstack = new Bullet*[gameStackPhSize];
		for (int i = 0; i < gameStackLogSize; i++)
			newstack[i] = stack[i];
		delete stack;
		stack = newstack;
	}

	stack[gameStackLogSize++] = new Bullet(s);
	stack[gameStackLogSize - 1]->setGame(this);
}

Snake* TheSnakesGame::checkSnakeOnBoard(Point p){
	char ch;
	ch = board[p.getY()][p.getX()];
	if (ch == snakes[0]->getSign())
		return snakes[0];
	else if (ch == snakes[1]->getSign())
		return snakes[1];
	else
		return nullptr;
}

bool TheSnakesGame::isSnake(const Point& p) {
	if (board[p.getY()][p.getX()] == snakes[0]->getSign() || board[p.getY()][p.getX()] == snakes[1]->getSign())
		return true;
	else
		return false;
}

bool TheSnakesGame::checkShootOnBoard(Point p){
	char ch;
	ch = board[p.getY()][p.getX()];
	return (ch == '*' ? true : false);
}

void TheSnakesGame::setBulletHit(Point p){
	int pos = -1; 
	for (int i = 0; i < gameStackLogSize; i++)
	{
		if (stack[i]->getLoc() == p)
			pos = i;
	}
	if (pos != -1)
		stack[pos]->setHit(true);
}

void TheSnakesGame::destroyHitBullets(){
	for (int i = 0; i < gameStackLogSize; i++)
	{
		if (stack[i]->hit()){
			stack[i]->cleanOBJfromGame();
			swapBulletinStack(i, gameStackLogSize - 1);
			delete stack[gameStackLogSize - 1];
			gameStackLogSize--;
		}
	}
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
	printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
	cout.flush();
	clearBulletsFromGame();
	resetPosAndDir();
}

void TheSnakesGame::setBoard(const char* boardToCopy[ROWS])
{
	setTextColor(WHITE);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			board[i][j] = boardToCopy[i][j];
		board[i][COLS] = '\0';
	}
}
void TheSnakesGame::init()
{
	gotoxy(0, 0);
	mission->printMissionName(mission->getMissionNum());
	for (int i = 1; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			cout << board[i][j];
			cout.flush();
		}
		board[i][COLS] = '\0';
	}
	snakes[0]->setGame(this);
	snakes[1]->setGame(this);
	snakes[0]->setArrowKeys("wxadz");
	snakes[1]->setArrowKeys("imjln");
	creaturesCreator();
}

void TheSnakesGame::creaturesCreator(){
	creatures[0] = new numEater();
	creatures[1] = new rowFly({ 30, 23 },RIGHT,true);
	creatures[2] = new rowFly({ 50, 15 },LEFT);
	creatures[3] = new colFly({ 25, 23 },UP);
	creatures[4] = new colFly({ 55, 15 },DOWN,true);
	for (int i = 0; i < 5; i++)
		creatures[i]->setGame(this);
}

bool TheSnakesGame::isSpotFree(const Point& p)
{
	if (board[p.getY()][p.getX()] == ' ')
		return true;
	else
		return false;
}

void TheSnakesGame::resetSize() {
	snakes[0]->setSize(3);
	snakes[1]->setSize(3);
}

void TheSnakesGame::resetPosAndDir() {
	snakes[0]->setPosition(10, 9);
	snakes[0]->setDirection(3);
	snakes[1]->setPosition(70, 9);
	snakes[1]->setDirection(2);
	snakes[0]->setGame(this);
	snakes[1]->setGame(this);
	snakes[0]->setFreeze(false);
	snakes[1]->setFreeze(false);
	snakes[0]->reload(5);
	snakes[1]->reload(5);
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



void TheSnakesGame::clearConsoleAndBoard() {
	gotoxy(0, 0);
	clearHalfRow();//clear mission name
	gotoxy(0, 1);
	clearHalfRow();//clear 2nd row.
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

void TheSnakesGame::printRandNumers(randNum** arr) {
	for (int i = 0; i < randNumSize; i++)
		printRandNum(arr[i]);
}



void TheSnakesGame::printRelevant(int player1, int player2) {
	setTextColor(WHITE);
	gotoxy(0, 0);
	mission->printMissionName(mission->getMissionNum());
	gotoxy(61, 0);
	cout << "TIME:     ";
	gotoxy(66, 0);
	cout << clock;
	gotoxy(0, 1);
	cout << "Press ESC to menu";
	gotoxy(56, 1);
	cout << "Player1 | Player2";
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
	int del, size = (randNumSize / 2);
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
	for (int i = 0; i < randNumSize; i++)
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
		if ((rand->getRandX() == 0) && i == -1)// edge case of being on the left end of screen
			i = 0;
		if ((i == digNum) && (board[rand->getRandY()][rand->getRandX() + i] == '\0')) //edge case of being on the right end of screen
			break;
		else if (board[rand->getRandY()][rand->getRandX() + i] != ' ')
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
void TheSnakesGame::deleteNumFromBoard(Point& p, int len) {
	for (int i = 0; i < len; i++)
		board[p.getY()][p.getX() + i] = ' ';
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

void TheSnakesGame::unFreezeSnake(Snake* s){
	Point p(rand() % 80, (rand() % 20) + 4);
	while (!(isSpotFree(p)))
		p.set(rand() % 80, (rand() % 20) + 4);
	s->setFreeze(false);
	s->setPosition(p);
}

void TheSnakesGame::refresh(){
	changeMission();
	checkSolveForAll();
	deleteHalfofRandNum(randNumbers);
	AfterMissionBoard();
	printRandNumers(randNumbers);
}
void TheSnakesGame::run()
{
	BOOL finishGame = FALSE;
	randNum* CurrNum = nullptr;
	char key = 0;
	int dir, count = 0, freeze1 = 0, freeze2 = 0;
	do
	{
		if (_kbhit())
		{
			printClock();
			if (count % 5 == 0) {
				randNumbers[randNumSize] = new randNum(this);
				if (TheSnakesGame::printRandNum(randNumbers[randNumSize])){
					randNumbers[randNumSize]->setPrint();
					randNumSize++;
				}
				else{
					randNumbers[randNumSize]->~randNum();
					delete randNumbers[randNumSize];
				}
			}
			count++;
			key = _getch();
			if ((dir = snakes[0]->getDirection(key)) != -1)
				snakes[0]->setDirection(dir);
			else if ((dir = snakes[1]->getDirection(key)) != -1)
				snakes[1]->setDirection(dir);
			snakes[0]->shoot(key);
			snakes[1]->shoot(key);
			if (snakes[0]->isFreeze()){
				freeze1++;
				if (freeze1 == 25){
					snakes[0]->setFreeze(false);
					unFreezeSnake(snakes[0]);
				}
			}
			else
				freeze1 = 0;
			if (snakes[1]->isFreeze()){
				freeze2++;
				if (freeze2 == 25){
					snakes[1]->setFreeze(false);
					unFreezeSnake(snakes[1]);
				}
			}
			else
				freeze2 = 0;
		}
		shootsMove();
		destroyHitBullets();
		for (int i = 1; i < 5; i++){
			CurrNum = creatures[i]->move();
			if (CurrNum != nullptr){
				deleteRandNum(CurrNum);
				CurrNum = nullptr;
				}
		}
		if (randNumSize >= 60) { //end of mission - lack of time
			printNoTime();
			lookForAns(randNumbers);
			refresh();
			key = 0;
		}
		if (!(snakes[0]->isFreeze()))
			CurrNum = snakes[0]->move();
		if (CurrNum != nullptr) {
			if (mission->isMissionOK(mission->getMissionNum(), CurrNum->getVal())) {
				printGoodJob();
				snakes[0]->changeSize(1);
			}
			else {
				snakes[1]->changeSize(1);
				lookForAns(randNumbers);
			}
			refresh();
			key = 0;
		}
		if (!(snakes[1]->isFreeze()))
			CurrNum = snakes[1]->move();
		if (CurrNum != nullptr) {
			if (mission->isMissionOK(mission->getMissionNum(), CurrNum->getVal())) {
				printGoodJob();
				snakes[1]->changeSize(1);
			}
			else {
				lookForAns(randNumbers);
				snakes[0]->changeSize(1);
			}
			refresh();
			key = 0;
		}
		if (snakes[0]->getSize() == 12 || snakes[1]->getSize() == 12) // someone win
		{
			gotoxy(0, 2);
			cout << "Player";
			if (snakes[0]->getSize() == 12){
				cout << "1 ";
				finishGame = checkLoseOrWin(snakes[0]->getSize());
			}
			else {
				cout << "2 ";
				finishGame = checkLoseOrWin(snakes[1]->getSize());
			}
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
		printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
		printRandNumers(randNumbers);
		key = 0;
		break;
	case(4) :
		//restart current mission
		clearConsoleAndBoard();
		deleteAllRandNum(randNumbers);
		clearBulletsFromGame();
		resetPosAndDir();
		printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
		restartClock();
		key = 0;
		break;
	case(5) :
		//start new mission
		clearConsoleAndBoard();
		deleteAllRandNum(randNumbers);
		clearBulletsFromGame();
		changeMission();
		checkSolveForAll();
		resetPosAndDir();
		printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
		key = 0;
		break;
	case(6) :
		//restart game
		clearConsoleAndBoard();
		deleteAllRandNum(randNumbers);
		clearBulletsFromGame();
		resetSize();
		resetPosAndDir();
		printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
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
			printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
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