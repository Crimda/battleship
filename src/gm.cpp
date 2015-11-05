#include "gm.h"

GameStateManager::GameStateManager()
{
	playerShipMap = Map(g_mapResX, g_mapResY);
	enemyShipMap  = Map(g_mapResX, g_mapResY);
	playerShotMap = Map(g_mapResX, g_mapResY);
	
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

void GameStateManager::parseCoords(std::string coords)
{
	gameOver = true;
	if (coords.size() <= 3 && coords.size() > 1)
	{
		if (coords.size() == 3)
		{ // Handle a 10
			if (coords[1] == '1' && coords[2] == '0')
			{
				playerShotY = 10;
				return;
			}
			else
			{
				statusMsgRedrawOverride = true;
				statusMsg = "Invalid shot position!";
				return;
			}
		}
		else
		{
			switch (coords[0])
			{
				case 'a': playerShotX = 0; break;
				case 'b': playerShotX = 1; break;
				case 'c': playerShotX = 2; break;
				case 'd': playerShotX = 3; break;
				case 'e': playerShotX = 4; break;
				case 'f': playerShotX = 5; break;
				case 'g': playerShotX = 6; break;
				case 'h': playerShotX = 7; break;
				case 'i': playerShotX = 8; break;
				case 'j': playerShotX = 9; break;
				default:
					statusMsgRedrawOverride = true;
					statusMsg = "Invalid Shot position!";
					return;
					break;
			}

			switch (coords[1])
			{
				case '1': playerShotY = 0; break;
				case '2': playerShotY = 1; break;
				case '3': playerShotY = 2; break;
				case '4': playerShotY = 3; break;
				case '5': playerShotY = 4; break;
				case '6': playerShotY = 5; break;
				case '7': playerShotY = 6; break;
				case '8': playerShotY = 7; break;
				case '9': playerShotY = 8; break;
				default:
					statusMsgRedrawOverride = true;
					statusMsg = "Invalid shot position!";
					break;
					return;
			}
		}
	}
	else
	{
		statusMsgRedrawOverride = true;
		statusMsg = "[ERR]: Invalid coords passed to coord parser!";
	}
}

void GameStateManager::parseCommand(std::string raw)
{ // TODO: Figure out why this isn't working or a better way to do it
	std::string word;
	for (int i = 0; i < raw.size(); i++)
	{
		if (raw[i] != ' ' || raw[i] != '\r' || raw[i] != '\n')
		{
			word += raw[i];
		}
		else
		{
			if (word.size() == 2)
			{ // We probably have coords here, try to parse em!
				parseCoords(word);
				if (statusMsgRedrawOverride)
					return; // We got an error! Pass it through!
			}
		}
	}	
}

void GameStateManager::getInput()
{
	std::getline(std::cin, command);
	parseCommand(command);
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
