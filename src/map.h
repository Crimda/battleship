#ifndef MAP
#define MAP

#include "types.h"
#include <vector>
#include <stdio.h>

class Map
{
	/* Variables */
	public:
		unsigned int maxResX;
		unsigned int maxResY;
	/* Functions */
	private:
		std::vector<std::vector<State> > mapdata;
	public:
		Map(int resX, int resY);
		Map();
		~Map();
		bool setNode(Vec2 pos, State state);
		bool setNode(int x, int y, State state);
		State getNode(Vec2 pos);
		State getNode(int x, int y);


};


#endif
