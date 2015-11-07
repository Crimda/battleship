#ifndef UI
#define UI
#include <string>
#include <stdlib.h>

#include <chrono>
#include <thread>

#define DELAY 1500 // 1.5 seconds iirc

#include "types.h"
#include "map.h"
#include "gamestate.h"


namespace ui
{
	void drawMap(GameState state); // Just draw map
	void prompt(std::string message); // Just draw a prompt
	void promptWithMap(GameState state, std::string message); // Draw everything
	void print(std::string message); // Just draw a message without a prompt
	void printWithMap(GameState state, std::string message); // Draw everything but prompt

	// Delayed variants
	void ddrawMap(GameState state);
	void dprompt(std::string message);
	void dpromptWithMap(GameState state, std::string message);
	void dprint(std::string message);
	void dprintWithMap(GameState state, std::string message);

	// Just show last message
	// Somewhat specialized, so only covers with map render
	void promptWithMap(GameState state);
	void printWithMap(GameState state);

	// Buffer for the last two functions
	extern std::string lastMessage;

	// Utility functions
	void clear();
	void delay(int ms);
}

#endif
