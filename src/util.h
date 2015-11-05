#ifndef UTILS
#define UTILS
#include <string>
#include <vector>
#include "types.h"

/*
 * A collection of utility functions for string parsing and other yes
*/

namespace util
{
	strVec parse(std::string raw);
	Vec2 parseCoords(std::string raw);
}

#endif
