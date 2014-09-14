#include "map.h"

map::map(std::vector<mapObject> Objects)
{
	mapObjects = Objects;
	loadedSuccessfully = false;
}

map::map()
{
	loadedSuccessfully = false;
}