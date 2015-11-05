#include "gm.h"

GameStateManager::GameStateManager()
{
	this->playerShipMap = Map(g_mapResX, g_mapResY);
	this->enemyShipMap  = Map(g_mapResX, g_mapResY);
	this->playerShotMap = Map(g_mapResX, g_mapResY);
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::test()
{ // Sets 5,5 to be different states on all 3 maps, then confirms it is indeed that
	playerShipMap.setNode(5,5, STATE_MISS);
	enemyShipMap.setNode(5,5, STATE_HIT);
	playerShotMap.setNode(5,5, STATE_SHIP);

	if (playerShipMap.getNode(5,5) == STATE_MISS)
		puts("Successfully set playerShipMap!");
	if (enemyShipMap.getNode(5,5) == STATE_HIT)
		puts("Successfully set enemyShipMap!");
	if (playerShotMap.getNode(5,5) == STATE_SHIP)
		puts("Successfully set playerShotMap!");
}
