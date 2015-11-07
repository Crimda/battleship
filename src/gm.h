#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER
#include <iostream>
#include <string>
#include <limits.h>

#include "types.h"
#include "ship.h"
#include "map.h"
#include "ui.h"
#include "util.h"
#include "ai.h"
#include "gamestate.h"


class GameStateManager
{
	private:
		// Used to manage game state
		GameState game;
		Turn turn = TURN_PLAYERSTART;

		// Used for shutting the game off and displaying end-game messages
		EndCondition gameEndType = END_QUIT;
		bool endGame = false;

		// Used for the status bar
		std::string statusMsg;
		bool keepLastStatus = false;

		/* Vars for ship placing */
		Direction playerShipDirection;
		Ship currentShip;

		/* Instantiate the AI */
		SimpleAI enemyAI = SimpleAI();

	public:
		GameStateManager();
		~GameStateManager();
		void main();
		void update();
		void getInput();

		void handleCommand(strVec commandList);
		ShipType getHitShip(Team team);
};

#endif
