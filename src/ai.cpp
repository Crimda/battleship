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
	return Vec2();
}

Vec2 SimpleAI::destroy(GameState state)
{ // We found a ship, focus fire untill it sinks
	return Vec2();
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
	return move;
}

