#include "ui.h"

// Allow for windows stupidry
#ifdef WINDOWS
	#define ENDLN "\r\n"
#else
	#define ENDLN "\n"
#endif

void ui::draw(Map playerShipMap, Map playerShotMap)
{
	// Symbols for rendering the grid
	char renderChars[] = 
	{
		'.',
		'O',
		'X',
		'+',
		'?' // Something went terribly wrong
	};

	// Print legend
	puts("x  A B C D E F G H I J  |  A B C D E F G H I J");

	std::string buffer;
	for (int y = 0; y < playerShipMap.maxResY; y++)
	{
		if (y < 9)
			printf("%d ", y + 1);
		else
			printf("%d", y + 1);

		for (int x = 0; x < playerShipMap.maxResX; x++)
		{
			putchar(' ');
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
		// Space over a bit
		printf("  | ");
		for (int x = 0; x < playerShotMap.maxResX; x++)
		{
			putchar(' ');
			switch (playerShotMap.getNode(x, y))
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

		// Finally print a newline
		printf("%s", ENDLN);
	}
}

