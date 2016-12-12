#include "Snake.h"
#include "TheSnakesGame.h"


Snake::Snake(int size, const Point& position, Color c, int dir)
{
	//color = c;
	direction = dir;
	setColor(c);
	this->size = size;
	body = new Point[size];
	for (int i = 0; i < size; i++)
	{
		body[i].set(position.getX(), position.getY());
		//body[i] = position;
	}		
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
/*
void Snake::setPosition(int y, int x)
{
	for (int i = 0; i < size; i++)
		body[i].set(x, y);
}*/
void Snake::move()
{
	body[size - 1].draw(' ');
	for (int i = size - 1; i > 0; --i)
		body[i] = body[i - 1];

	if (theGame->isWall(body[0].next(direction)))
		direction = 4;

	body[0].move(direction);
	setTextColor(color);
	body[0].draw('@');
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
