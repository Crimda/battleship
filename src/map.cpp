#include "map.h"

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

