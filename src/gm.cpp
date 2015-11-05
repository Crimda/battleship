#include "gm.h"

GameStateManager::GameStateManager()
{
	playerShipMap = Map(10, 10);
	enemyShipMap  = Map(10, 10);
	playerShotMap = Map(10, 10);
	
	// Set up the ships
	playerShips[SHIP_CARRIER]   = enemyShips[SHIP_CARRIER]   = Ship(5);
	playerShips[SHIP_BATTLE]    = enemyShips[SHIP_BATTLE]    = Ship(4);
	playerShips[SHIP_CRUISER]   = enemyShips[SHIP_CRUISER]   = Ship(3);
	playerShips[SHIP_SUBMARINE] = enemyShips[SHIP_SUBMARINE] = Ship(3);
	playerShips[SHIP_DESTROYER] = enemyShips[SHIP_DESTROYER] = Ship(2);
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::main()
{
	while (!gameOver)
	{
		update();
		ui::draw(playerShipMap, playerShotMap, statusMsg);
		getInput();
	}
}

void GameStateManager::update()
{
	if (!statusMsgRedrawOverride)
	{
		if (turn == -2)
		{
			statusMsg = "Place your ships!";
		}
	}
	else
	{
		statusMsgRedrawOverride = false;
	}
}

void GameStateManager::handleCommand(strVec commandList)
{ 
}

void GameStateManager::getInput()
{
	std::string rawCommand;
	std::getline(std::cin, rawCommand);

	strVec commandList = util::parse(rawCommand);
	handleCommand(commandList);

	/*
	if (statusMsgRedrawOverride)
		return;
	if (command == "test")
	{
		statusMsg = "SUCCESSFUL! \\o/";
	} else
	if (command == "quit" || command == "q" || command == "sd")
	{
		gameOver = true;
	}
	*/
}

void GameStateManager::print(std::string msg)
{ // Helper to print info to the status bar
	statusMsgRedrawOverride = true;
	statusMsg = msg;
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
	ui::draw(playerShipMap, playerShotMap, "AUGH!");
}
