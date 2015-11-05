#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER

#include "types.h"
#include "ship.h"
#include "map.h"
#include "ui.h"
#include "gameconf.h"

class GameStateManager
{
	private:
		Map playerShipMap; // Will track enemy shots too
		Map enemyShipMap;  // Will not be drawn
		Map playerShotMap; // Will be shown to the player

		int turn = -2; // -2 == player ship placement, -1 == comp ship place, 0 == player, 1 == comp, 2 == over

		Ship playerShips[5]; // Store ships
		Ship enemyShips[5];   // yes

		int playerShipsLeft = 5;
		int enemyShipsLeft = 5;
	public:
		GameStateManager();
		~GameStateManager();
		void test();
		void update();

};

#endif
