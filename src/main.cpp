#include <stdio.h>
#include "gm.h"

int main(int argc, char* argv[])
{
	puts("hi");
/*
	Map playerShipMap = Map(10, 10);
	if (playerShipMap.getNode(5, 5) == STATE_EMPTY)
		puts("Success! Node 5,5 on player ship map is empty!");

	if (playerShipMap.setNode(5, 5, STATE_MISS))
		puts("Successfully set node 5,5 as a missed shot!");

	if (playerShipMap.getNode(5, 5) == STATE_MISS)
		puts("Full glorious success of our glorious master race, Node 5,5 is STATE_MISS!");

	char renderChars[] = 
	{
		'.',
		'O',
		'X',
		'+',
		' '
	};

	for (int y = 0; y < playerShipMap.maxResY; y++)
	{
		for (int x = 0; x < playerShipMap.maxResX; x++)
		{
			switch (playerShipMap.getNode(x, y))
			{
				case STATE_EMPTY:
					putchar(renderChars[STATE_EMPTY]);
					break;
				case STATE_HIT:
					putchar(renderChars[STATE_HIT]);
					break;
				case STATE_MISS:
					putchar(renderChars[STATE_MISS]);
					break;
				case STATE_SHIP:
					putchar(renderChars[STATE_SHIP]);
					break;
				case STATE_NULL:
					putchar(renderChars[STATE_NULL]);
					break;
			}
		}
		putchar('\n');
	}
	*/
	
	GameStateManager gm = GameStateManager();
	gm.test();

	return 0;
}

