#include <vector>
#include "mapObject.h"
//Map object, you could stuff more properties and methods in here if desired.
//Allowing for programmers to have an interface to the map.
class map
{
public:
	map();
	map(std::vector<mapObject> Objects);
	std::vector<mapObject> mapObjects;
	std::string m_fileName;
	bool loadedSuccessfully;
};