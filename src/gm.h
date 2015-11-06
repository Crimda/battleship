#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER
#include <iostream>
#include <string>

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
		/*
		 * -2: Player ship placement
		 * -1: Computer ship placement
		 *  0: Player's turn
		 *  1: Computer's turn
		*/
		int turn = -2;

		// Used for shutting the game off and displaying end-game messages
		EndCondition gameEndType = END_QUIT;
		bool endGame = false;

		// Used for the status bar
		std::string statusMsg;
		bool statusMsgRedrawOverride;

		/* Vars for ship placing */
		Direction playerShipDirection;
		Ship currentShip;

		/* Instantiate the AI */
		SimpleAI enemyAI = SimpleAI();

	public:
		GameStateManager();
		~GameStateManager();
		void test();
		void main();
		void update();
		void getInput();

		void print(std::string msg);
		void error(std::string msg);

		void handleCommand(strVec commandList);
		ShipType getHitShip(Team team);
};

#endif
