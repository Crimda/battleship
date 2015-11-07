#include "ui.h"

// Allow for windows stupidry
#ifdef WIN32
	#define ENDLN "\r\n"
#else
	#define ENDLN "\n"
#endif

std::string ui::lastMessage = "";

void ui::delay(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

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

void ui::drawMap(GameState state)
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
	printf("x  A B C D E F G H I J  |  A B C D E F G H I J  x");

	printf("%s", ENDLN);
	
	for (int y = 0; y < state.playerShipMap.maxResY; y++)
	{
		if (y < 9)
			printf("%d ", y + 1);
		else
			printf("%d", y + 1);

		for (int x = 0; x < state.playerShipMap.maxResX; x++)
		{
			putchar(' ');
			switch (state.playerShipMap.getNode(x, y))
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
		//printf("  | ");

		if (y < 9)
			printf("  %d ", y + 1);
		else
			printf(" %d ", y + 1);


		for (int x = 0; x < state.playerShotMap.maxResX; x++)
		{
			putchar(' ');
			switch (state.playerShotMap.getNode(x, y))
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
		
		if (y < 9)
			printf("  %d", y + 1);
		else
			printf(" %d", y + 1);

		// Finally print a few newline's
		printf("%s", ENDLN);
	}
	puts("");
	puts("x  A B C D E F G H I J  |  A B C D E F G H I J  x");
	puts("=================================================");

	fflush(stdout);
}

void ui::print(std::string message)
{
	lastMessage = message;
	clear();
	printf("%s%s", message.c_str(), ENDLN);
	fflush(stdout);
}

void ui::printWithMap(GameState state, std::string message)
{
	drawMap(state);
	printf("%s%s", message.c_str(), ENDLN);
	fflush(stdout);
}

void ui::prompt(std::string message)
{
	print(message); // Clears buffer anyway
	puts("");
	printf(">>> ");
	fflush(stdout);
}

void ui::promptWithMap(GameState state, std::string message)
{
	lastMessage = message;
	drawMap(state);
	printf("%s%s", message.c_str(), ENDLN);
	puts("");
	printf(">>> ");
	fflush(stdout);
}

void ui::ddrawMap(GameState state)
{
	drawMap(state);
	fflush(stdout);
	delay(DELAY);
}

void ui::dprint(std::string message)
{
	print(message);
	fflush(stdout);
	delay(DELAY);
}

void ui::dprintWithMap(GameState state, std::string message)
{
	printWithMap(state, message);
	fflush(stdout);
	delay(DELAY);
}

void ui::dprompt(std::string message)
{
	prompt(message);
	fflush(stdout);
	delay(DELAY);
}

void ui::dpromptWithMap(GameState state, std::string message)
{
	promptWithMap(state, message);
	fflush(stdout);
	delay(DELAY);
}

void ui::promptWithMap(GameState state)
{
	promptWithMap(state, lastMessage);
}

void ui::printWithMap(GameState state)
{
	printWithMap(state, lastMessage);
}
