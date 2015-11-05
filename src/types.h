#ifndef TYPES
#define TYPES

typedef struct
{
	int x;
	int y;
} Vec2;

typedef enum
{
	STATE_EMPTY, // No shots taken
	STATE_MISS,  // A missed shot
	STATE_HIT,   // A hit
	STATE_SHIP,  // A ship
	STATE_NULL   // An index into an out of bounds location in the map data :/
} State;

#endif

