#ifndef GAMESTATE
#define GAMESTATE

#include "types.h"
#include "map.h"
#include "ship.h"

struct GameState
{ // A container for data with some useful functions
	Map playerShipMap; // Store's player's ship positions and hits or misses by computer
	Map playerShotMap; // Display's player's shots, hits, and misses
	Ship playerShips[5]; // Storage for player's ship entities
	Vec2 playerTargetPos; // Track player's coordinate choice

	Map enemyShipMap;  // Store computer's ships
	Map enemyShotMap;  // Store computer's shots for later analysis
	Ship enemyShips[5];  // Storage for computer's ship entities
	Vec2 enemyTargetPos; // Track computer's coordinate choice

	int playerShipsLeft = 0; // Set to zero as used for tracking during ship placement
	int enemyShipsLeft = 0;  // Set to zero for same reason
};

#endif

