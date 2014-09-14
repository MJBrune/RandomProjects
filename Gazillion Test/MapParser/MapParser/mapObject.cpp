#include "mapObject.h"
#include <iostream>

mapObject::mapObject(std::string name, int weight, Vector2i pos)
{
	m_name = name;
	m_pos = pos;
	m_weight = weight;
}

mapObject::mapObject(std::string name, int weight, std::string pos)
{
	m_name = name;
	m_weight = weight;
	std::string delim = ",";
	std::string x;
	std::string y;
	auto start = 0U;
	auto end = pos.find(delim);
	while (end != std::string::npos)
	{
		x = pos.substr(start, end - start);
		start = end + delim.length();
		end = pos.find(delim, start);
	}
	y = pos.substr(start, end);
	m_pos = Vector2i(atoi(x.c_str()), atoi(y.c_str()));
}