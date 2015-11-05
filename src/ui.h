#ifndef UI
#define UI
#include <string>

#include "types.h"
#include "map.h"

namespace ui
{
	void draw(Map playerShipMap, Map playerShotMap, std::string status);
}

#endif
