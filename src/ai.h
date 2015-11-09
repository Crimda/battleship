#ifndef AI
#define AI

#include <stdio.h>
#include <string>
#include <vector>


#include "types.h"
#include "map.h"
#include "ship.h"
#include "gamestate.h"

typedef enum
{
	LOGIC_SEARCH,
	LOGIC_DESTROY
} AIState;

typedef struct
{
	Vec2 pos;
	Direction dir;
} Placement;

class SimpleAI
{
	private:
		std::vector<Vec2> shotHistory; // Store past shots for future reference
		AIState logicState = LOGIC_SEARCH; // Used for statemachine control
	/* Functions */
	private:
		Vec2 search(GameState state);
		Vec2 destroy(GameState state);
		void addHistory(Vec2 pos);
		bool inHistory(Vec2 pos);

	public:
		SimpleAI();
		~SimpleAI();
		Vec2 process(GameState state);
		Placement placeShip();

};

#endif
