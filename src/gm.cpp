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
	if (turn == -2)
	{
		switch (playerShipsLeft)
		{
			case SHIP_CARRIER:
				print("Place your carrier!");
				if (playerShipDirection != DIR_NONE)
				{
					if (playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_CARRIER))
					{
						playerShipsLeft++; // We placed the ship, go ahead and inc
						print("Place your battleship!");
					}

				}
				break;
			case SHIP_BATTLE:
				print("Place your battleship!");
				if (playerShipDirection != DIR_NONE)
				{
					if (playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_BATTLE))
					{
						playerShipsLeft++;
						print("Place your cruiser!");
					}
				}
				break;
			case SHIP_CRUISER:
				print("Place your cruiser!");
				if (playerShipDirection != DIR_NONE)
				{
					if (playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_CRUISER))
					{
						playerShipsLeft++;
						print("Place your submarine!");
					}
				}
				break;
			case SHIP_SUBMARINE:
				print("Place your submarine!");
				if (playerShipDirection != DIR_NONE)
				{
					if (playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_SUBMARINE))
					{
						playerShipsLeft++;
						print("Place your destroyer!");
					}
				}
				break;
			case SHIP_DESTROYER:
				print("Place your destroyer!");
				if (playerShipDirection != DIR_NONE)
				{
					if (playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_DESTROYER))
						turn = -1;
				}
				break;
		}
	}

	/* Reset state variables */
	playerShipDirection = DIR_NONE;
	playerTargetPos = Vec2(-1, -1);
	if (statusMsgRedrawOverride)
	{
		statusMsgRedrawOverride = false;
	}
}

void GameStateManager::handleCommand(strVec commandList)
{
	if (commandList.empty())
		return;

	if (commandList.size() == 1)
	{ // Handle 0 arg commands
		if (commandList[0] == "quit" || commandList[0] == "q" || commandList[0] == "sd")
		{
			gameOver = true;
		}
		else
		{
			playerTargetPos = util::parseCoords(commandList[0]);
			if (playerTargetPos.x == -1 || playerTargetPos.y == -1)
			{
				error("Invalid coordinates!");
				return;
			}
		}
	} else
	if (commandList.size() == 2)
	{ // Handle single argument commands
		if (commandList[1] == "north" || commandList[1] == "south" || commandList[1] == "east" || commandList[1] == "west")
		{
			playerTargetPos = util::parseCoords(commandList[0]);
			if (playerTargetPos.x == -1 || playerTargetPos.y == -1)
			{
				error("Invalid coordinates!");
				return;
			}

			if (commandList[1] == "north") playerShipDirection = DIR_NORTH; else
			if (commandList[1] == "south") playerShipDirection = DIR_SOUTH; else
			if (commandList[1] == "west")  playerShipDirection = DIR_WEST; else
			if (commandList[1] == "east")  playerShipDirection = DIR_EAST;

			return;
		}
		else
			goto invalidCommand;
	}
	else
	invalidCommand:
		error("Invalid command!");
}

void GameStateManager::getInput()
{
	std::string rawCommand;
	std::getline(std::cin, rawCommand);

	strVec commandList;
	commandList = util::parse(rawCommand);

	handleCommand(commandList);
}

void GameStateManager::print(std::string msg)
{ // Helper to print info to the status bar
	statusMsg = msg;
}

void GameStateManager::error(std::string msg)
{
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
