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

void Snake::setPosition(int x, int y)
{
	for (int i = 0; i < size; i++)
		body[i].set(x, y);
}
randNum* Snake::move(){
	randNum* res = nullptr;


	if (theGame->isNotFree(body[0].next(direction))){
		res = theGame->isRandNum(body[0].next(direction));
		if (res == nullptr)//not a rand number -> its a other snake.
			direction = 4;
	}
	
	if (direction != 4){
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
int Snake::getDirection(char key)
{
	for (int i = 0; i < 4; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}
char Snake::getSign(){
	return (sign);
}
int Snake::getSize(){
	return (size);
}
