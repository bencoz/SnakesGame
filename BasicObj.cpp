#include "BasicObj.h"
#include "TheSnakesGame.h"

BasicOBJ::BasicOBJ(int _size, const Point& position, Color c, int dir, char symb)
{
	setSign(symb);
	direction = dir;
	setColor(c);
	size = _size;
	body = new Point[size];
	for (int i = 0; i < size; i++)
		body[i] = position;
	theGame = nullptr;
}

BasicOBJ::BasicOBJ(const BasicOBJ& obj)
{
	setSign(obj.sign);
	direction = obj.direction;
	setColor(obj.color);
	size = obj.size;
	body = new Point[size];
	for (int i = 0; i < size; i++)
		body[i] = obj.body[i];
}
BasicOBJ::~BasicOBJ(){ 
	cleanOBJfromGame(); 
	delete[] body;
}

void BasicOBJ::setPosition(int x, int y)
{
	for (int i = 0; i < size; i++)
		body[i].set(x, y);
}
void BasicOBJ::setPosition(Point p)
{
	for (int i = 0; i < size; i++)
		body[i] = p;
}
Point& BasicOBJ::getLoc(){
	return body[0];
}
Point& BasicOBJ::getTail(){
	return body[size-1];
}
int BasicOBJ::nextPointY(){
	Point p;
	p = body[0].next(direction);
	return (p.getY());
}
int BasicOBJ::nextPointX(){
	Point p;
	p = body[0].next(direction);
	return (p.getX());
}
int BasicOBJ::getDirection(){
	return direction;
}
char BasicOBJ::getSign(){
	return (sign);
}
int BasicOBJ::getSize(){
	return (size);
}
void BasicOBJ::setSize(int _size){
	size = _size;
	Point p = body[0];
	Point *newbody = new Point[size];
	for (int i = 0; i < size; i++)
		newbody[i] = p;
	delete body;
	body = newbody;
}
void BasicOBJ::changeSize(int a){// positve for growth negative+zero for decrease.
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
void BasicOBJ::moveBody(){
	for (int i = size - 1; i > 0; --i)
		body[i] = body[i - 1];
}

void BasicOBJ::cleanOBJfromGame(){
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