#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER

#include "types.h"
#include "map.h"
#include "ui.h"
#include "gameconf.h"

class GameStateManager
{
	private:
		Map playerShipMap; // Will track enemy shots too
		Map enemyShipMap;  // Will not be drawn
		Map playerShotMap; // Will be shown to the player
	public:
		GameStateManager();
		~GameStateManager();
		void test();
};

#endif
