#include "TheSnakesGame.h"
#include "randNum.h"
#include "Bullet.h"
#include "Cretures.h"
#include "Replay.h"

int TheSnakesGame::randNumSize;
unsigned int TheSnakesGame::clock;

TheSnakesGame::TheSnakesGame() //c'tor
{
	snakes = new Snake*[2];
	snakes[0] = snakes[1] = nullptr;
	randNumbers = new randNum*[60];
	stack = new Bullet*[gameStackPhSize];
	creatures = new BasicOBJ*[5];
	screen = new Screen;
	missions = new MissionManager*[missStackPhSize];
	rep = new Replay;
}

TheSnakesGame::~TheSnakesGame() //d'tor
{
	delete[] snakes;
	delete screen;
	delete[] randNumbers;
	delete[] stack;
	delete[] creatures;
	delete[]missions;
	delete rep;
	gotoxy(0, 0);
}

void TheSnakesGame::createSnakes() {
	snakes[0] = new Snake(3, { 10, 9 }, Color::LIGHTGREEN, 3, '@');
	snakes[1] = new Snake(3, { 70, 9 }, Color::LIGHTBLUE, 2, '#');
}

void TheSnakesGame::killMissions() {
	for (int i = 0; i < missStackLogSize; i++)
		delete missions[i];
}

void TheSnakesGame::killSnakes() {
	for (int i = 0; i < 2; i++)
		delete snakes[i];
}

void TheSnakesGame::killAllOBJS() {
	killSnakes();
	killMissions();
	deleteAllRandNum(randNumbers);
	clearBulletsFromGame();
	killCreatures();
}

void TheSnakesGame::killCreatures() {
	for (int i = 0; i < 5; ++i)
		delete creatures[i];
}


bool TheSnakesGame::readingMissions() {
	char identifer, dummy;
	ifstream read;
	MissionManager **newmissions;
	if (difficulty == '1')
		read.open("easyMissions.txt");
	else if (difficulty == '2')
		read.open("mediumMissions.txt");
	else
		read.open("hardMissions.txt");
	if (read.good())
	{
		do
		{
			read.get(identifer);
			read.get(dummy);
			missionCreator(read, identifer, missStackLogSize);
			missStackLogSize++;
			if (missStackLogSize == missStackPhSize)
			{
				missStackPhSize *= 2;
				newmissions = new MissionManager*[missStackPhSize];
				for (int i = 0; i < missStackLogSize; i++)
					newmissions[i] = missions[i];
				delete missions;
				missions = newmissions;
			}
			read.get(dummy);
		} while (read.good());
	}
	else
	{
		clearConsoleAndBoard();
		gotoxy(0, 3);
		clearHalfRow();
		gotoxy(0, 0);
		cout << "File not found, try a different difficulty level!" << endl;
		Sleep(2000);
		read.close();
		return false;
	}
	read.close();
	return true;
}

void TheSnakesGame::missionCreator(ifstream& file, char identifer, int pos) {
	int a, b;
	char *description = new char[50];
	file >> description >> a >> b;
	switch (identifer) {
	case('A') :
		missions[pos] = new divideByXnotByY(description, a, b);
		break;
	case('B') :
		missions[pos] = new biggerThanXandSmallerThanY(description, a, b);
		break;
	case('C') :
		missions[pos] = new dividedByX(description, a, b);
		break;
	case('D') :
		missions[pos] = new Equation(description, a, b);
		break;
	case('E') :
		missions[pos] = new SquareOfX(description, a, b);
		break;
	}
}

void TheSnakesGame::checkSolveForAll(){
	for (int i = 0; i < randNumSize; i++){
		if (randNumbers[i]->checkMission())
			randNumbers[i]->setSolve(true);
		else
			randNumbers[i]->setSolve(false);
	}
}

Point** TheSnakesGame::getSolvers(int *size) {
	Point **res = nullptr;
	*size = 0;
	int i, write, mySize = 0;
	for (i = 0; i < randNumSize; i++) {
		if (*randNumbers[i]->getSolve())
			mySize++;
	}
	if (mySize == 0)
		return res;
	else
		res = new Point*[mySize];
	for (i = 0, write = 0; i < randNumSize; i++) {
		if (*randNumbers[i]->getSolve()) {
			res[write] = randNumbers[i]->getPointPointer();
			write++;
		}
	}
	*size = mySize;
	return res;
}

void TheSnakesGame::realaseSolvers(Point **arr, int size) {
	for (int i = 0; i < size; i++)
		delete arr[i];
	delete arr;
}

void TheSnakesGame::printCharOnBoard(const Point& p, char ch){
	board[p.getY()][p.getX()] = ch;
	rep->addChange(p, ch);
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
	for (int i = 0; i < gameStackLogSize; i++)
		delete stack[i];
	gameStackLogSize = 0;
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
				myswap(stack[i], stack[gameStackLogSize - 1]);
				delete stack[gameStackLogSize - 1];
				gameStackLogSize--;

			}
		}
	}
}

void TheSnakesGame::creaturesMove() {
	randNum* num;
	for (int i = 0; i < 5; ++i) {
		if (creatures[i] != nullptr) { // creature is not dead
			if (typeid(creatures[i]) == typeid(numEater*) || typeid(creatures[i]) == typeid(rowFly*)) { // creatures who is moving twice
				num = creatures[i]->move();
				if (num != nullptr)
					deleteRandNum(num);
			}//move twice
			num = creatures[i]->move();
			if (num != nullptr)
				deleteRandNum(num);
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

bool TheSnakesGame::checkNumEaterOnBoard(Point p) {
	char ch;
	ch = board[p.getY()][p.getX()];
	return (ch == '%' ? true : false);
}

void TheSnakesGame::setBulletHit(Point p,int flag){
	int pos = -1; 
	for (int i = 0; i < gameStackLogSize; i++)
	{
		if (stack[i]->getLoc() == p)
			pos = i;
	}
	if (pos != -1) {
		stack[pos]->setHit(true);
		if (flag)
			stack[pos]->getShooter()->reload();
	}
}

bool TheSnakesGame::setCreatureHit(Point p) {
	bool res = false;
	numEater* a;
	colFly* b;
	for (int i = 0; i < 5; i++) {
		if (creatures[i]) {
			if (creatures[i]->getLoc() == p) {
				if (a = dynamic_cast<numEater*>(creatures[i])) {
					a->setHit(true);
					res = true;
				}
				if (b = dynamic_cast<colFly*>(creatures[i])) {
					b->setHit(true);
					res = true;
				}
			}
		}
	}
	return res;
}

void TheSnakesGame::destroyHitBullets(){
	for (int i = 0; i < gameStackLogSize; i++)
	{
		if (stack[i]->hit()){
			stack[i]->cleanOBJfromGame();
			myswap(stack[i], stack[gameStackLogSize - 1]);
			delete stack[gameStackLogSize - 1];
			gameStackLogSize--;
		}
	}
}

void TheSnakesGame::destroyHitCreatures() {
	colFly* a;
	numEater* b;
	int pos = -1;
	for (int i = 0; i < 5; ++i, pos = -1) {
		if (creatures[i]) {
			a = dynamic_cast<colFly*>(creatures[i]);
			if (a) {
				if (*a->hit())
					pos = i;
			}
			b = dynamic_cast<numEater*>(creatures[i]);
			if (b) {
				if (*b->hit())
					pos = i;
			}
		}
		if (pos != -1) {
			delete creatures[pos];
			creatures[pos] = nullptr;
		}
	}
}
void TheSnakesGame::reviveCreatures() {
	for (int i = 0; i < 5; i++) {
		if (creatures[i] == nullptr)
			switch (i) {
			case(0) :
				creatures[0] = new numEater();
				break;
			case(1) :
				creatures[1] = new rowFly({ 30, 23 }, RIGHT, true);
				break;
			case(2) :
				creatures[2] = new rowFly({ 50, 15 }, LEFT);
				break;
			case(3) :
				creatures[3] = new colFly({ 25, 23 }, UP);
				break;
			case(4) :
				creatures[4] = new colFly({ 55, 15 }, DOWN, true);
			}
		creatures[i]->setGame(this);
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
	missions[missPos]->printDescript();
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
	createSnakes();
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
	if (snakes[0] != nullptr && snakes[1] != nullptr){
		snakes[0]->setSize(3);
		snakes[1]->setSize(3);
	}
}

void TheSnakesGame::resetPosAndDir() {
	if (snakes[0] != nullptr && snakes[1] != nullptr){
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
	missions[missPos]->printDescript();
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

void TheSnakesGame::printNumEaterEnd() {
	gotoxy(0, 2);
	setTextColor(LIGHTMAGENTA);
	cout << "you can't F*** with NumEater !!!";
	Sleep(1000);
}

void TheSnakesGame::changeMission() {
	int lastMissionPos = missPos;
	do {
		missPos = rand() % missStackLogSize;
	} while (lastMissionPos == missPos);
}

void TheSnakesGame::deleteHalfofRandNum(randNum** arr)
{
	int del, size = (randNumSize / 2);
	for (int i = 0; i < size; i++, randNumSize--)
	{
		del = rand() % randNumSize;
		myswap(randNumbers[randNumSize - 1], randNumbers[del]);
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
		rep->addChange({ rand->getRandX(), rand->getRandY() }, (char)('0' + (num / 100)));
		board[rand->getRandY()][rand->getRandX() + 1] = (char)('0' + ((num / 10) % 10));
		rep->addChange({ rand->getRandX() + 1, rand->getRandY() }, (char)('0' + ((num / 10) % 10)));
		board[rand->getRandY()][rand->getRandX() + 2] = (char)('0' + (num % 10));
		rep->addChange({ rand->getRandX() + 2, rand->getRandY() }, (char)('0' + (num % 10)));
	}
	else if (digNum == 2) {
		board[rand->getRandY()][rand->getRandX()] = (char)('0' + ((num / 10) % 10));
		rep->addChange({ rand->getRandX(), rand->getRandY() }, (char)('0' + ((num / 10) % 10)));
		board[rand->getRandY()][rand->getRandX() + 1] = (char)('0' + (num % 10));
		rep->addChange({ rand->getRandX() + 1, rand->getRandY() }, (char)('0' + (num % 10)));
	}
	else {
		board[rand->getRandY()][rand->getRandX()] = (char)('0' + num);
		rep->addChange({ rand->getRandX(), rand->getRandY() }, (char)('0' + num));
	}
	rand->draw();
	return true;
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
		if (missions[missPos]->isMissionOK(arr[i]->getVal()))
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
	reviveCreatures();
	deleteHalfofRandNum(randNumbers);
	AfterMissionBoard();
	printRandNumers(randNumbers);
	Sleep(1000);
	rep->saveState(board);
}

void TheSnakesGame::run()
{
	BOOL finishGame = false, flag = false;
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
		creaturesMove();
		destroyHitCreatures();
		if (randNumSize >= 60) { //end of mission - lack of time
			printNoTime();
			lookForAns(randNumbers);
			refresh();
		}
		if (!(snakes[0]->isFreeze()))
			CurrNum = snakes[0]->move();
		if (CurrNum != nullptr) {
			if (missions[missPos]->isMissionOK(CurrNum->getVal())) {
				printGoodJob();
				snakes[0]->changeSize(1);
			}
			else {
				snakes[1]->changeSize(1);
				lookForAns(randNumbers);
			}
			try {
				if (_kbhit())
					key = _getch();
				throw key;
			}
			catch (char ch) {
				if (ch == ESC)
					key = PauseScreenSwitch();
				if (key == ESC)
					return;
			}
			if (!finishGame)
				refresh();
		}
		if (!(snakes[1]->isFreeze()))
			CurrNum = snakes[1]->move();
		if (CurrNum != nullptr) {
			if (missions[missPos]->isMissionOK(CurrNum->getVal())) {
				printGoodJob();
				snakes[1]->changeSize(1);
			}
			else {
				lookForAns(randNumbers);
				snakes[0]->changeSize(1);
			}
			try {
				if (_kbhit())
					key = _getch();
				throw key;
			}
			catch (char ch) {
				if (ch == ESC)
					key = PauseScreenSwitch();
				if (key == ESC)
					return;
			}
			if (!finishGame)
				refresh();
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
	case(7) :
		//replay last mission
		clearConsoleAndBoard();
		printRelevant(snakes[0]->getSize(), snakes[1]->getSize());
		printRandNumers(randNumbers);
		rep->startReplay();
		rep->waitForReturn();
		key = 0;
		break;
	}//switch
	return key;
}

char TheSnakesGame::BeginScreenSwitch() {
	char key;
	bool flag = true;
	do {
		switch (screen->Begin_Screen()) {
		case(1) :
			//show instructions
			screen->Instructions_Screen();
			key = 0;
			break;
		case(2) :
			//start new game
			chooseDifficulty();
			flag = readingMissions();
			if (flag)
			{
				clearConsoleAndBoard();
				deleteAllRandNum(randNumbers);
				restartClock();
				resetSize();
				resetPosAndDir();
				printRelevant();
				rep->saveState(board);
				key = 1;
			}
			else
				key = 0;
			break;
		case(9) :
			//Exit game
			key = ESC;
			break;
		}
	} while (key == 0);
	return key;
}

void TheSnakesGame::chooseDifficulty() {
	gotoxy(0, 0);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < COLS; j++)
			cout << " ";
	gotoxy(0, 0);
	cout << "Choose difficulty:" << endl;
	cout << "For easy level press 1" << endl;
	cout << "For medium level press 2" << endl;
	cout << "For hard level press 3" << endl;
	difficulty = _getch();
	while (int(difficulty - '0') < 1 || int(difficulty - '0') > 3)
	{
		difficulty = _getch();
		cout << "Invalid input, try again please" << endl;
	}
}