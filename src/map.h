#ifndef MAP
#define MAP

#include "gameconf.h"
#include "types.h"
#include <vector>
#include <stdio.h>

class Map
{
	private:
		std::vector<std::vector<State> > mapdata;
		unsigned int maxResX;
		unsigned int maxResY;
	public:
		Map(int resX, int resY);
		~Map();
		bool setNode(Vec2 pos, State state);
		bool setNode(int x, int y, State state);
		State getNode(Vec2 pos);
		State getNode(int x, int y);


};


#endif
