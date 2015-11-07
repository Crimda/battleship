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
//		ui::promptWithMap(game);
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
	if (turn == TURN_PLAYERSTART)
 	{
		switch (game.playerShipsLeft)
 	 	{ 
			case SHIP_CARRIER:
				ui::promptWithMap(game, "Place your carrier!");
				if (playerShipDirection != DIR_NONE)
		 		{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_CARRIER);
					if (ship.isValid())
					{
						game.playerShips[SHIP_CARRIER] = ship;
						game.playerShipsLeft++; // We placed the ship, go ahead and inc
						ui::promptWithMap(game, "Place your battleship!");
					}

				}
				break;
			case SHIP_BATTLE:
				ui::promptWithMap(game, "Place your battleship!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_BATTLE);
					if (ship.isValid())
					{
						game.playerShips[SHIP_BATTLE] = ship;
						game.playerShipsLeft++;
						ui::promptWithMap(game, "Place your cruiser!");
					}
				}
				break;
			case SHIP_CRUISER:
				ui::promptWithMap(game, "Place your cruiser!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_CRUISER);
					if (ship.isValid())
					{
						game.playerShips[SHIP_CRUISER] = ship;
						game.playerShipsLeft++;
						ui::promptWithMap(game, "Place your submarine!");
					}
				}
				break;
			case SHIP_SUBMARINE:
				ui::promptWithMap(game, "Place your submarine!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_SUBMARINE);
					if (ship.isValid())
					{
						game.playerShips[SHIP_SUBMARINE] = ship;
						game.playerShipsLeft++;
						ui::promptWithMap(game, "Place your destroyer!");
					}
				}
				break;
			case SHIP_DESTROYER:
				ui::promptWithMap(game, "Place your destroyer!");
				if (playerShipDirection != DIR_NONE)
				{
					Ship ship = game.playerShipMap.addShip(game.playerTargetPos, playerShipDirection, SHIP_DESTROYER);
					if (ship.isValid())
						turn = TURN_COMPUTERSTART;
					// Reset targSpot
					game.playerTargetPos = Vec2(-1, -1);
				}
				break;
		}
	}

	if (turn == TURN_COMPUTERSTART)
	{
		ui::printWithMap(game, "Computer placing ships, please wait...");
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
					turn = TURN_PLAYER;
				}
				break;
			}
		}
		}
	}

	if (turn == TURN_PLAYER)
	{
		ui::promptWithMap(game, "Player's turn! Enter coords for attack or a command!");
		if (game.playerTargetPos.inBounds())
		{
			// See if we already tried here
			switch (game.playerShotMap.getNode(game.playerTargetPos))
			{
				case STATE_HIT:
				case STATE_MISS:
					ui::dprintWithMap(game, "Already attacked coords, try another!");
					return;
				default: break;
			}

			switch (game.enemyShipMap.getNode(game.playerTargetPos))
			{
				case STATE_EMPTY:
					game.playerShotMap.setNode(game.playerTargetPos, STATE_MISS);
					ui::dprintWithMap(game, "Missed!");
					break;
				case STATE_SHIP:
					game.playerShotMap.setNode(game.playerTargetPos, STATE_HIT);
					ui::dprintWithMap(game, "Hit!");
					switch (getHitShip(ENEMY))
					{
						case SHIP_CARRIER:
							game.enemyShips[SHIP_CARRIER].hit();
							if (!game.enemyShips[SHIP_CARRIER].isAlive())
							{
								game.enemyShipsLeft--;
								ui::dprintWithMap(game, "You sank the computer's carrier!");
							}
							break;
						case SHIP_BATTLE:
							game.enemyShips[SHIP_BATTLE].hit();
							if (!game.enemyShips[SHIP_BATTLE].isAlive())
							{
								game.enemyShipsLeft--;
								ui::dprintWithMap(game, "You sank the computer's battleship!");
							}
							break;
						case SHIP_CRUISER:
							game.enemyShips[SHIP_CRUISER].hit();
							if (!game.enemyShips[SHIP_CRUISER].isAlive())
							{
								game.enemyShipsLeft--;
								ui::dprintWithMap(game, "You sank the computer's cruiser!");
							}
							break;
						case SHIP_SUBMARINE:
							game.enemyShips[SHIP_SUBMARINE].hit();
							if (!game.enemyShips[SHIP_SUBMARINE].isAlive())
							{
								game.enemyShipsLeft--;
								ui::dprintWithMap(game, "You sank the computer's submarine!");
							}
							break;
						case SHIP_DESTROYER:
							game.enemyShips[SHIP_DESTROYER].hit();
							if (!game.enemyShips[SHIP_DESTROYER].isAlive())
							{
								game.enemyShipsLeft--;
								ui::dprintWithMap(game, "You sank the computer's destroyer!");
							}
							break;
						default: ui::dprint("Something went terribly wrong in the enemy ship hit code!"); break;
					}
					break;
				default:
					ui::dprint("Something just went terribly wrong! gm.cpp:247");
					break;
			}
			turn = TURN_COMPUTER;
		}
	}

	if (turn == TURN_COMPUTER)
	{
		game.enemyTargetPos = enemyAI.process(game);
		switch(game.playerShipMap.getNode(game.enemyTargetPos))
		{
			case STATE_EMPTY:
				game.playerShipMap.setNode(game.enemyTargetPos, STATE_MISS);
				game.enemyLastShotHit = false;
				ui::dprintWithMap(game, "Computer missed!");
				break;
			case STATE_SHIP:
				game.playerShipMap.setNode(game.enemyTargetPos, STATE_HIT);
				switch (getHitShip(PLAYER))
				{
					case SHIP_CARRIER:
						game.playerShips[SHIP_CARRIER].hit();
						if (!game.playerShips[SHIP_CARRIER].isAlive())
						{
							game.playerShipsLeft--;
							ui::dprintWithMap(game, "Computer sank your carrier!");
						}
						break;
					case SHIP_BATTLE:
						game.playerShips[SHIP_BATTLE].hit();
						if (!game.playerShips[SHIP_BATTLE].isAlive())
						{
							game.playerShipsLeft--;
							ui::dprintWithMap(game, "Computer sank your battleship!");
						}
						break;
					case SHIP_CRUISER:
						game.playerShips[SHIP_CRUISER].hit();
						if (!game.playerShips[SHIP_CRUISER].isAlive())
						{
							game.playerShipsLeft--;
							ui::dprintWithMap(game, "Computer sank your cruiser!");
						}
						break;
					case SHIP_SUBMARINE:
						game.playerShips[SHIP_SUBMARINE].hit();
						if (!game.playerShips[SHIP_SUBMARINE].isAlive())
						{
							game.playerShipsLeft--;
							ui::dprintWithMap(game, "Computer sank your submarine!");
						}
						break;
					case SHIP_DESTROYER:
						game.playerShips[SHIP_DESTROYER].hit();
						if (!game.playerShips[SHIP_DESTROYER].isAlive())
						{
							game.playerShipsLeft--;
							ui::dprintWithMap(game, "Computer sank your destroyer!");
						}
						break;
					default: ui::dprint("Something went terribly wrong in the player ship hit code!"); break;

				}
				break;
			case STATE_HIT:
			case STATE_MISS:
				ui::dprint("Comp shot at an already selected coord!");
				break;
			default:
				ui::dprint("Something just went terribly wrong! gm.cpp:317");
				break;
		}
		turn = TURN_PLAYER;
		ui::promptWithMap(game, "Player's turn! Enter coords for attack or a command!");
	}

	if (turn == TURN_PLAYER || turn == TURN_COMPUTER)
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
	if (keepLastStatus)
	{
		keepLastStatus = false;
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
				ui::dprintWithMap(game, "Invalid coordinates!");
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
				ui::dprintWithMap(game, "Invalid coordinates!");
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
		ui::dprintWithMap(game, "Invalid command!");
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

