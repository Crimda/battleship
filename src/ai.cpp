#include "ai.h"

SimpleAI::SimpleAI()
{}

SimpleAI::~SimpleAI()
{}

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

	printf("Targeting: %d, %d\n", choice.x, choice.y);
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

