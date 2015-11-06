#ifndef TYPES
#define TYPES

#include <vector>
#include <string>

class Vec2
{
	public:
		int x;
		int y;
		Vec2(int x, int y);
		Vec2();
		bool inBounds();
};

typedef std::vector<std::string> strVec;

typedef enum
{
	STATE_EMPTY, // No shots taken
	STATE_MISS,  // A missed shot
	STATE_HIT,   // A hit
	STATE_SHIP,  // A ship
	STATE_NULL   // An index into an out of bounds location in the map data :/
} State;

typedef enum
{
	SHIP_CARRIER,
	SHIP_BATTLE,
	SHIP_CRUISER,
	SHIP_SUBMARINE,
	SHIP_DESTROYER,
	SHIP_NULL
} ShipType;

typedef enum
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_NONE
} Direction;

typedef enum
{
	PLAYER,
	ENEMY
} Team;

#endif

