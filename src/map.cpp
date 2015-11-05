#include "map.h"

Map::Map()
{} // I hate this language

Map::Map(int resX, int resY)
{ // Create a map of resX by resY
	// Allocate space for the y axis
	mapdata.resize(resY);

	// Allocate space for the x axis
	for(int y = 0; y < mapdata.size(); y++)
	{
		mapdata[y].resize(resX);
	}

	maxResX = resX;
	maxResY = resY;
}

Map::~Map()
{
}

bool Map::setNode(Vec2 pos, State state)
{ // Sets state of a node, returns false if failed to or true if successful
	if (pos.x > maxResX || pos.y > maxResY)
		return false;

	mapdata[pos.y][pos.x] = state;
	return true;
}

bool Map::setNode(int x, int y, State state)
{ // Overload for setNode to take ints instead of a Vec2
	if (x > maxResX || y > maxResY)
		return false;

	mapdata[y][x] = state;
	return true;
}

State Map::getNode(Vec2 pos)
{ // Returns state of a node at pos, or STATE_NULL on failure(out of bounds?)
	if (pos.x > maxResX || pos.y > maxResY)
		return STATE_NULL;

	return mapdata[pos.y][pos.x];
}

State Map::getNode(int x, int y)
{ // Overload for getNode to take ints instead of a Vec2
	if (x > maxResX || y > maxResY)
		return STATE_NULL;

	return mapdata[y][x];
}

bool Map::addShip(Vec2 pos, Direction dir, ShipType type)
{ // Return true if ship is placable, and update data, false if not
	/* Are we even on the damn board? */
	if (!pos.inBounds())
		return false;

	int size;
	switch (type)
	{ // These are offset from our current position, hence the one less than size
		case SHIP_CARRIER:   size = 4; break;
		case SHIP_BATTLE:    size = 3; break;
		case SHIP_CRUISER:   size = 2; break;
		case SHIP_SUBMARINE: size = 2; break;
		case SHIP_DESTROYER: size = 1; break;
	}

	Vec2 onBoardTest = Vec2(pos.x, pos.y);
	switch (dir)
	{
		case DIR_NORTH: onBoardTest.y -= size; break;
		case DIR_SOUTH: onBoardTest.y += size; break;
		case DIR_WEST:  onBoardTest.x -= size; break;
		case DIR_EAST:  onBoardTest.x += size; break;
		case DIR_NONE:  return false; break;
	}

	/* Will we still be on the board once placed? */
	if (!onBoardTest.inBounds())
		return false;

	/* Is there a ship in the way? */
	switch(dir)
	{
		case DIR_NORTH:
			for (int y = pos.y; y >= pos.y - size; y--)
				if (getNode(pos.x, y) == STATE_SHIP)
					return false;
			break;
		case DIR_SOUTH:
			for (int y = pos.y; y <= pos.y + size; y++)
				if (getNode(pos.x, y) == STATE_SHIP)
					return false;
			break;
		case DIR_WEST:
			for (int x = pos.x; x >= pos.x - size; x--)
				if (getNode(x, pos.y) == STATE_SHIP)
					return false;
			break;
		case DIR_EAST:
			for (int x = pos.x; x <= pos.x + size; x++)
				if (getNode(x, pos.y) == STATE_SHIP)
					return false;
			break;
		case DIR_NONE: return false; break;
	}

	/* Okay, we can actually add the damn ship now \o/ */
	switch(dir)
	{
		case DIR_NORTH:
			for (int y = pos.y; y >= pos.y - size; y--)
				setNode(pos.x, y, STATE_SHIP);
			break;
		case DIR_SOUTH:
			for (int y = pos.y; y <= pos.y + size; y++)
				setNode(pos.x, y, STATE_SHIP);
			break;
		case DIR_WEST:
			for (int x = pos.x; x >= pos.x - size; x--)
				setNode(x, pos.y, STATE_SHIP);
			break;
		case DIR_EAST:
			for (int x = pos.x; x <= pos.x + size; x++)
				setNode(x, pos.y, STATE_SHIP);
			break;
		case DIR_NONE: return false; break;
	}

	return true;
}

bool Map::addShip(int x, int y, Direction dir, ShipType type)
{ // Fuck you do it right
	return addShip(Vec2(x, y), dir, type);
}
