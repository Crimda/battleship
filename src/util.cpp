#include "util.h"

strVec util::parse(std::string raw)
{ // Use result.empty() to test if it was able to parse or not
	strVec retVal;
	std::string buffer;

	for (int i = 0; i < raw.size(); i++)
	{
		if (raw[i] == ' ' || raw[i] == '\r' || raw[i] == '\n')
		{
			retVal.push_back(buffer);
			buffer = "";
		}
		else
		{
			buffer += raw[i];
		}
	}
	retVal.push_back(buffer);
	return retVal;
}

Vec2 util::parseCoords(std::string raw)
{ // Returns Vec2 on successful parse. on failure return -1,-1
	Vec2 retVal;

	if (raw.size() > 3)
		return Vec2(-1, -1);

	if (raw.size() < 2)
		return Vec2(-1, -1);

	if (raw.size() == 3)
	{
		if (raw[1] == '1' && raw[2] == '0')
		{
			retVal.y = 10;
			goto getFirst;
		}
		else
		{
			return Vec2(-1, -1);
		}
	}

	// Handle raw[1] first, so we can use goto to skip this part to raw[0]
	// goto is perfectly safe and acceptable provided you use it responsibly
	switch (raw[1])
	{
		case '1': retVal.y = 0; break;
		case '2': retVal.y = 1; break;
		case '3': retVal.y = 2; break;
		case '4': retVal.y = 3; break;
		case '5': retVal.y = 4; break;
		case '6': retVal.y = 5; break;
		case '7': retVal.y = 6; break;
		case '8': retVal.y = 7; break;
		case '9': retVal.y = 8; break;
		default: return Vec2(-1, -1); break;
	}
	getFirst:
	switch (raw[0])
	{
		case 'a': retVal.x = 0; break;
		case 'b': retVal.x = 1; break;
		case 'c': retVal.x = 2; break;
		case 'd': retVal.x = 3; break;
		case 'e': retVal.x = 4; break;
		case 'f': retVal.x = 5; break;
		case 'g': retVal.x = 6; break;
		case 'h': retVal.x = 7; break;
		case 'i': retVal.x = 8; break;
		case 'j': retVal.x = 9; break;
		default: return Vec2(-1, -1); break;
	}
	return retVal;
}

