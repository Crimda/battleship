#include "ui.h"

// Allow for windows stupidry
#ifdef WIN32
	#define ENDLN "\r\n"
#else
	#define ENDLN "\n"
#endif


void ui::clear()
{
	// YES I KNOW THIS IS BAD OKAY WHAT OTHER CHOICE DO I HAVE!?
	// DON'T JUDGE ME! IT'S 2015 AND THERE _STILL_ IS NO WAY TO
	// DO A CROSS-PLATFORM CLEARING OF THE SCREEN FFS! T_T
	#ifdef WIN32
	system("cls");
	#else
	system("clear");
	#endif
}

void ui::draw(Map playerShipMap, Map playerShotMap, std::string status)
{
	// Clear the screen
	clear();
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
	printf("x  A B C D E F G H I J  |  A B C D E F G H I J");

	// Print status
	printf("  %s%s", status.c_str(), ENDLN);
	
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

		// Finally print a few newline's
		printf("%s", ENDLN);
	}
	puts("");
	printf(">>> ");
}

