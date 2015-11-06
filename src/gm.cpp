#include "gm.h"

GameStateManager::GameStateManager()
{
	game.playerShipMap = Map(10, 10);
	game.enemyShipMap  = Map(10, 10);
	game.playerShotMap = Map(10, 10);
	
	// Set up the ships
	game.playerShips[SHIP_CARRIER]   = game.enemyShips[SHIP_CARRIER]   = Ship();
	game.playerShips[SHIP_BATTLE]    = game.enemyShips[SHIP_BATTLE]    = Ship();
	game.playerShips[SHIP_CRUISER]   = game.enemyShips[SHIP_CRUISER]   = Ship();
	game.playerShips[SHIP_SUBMARINE] = game.enemyShips[SHIP_SUBMARINE] = Ship();
	game.playerShips[SHIP_DESTROYER] = game.enemyShips[SHIP_DESTROYER] = Ship();
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::main()
{
	while (!endGame)
	{
		update();
		ui::draw(game.playerShipMap, game.playerShotMap, statusMsg);
		getInput();
	}
	
	switch (gameEndType)
	{
		case END_QUIT:
			ui::clear();
			break;
		case END_WIN:
			ui::clear();
			puts("!!You Win!!");
			break;
		case END_LOSE:
			ui::clear();
			puts("!!You Lose!!");
			break;
	}
}

void GameStateManager::update()
{
	if (turn == -2)
	{
		switch (game.playerShipsLeft)
		{
			case SHIP_CARRIER:
				print("Place your carrier!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_CARRIER);
					if (ship.isValid())
					{
						game.playerShips[SHIP_CARRIER] = ship;
						game.playerShipsLeft++; // We placed the ship, go ahead and inc
						print("Place your battleship!");
					}

				}
				break;
			case SHIP_BATTLE:
				print("Place your battleship!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_BATTLE);
					if (ship.isValid())
					{
						game.playerShips[SHIP_BATTLE] = ship;
						game.playerShipsLeft++;
						print("Place your cruiser!");
					}
				}
				break;
			case SHIP_CRUISER:
				print("Place your cruiser!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_CRUISER);
					if (ship.isValid())
					{
						game.playerShips[SHIP_CRUISER] = ship;
						game.playerShipsLeft++;
						print("Place your submarine!");
					}
				}
				break;
			case SHIP_SUBMARINE:
				print("Place your submarine!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_SUBMARINE);
					if (ship.isValid())
					{
						game.playerShips[SHIP_SUBMARINE] = ship;
						game.playerShipsLeft++;
						print("Place your destroyer!");
					}
				}
				break;
			case SHIP_DESTROYER:
				print("Place your destroyer!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_DESTROYER);
					if (ship.isValid())
						turn = -1;
					// Reset targSpot
					game.playerTargetPos = Vec2(-1, -1);
				}
				break;
		}
	}

	if (turn == -1)
	{
		print("Computer placing ships, please wait...");
		printf("Enemyships: %d\n", game.enemyShipsLeft);
		for (int i = 0; i <= 5; i++)
		{
		switch (game.enemyShipsLeft)
		{
			case SHIP_CARRIER:
			{
				Ship ship = game.enemyShipMap.addShip(Vec2(9, 9), DIR_WEST, SHIP_CARRIER);
				if (ship.isValid())
				{
					game.enemyShips[SHIP_CARRIER] = ship;
					game.enemyShipsLeft++;
				}
				break;
			}
			case SHIP_BATTLE:
			{
				Ship ship = game.enemyShipMap.addShip(Vec2(9, 8), DIR_WEST, SHIP_BATTLE);
				if (ship.isValid())
				{
					game.enemyShips[SHIP_BATTLE] = ship;
					game.enemyShipsLeft++;
				}
				break;
			}
			case SHIP_CRUISER:
			{
				Ship ship = game.enemyShipMap.addShip(Vec2(9, 7), DIR_WEST, SHIP_CRUISER);
				if (ship.isValid())
				{
					game.enemyShips[SHIP_CRUISER] = ship;
					game.enemyShipsLeft++;
				}
				break;
			}
			case SHIP_SUBMARINE:
			{
				Ship ship = game.enemyShipMap.addShip(Vec2(9, 6), DIR_WEST, SHIP_SUBMARINE);
				if (ship.isValid())
				{
					game.enemyShips[SHIP_SUBMARINE] = ship;
					game.enemyShipsLeft++;
				}
				break;
			}
			case SHIP_DESTROYER:
			{
				Ship ship = game.enemyShipMap.addShip(Vec2(9, 5), DIR_WEST, SHIP_DESTROYER);
				if (ship.isValid())
				{
					game.enemyShips[SHIP_DESTROYER] = ship;
					game.enemyShipsLeft++;
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
		if (game.playerTargetPos.inBounds())
		{
			// See if we already tried here
			switch (game.playerShotMap.getNode(game.playerTargetPos))
			{
				case STATE_HIT:
				case STATE_MISS:
					print("Already attacked coords, try another!");
					return;
				default: break;
			}

			switch (game.enemyShipMap.getNode(game.playerTargetPos))
			{
				case STATE_EMPTY:
					game.playerShotMap.setNode(game.playerTargetPos, STATE_MISS);
					error("Missed!");
					break;
				case STATE_SHIP:
					game.playerShotMap.setNode(game.playerTargetPos, STATE_HIT);
					switch (getHitShip(ENEMY))
					{
						case SHIP_CARRIER:
							game.enemyShips[SHIP_CARRIER].hit();
							if (!game.enemyShips[SHIP_CARRIER].isAlive())
							{
								game.enemyShipsLeft--;
								error("You sank the computer's carrier!");
							}
							break;
						case SHIP_BATTLE:
							game.enemyShips[SHIP_BATTLE].hit();
							if (!game.enemyShips[SHIP_BATTLE].isAlive())
							{
								game.enemyShipsLeft--;
								error("You sank the computer's battleship!");
							}
							break;
						case SHIP_CRUISER:
							game.enemyShips[SHIP_CRUISER].hit();
							if (!game.enemyShips[SHIP_CRUISER].isAlive())
							{
								game.enemyShipsLeft--;
								error("You sank the computer's cruiser!");
							}
							break;
						case SHIP_SUBMARINE:
							game.enemyShips[SHIP_SUBMARINE].hit();
							if (!game.enemyShips[SHIP_SUBMARINE].isAlive())
							{
								game.enemyShipsLeft--;
								error("You sank the computer's submarine!");
							}
							break;
						case SHIP_DESTROYER:
							game.enemyShips[SHIP_DESTROYER].hit();
							if (!game.enemyShips[SHIP_DESTROYER].isAlive())
							{
								game.enemyShipsLeft--;
								error("You sank the computer's destroyer!");
							}
							break;
						default: error("Something went terribly wrong in the enemy ship hit code!"); break;
					}
					break;
				default:
					error("Something just went terribly wrong! gm.cpp:192");
					break;
			}
		}
		turn = 1;
	}

	if (turn == 1)
	{
		enemyAI.process(game);
		turn = 0;
	}

	if (turn >= 0)
	{
		if (game.playerShipsLeft <= 0)
		{
			endGame = true;
			gameEndType = END_LOSE;
		} else
		if (game.enemyShipsLeft <= 0)
		{
			endGame = true;
			gameEndType = END_WIN;
		}
	}


	/* Reset state variables */
	playerShipDirection = DIR_NONE;
	game.playerTargetPos = Vec2(-1, -1);
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
			endGame = true;
		}
		else
		{
			game.playerTargetPos = util::parseCoords(commandList[0]);
			if (game.playerTargetPos.x == -1 || game.playerTargetPos.y == -1)
			{
				error("Invalid coordinates!");
				return;
			}
		}
	} else
	if (commandList.size() == 2)
	{ // Handle single argument commands
		if (commandList[1] == "north" || commandList[1] == "south" || commandList[1] == "east" || commandList[1] == "west" ||
				commandList[1] == "n" || commandList[1] == "s" || commandList[1] == "e" || commandList[1] == "w")
		{
			game.playerTargetPos = util::parseCoords(commandList[0]);
			if (game.playerTargetPos.x == -1 || game.playerTargetPos.y == -1)
			{
				error("Invalid coordinates!");
				return;
			}

			if (commandList[1] == "north" || commandList[1] == "n") playerShipDirection = DIR_NORTH; else
			if (commandList[1] == "south" || commandList[1] == "s") playerShipDirection = DIR_SOUTH; else
			if (commandList[1] == "west"  || commandList[1] == "w")  playerShipDirection = DIR_WEST; else
			if (commandList[1] == "east"  || commandList[1] == "e")  playerShipDirection = DIR_EAST;

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
	if (!endGame && turn != 1)
	{
		std::string rawCommand;
		std::getline(std::cin, rawCommand);

		strVec commandList;
		commandList = util::parse(rawCommand);

		handleCommand(commandList);
	}
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
	if (team == ENEMY)
	{
		for (int i = 0; i <= 5; i++)
		{
			if (game.enemyShips[i].contains(game.playerTargetPos))
			{
				return game.enemyShips[i].type;
			}
		}
	} else
	if (team == PLAYER)
	{
		for (int i = 0; i <= 5; i++)
		{
			if (game.playerShips[i].contains(game.enemyTargetPos))
			{
				return game.playerShips[i].type;
			}
		}
	}
	return SHIP_NULL;
}

void GameStateManager::test()
{ // Sets 5,5 to be different states on all 3 maps, then confirms it is indeed that
	game.playerShipMap.setNode(5,5, STATE_MISS);
	game.enemyShipMap.setNode(5,5, STATE_HIT);
	game.playerShotMap.setNode(5,5, STATE_SHIP);

	if (game.playerShipMap.getNode(5,5) == STATE_MISS)
		puts("Successfully set game.playerShipMap!");
	if (game.enemyShipMap.getNode(5,5) == STATE_HIT)
		puts("Successfully set game.enemyShipMap!");
	if (game.playerShotMap.getNode(5,5) == STATE_SHIP)
		puts("Successfully set game.playerShotMap!");
	ui::draw(game.playerShipMap, game.playerShotMap, "AUGH!");
}
