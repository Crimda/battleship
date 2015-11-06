#ifndef UI
#define UI
#include <string>
#include <stdlib.h>

#include "types.h"
#include "map.h"

namespace ui
{
	void draw(Map playerShipMap, Map playerShotMap, std::string status);
	void clear();
}

#endif
