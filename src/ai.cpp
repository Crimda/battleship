#include "ai.h"

SimpleAI::SimpleAI()
{}

SimpleAI::~SimpleAI()
{}



Placement SimpleAI::placeShip()
{ // Brute-force ship placement method meant to be called from a loop
	Placement result;

	result.pos.reseed();
	result.pos.randomize();
	int choice = getRandInt(4);
	switch (choice)
	{ // Randomly select a direction
		case 0:
			result.dir = DIR_NORTH;
			break;
		case 1:
			result.dir = DIR_EAST;
			break;
		case 2:
			result.dir = DIR_SOUTH;
			break;
		case 3:
			result.dir = DIR_WEST;
			break;
	}
	return result;
}
	

void SimpleAI::addHistory(Vec2 pos)
{ // Helper function, append shot history
	shotHistory.push_back(pos);
}

bool SimpleAI::inHistory(Vec2 pos)
{ // Helper function, test if pos in history
	for (int i = 0; i < shotHistory.size(); i++)
	{
		if (shotHistory[i].x == pos.x && shotHistory[i].y == pos.y)
			return true;
	}
	return false;
}

Vec2 SimpleAI::search(GameState state)
{ // Pick a random spot we haven't tried and fire
	Vec2 choice = Vec2();
	choice.randomize();
	if (inHistory(choice))
	{
		while (inHistory(choice))
		{ // This also stops shots in the same cell ^^
			choice.randomize();
		}
	}
	return choice;
}

Vec2 SimpleAI::destroy(GameState state)
{ // We found a ship, focus fire untill it sinks
	Vec2 choice = Vec2();
	return choice;
}

Vec2 SimpleAI::process(GameState state)
{
	Vec2 move = Vec2();
	switch(logicState)
	{
		case LOGIC_SEARCH:
			move = search(state);
			break;
		case LOGIC_DESTROY:
			move = destroy(state);
			break;
	}
	addHistory(move);
	return move;
}

