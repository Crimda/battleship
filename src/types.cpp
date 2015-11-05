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

Vec2::Vec2()
{}
