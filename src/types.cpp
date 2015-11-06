#include "types.h"

Vec2::Vec2(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Vec2::inBounds()
{
	if (x > -1 && x < 10)
		if (y > -1 && y < 10)
			return true;
	return false;
}

void Vec2::reseed()
{
	srand(time(NULL));
}

void Vec2::randomize()
{
	x = rand() % 10;
	y = rand() % 10;
}

Vec2::Vec2()
{}
