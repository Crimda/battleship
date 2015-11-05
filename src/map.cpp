#include "map.h"

Map::Map(int resX, int resY)
{
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

bool Map::set(Vec2 pos, State state)
{ // Sets state of a node, returns false if failed to or true if successful
	if (pos.x > maxResX || pos.y > maxResY)
		return false;

	mapdata[pos.y][pos.x] = state;
	return true;
}
