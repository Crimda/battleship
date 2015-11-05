#include <stdio.h>
#include "map.h"

int main(int argc, char* argv[])
{
	puts("hi");

	Map playerShipMap = Map(10, 10);
	if (playerShipMap.getNode(5, 5) == STATE_EMPTY)
		puts("Success! Node 5,5 on player ship map is empty!");

	if (playerShipMap.setNode(5, 5, STATE_MISS))
		puts("Successfully set node 5,5 as a missed shot!");

	if (playerShipMap.getNode(5, 5) == STATE_MISS)
		puts("Full glorious success of our glorious master race, Node 5,5 is STATE_MISS!");

	return 0;
}

