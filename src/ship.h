#ifndef SHIPS
#define SHIPS

#include "types.h"
#include <vector>

class Ship
{
	private:
		int hp;
	public:
		std::vector<Vec2> positions;
		ShipType type;

	public:
		Ship();
		Ship(int size, ShipType name);
		~Ship();
		bool isAlive();
		void hit();
		bool contains(Vec2 pos);
		bool isValid();
};

#endif
