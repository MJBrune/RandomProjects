#include "mapParser.h"
#include <iostream>
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		//This is where I would put asynchronous code using std::future and std::async to allow
		//for level loading in chunks to be streamed to the client.
		mapParser mapParse = mapParser(argv[1]);

		if (mapParse.m_map.loadedSuccessfully)
		{
			int walls = 0;
			int topItems = 0;

			for (auto it = mapParse.m_map.mapObjects.begin(); it != mapParse.m_map.mapObjects.end(); ++it)
			{
				if (it->m_name == "Wall")
				{
					std::cout << "Wall Y axis:" << std::endl;
					walls++;
					std::cout << it->m_pos.m_y << std::endl;
				}
				else
				{
					if (it->m_weight == 0)
						topItems++;
					std::cout << it->m_name << std::endl;
				}
			}

			std::cout << "Number Of Walls: " << walls << std::endl
				<< "Number of Top Level Items: " << topItems << std::endl;
			std::string l;
			std::cin >> l;
		}
	}
}