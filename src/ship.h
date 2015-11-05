#ifndef SHIPS
#define SHIPS

#include "types.h"

class Ship
{
	private:
		int hp;
	public:
		Ship();
		Ship(int size);
		~Ship();
		bool isAlive();
		void hit();
};

#endif
