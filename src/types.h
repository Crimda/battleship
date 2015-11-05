#ifndef TYPES
#define TYPES

typedef struct
{
	int x;
	int y;
} Vec2;

typedef enum
{
	STATE_EMPTY,
	STATE_SHOT,
	STATE_HIT,
	STATE_SHIP
} State;

#endif

