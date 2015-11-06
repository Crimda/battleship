#include "gm.h"

GameStateManager::GameStateManager()
{
	playerShipMap = Map(10, 10);
	enemyShipMap  = Map(10, 10);
	playerShotMap = Map(10, 10);
	
	// Set up the ships
	playerShips[SHIP_CARRIER]   = enemyShips[SHIP_CARRIER]   = Ship();
	playerShips[SHIP_BATTLE]    = enemyShips[SHIP_BATTLE]    = Ship();
	playerShips[SHIP_CRUISER]   = enemyShips[SHIP_CRUISER]   = Ship();
	playerShips[SHIP_SUBMARINE] = enemyShips[SHIP_SUBMARINE] = Ship();
	playerShips[SHIP_DESTROYER] = enemyShips[SHIP_DESTROYER] = Ship();
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
					Ship ship = playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_CARRIER);
					if (ship.isValid())
					{
						playerShips[SHIP_CARRIER] = ship;
						playerShipsLeft++; // We placed the ship, go ahead and inc
						print("Place your battleship!");
					}

				}
				break;
			case SHIP_BATTLE:
				print("Place your battleship!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_BATTLE);
					if (ship.isValid())
					{
						playerShips[SHIP_BATTLE] = ship;
						playerShipsLeft++;
						print("Place your cruiser!");
					}
				}
				break;
			case SHIP_CRUISER:
				print("Place your cruiser!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_CRUISER);
					if (ship.isValid())
					{
						playerShips[SHIP_CRUISER] = ship;
						playerShipsLeft++;
						print("Place your submarine!");
					}
				}
				break;
			case SHIP_SUBMARINE:
				print("Place your submarine!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_SUBMARINE);
					if (ship.isValid())
					{
						playerShips[SHIP_SUBMARINE] = ship;
						playerShipsLeft++;
						print("Place your destroyer!");
					}
				}
				break;
			case SHIP_DESTROYER:
				print("Place your destroyer!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = playerShipMap.addShip(playerTargetPos, playerShipDirection, SHIP_DESTROYER);
					if (ship.isValid())
						turn = -1;
					// Reset targSpot
					playerTargetPos = Vec2(-1, -1);
				}
				break;
		}
	}

	if (turn == -1)
	{
		print("Computer placing ships, please wait...");
		printf("Enemyships: %d\n", enemyShipsLeft);
		for (int i = 0; i <= 5; i++)
		{
		switch (enemyShipsLeft)
		{
			case SHIP_CARRIER:
			{
				Ship ship = enemyShipMap.addShip(Vec2(9, 9), DIR_WEST, SHIP_CARRIER);
				if (ship.isValid())
				{
					enemyShips[SHIP_CARRIER] = ship;
					enemyShipsLeft++;
				}
				break;
			}
			case SHIP_BATTLE:
			{
				Ship ship = enemyShipMap.addShip(Vec2(9, 8), DIR_WEST, SHIP_BATTLE);
				if (ship.isValid())
				{
					enemyShips[SHIP_BATTLE] = ship;
					enemyShipsLeft++;
				}
				break;
			}
			case SHIP_CRUISER:
			{
				Ship ship = enemyShipMap.addShip(Vec2(9, 7), DIR_WEST, SHIP_CRUISER);
				if (ship.isValid())
				{
					enemyShips[SHIP_CRUISER] = ship;
					enemyShipsLeft++;
				}
				break;
			}
			case SHIP_SUBMARINE:
			{
				Ship ship = enemyShipMap.addShip(Vec2(9, 6), DIR_WEST, SHIP_SUBMARINE);
				if (ship.isValid())
				{
					enemyShips[SHIP_SUBMARINE] = ship;
					enemyShipsLeft++;
				}
				break;
			}
			case SHIP_DESTROYER:
			{
				Ship ship = enemyShipMap.addShip(Vec2(9, 5), DIR_WEST, SHIP_DESTROYER);
				if (ship.isValid())
				{
					enemyShips[SHIP_DESTROYER] = ship;
					enemyShipsLeft++;
					turn = 0;
				}
				break;
			}
		}
		}
	}

	if (turn == 0)
	{
		print("Player's turn! Enter coords for attack or a command!");
		if (playerTargetPos.inBounds())
		{
			switch (enemyShipMap.getNode(playerTargetPos))
			{
				case STATE_EMPTY:
					playerShotMap.setNode(playerTargetPos, STATE_MISS);
					break;
				case STATE_SHIP:
					playerShotMap.setNode(playerTargetPos, STATE_HIT);
					break;
				default:
					error("Something just went terribly wrong! gm.cpp:179");
					break;
			}
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

ShipType GameStateManager::getHitShip(Team team)
{
	if (team == PLAYER)
	{
		for (int i = 0; i <= enemyShipsLeft; i++)
		{
			if (enemyShips[i].contains(playerTargetPos))
			{
				return enemyShips[i].type;
			}
		}
	} else
	if (team == ENEMY)
	{
		for (int i = 0; i <= playerShipsLeft; i++)
		{
			if (playerShips[i].contains(enemyTargetPos))
			{
				return playerShips[i].type;
			}
		}
	}
	return SHIP_DESTROYER; // This will never be reached as far as I know, so is just to kill a warning
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
