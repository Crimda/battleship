#include "ship.h"

Ship::Ship()
{}

Ship::Ship(int size, ShipType name)
{
	hp = size;
	type = name;
}

Ship::~Ship()
{}

void Ship::hit()
{
	if (hp > 0)
		hp--;
}

bool Ship::isAlive()
{
	if (hp <= 0)
		return false;

	return true;
}

bool Ship::contains(Vec2 pos)
{
	for (int i = 0; i < positions.size(); i++)
		if (positions[i].x == pos.x && positions[i].y == pos.y)
			return true;
	return false;
}

bool Ship::isValid()
{
	if (positions.size() > 0)
		return true;
	
	return false;
}

