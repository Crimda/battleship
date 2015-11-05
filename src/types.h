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
	STATE_MISS,
	STATE_HIT,
	STATE_SHIP,
	STATE_NULL
} State;

#endif

