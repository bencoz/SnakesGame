#include "Snake.h"
#include "TheSnakesGame.h"


Snake::Snake(int size, const Point& position, Color c, int dir, char symb)
{
	setSign(symb);
	direction = dir;
	setColor(c);
	this->size = size;
	body = new Point[size];
	for (int i = 0; i < size; i++)
		body[i] = position;
}

Snake::Snake(const Snake& s)
{
	setColor(s.color);
	size = s.size;
	body = new Point[size];
	for (int i = 0; i < size; i++)
	{
		body[i] = s.body[i];
	}
}

/*Snake::~Snake(){
	for (int i = 0; i < size; i++)
		theGame->printCharOnBoard(body[i], ' ');
	delete[] body;
}*/
void Snake::setPosition(int x, int y)
{
	for (int i = 0; i < size; i++)
		body[i].set(x, y);
}
void Snake::setPosition(Point p)
{
	for (int i = 0; i < size; i++)
		body[i] = p;
}
int Snake::nextPointY(){
	Point p;
	p = body[0].next(direction);
	return (p.getY());
}
int Snake::nextPointX(){
	Point p;
	p = body[0].next(direction);
	return (p.getX());
}

TheSnakesGame *Snake::getGame(){
	return theGame;
}
Point& Snake::getLoc(){
	return body[0];
}
randNum* Snake::move(){
	randNum* res = nullptr;
	Point NextP;
	NextP = body[0].next(direction);
	if (!(theGame->isSpotFree(NextP))){
		res = theGame->isRandNum(NextP);
		if (res == nullptr)//not a rand number -> its a other snake.
			direction = STOP;
	}
	
	if (direction != STOP){
	body[size - 1].draw(' ');
	theGame->printSnakeOnBoard(body[size - 1].getX(), body[size - 1].getY(), ' ');
	for (int i = size - 1; i > 0; --i)
		body[i] = body[i - 1];
	}
	

	body[0].move(direction);
	setTextColor(color);
	body[0].draw(sign);
	theGame->printSnakeOnBoard(body[0].getX(), body[0].getY(), sign);

	return res;
}

void Snake::reload(){
	stackSize++;
}
void Snake::reload(int a){
	stackSize = a;
}
void Snake::setFreeze(int a){
	a > 0 ? freeze = true : freeze = false;
}
void Snake::setLoc(Point p){
	for (int i = 0; i < size; i++)
		body[i] = p;
}
void Snake::cleanSnakefromGame(){
	int x, y;
	for (int i = 0; i<size; i++){
		x = body[i].getX();
		y = body[i].getY();
		gotoxy(x, y);
		cout << ' ';
		cout.flush();
		theGame->printCharOnBoard(body[i], ' ');
	}
}
bool Snake::shoot(char key){
	if ((key == arrowKeys[4]) && (stackSize > 0) && (direction != STOP)){
		stackSize--;
		theGame->shoot(this);
		return true;
	}
	else return false;
	
}

void Snake::setArrowKeys(const char* keys) {
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}


int Snake::getDirection(char key)
{
	for (int i = 0; i < 4; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}
int Snake::getDirection()
{
	return direction;
}

char Snake::getSign(){
	return (sign);
}
int Snake::getSize(){
	return (size);
}
void Snake::setSize(int _size){
	size = _size;
	Point p = body[0];
	Point *newbody = new Point[size];
	for (int i = 0; i < size; i++)
		newbody[i] = p;
	delete body;
	body = newbody;
}
void Snake::changeSize(int a){// positve for growth negative+zero for decrease.
	Point p = body[0];
	if (a > 0)
		size++;
	else
		size--;
	Point *newbody = new Point[size];
	for (int i = 0; i < size; i++)
		newbody[i] = p;
	delete body;
	body = newbody;
}