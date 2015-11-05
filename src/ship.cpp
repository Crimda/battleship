#include "ship.h"

Ship::Ship()
{}

Ship::Ship(int size)
{
	hp = size;
}

Ship::~Ship()
{}

void Ship::hit()
{
	hp--;
}

bool Ship::isAlive()
{
	if (hp <= 0)
		return false;

	return true;
}

