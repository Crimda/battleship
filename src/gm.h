#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER
#include <iostream>
#include <string>

#include "types.h"
#include "ship.h"
#include "map.h"
#include "ui.h"
#include "util.h"

class GameStateManager
{
	private:
		Map playerShipMap; // Will track enemy shots too
		Map enemyShipMap;  // Will not be drawn
		Map playerShotMap; // Will be shown to the player

		int turn = -2; // -2 == player ship placement, -1 == comp ship place, 0 == player, 1 == comp, 2 == over
		bool gameOver = false;

		std::string statusMsg;
		bool statusMsgRedrawOverride;

		Ship playerShips[5]; // Store ships
		Ship enemyShips[5];  // yes

		Vec2 playerTargetPos;
		Vec2 enemyTargetPos;

		int playerShipsLeft = 0; // Set to zero as used for tracking during ship placement
		int enemyShipsLeft = 0;  // Set to zero for same reason

		/* Vars for ship placing */
		Direction playerShipDirection;
		Ship currentShip;

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
