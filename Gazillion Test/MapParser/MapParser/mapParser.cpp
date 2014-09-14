#include "mapParser.h"

mapParser::mapParser(std::string fileName)
{
	if (loadFile(fileName))
	{
		m_map.m_fileName = fileName;
		m_map.loadedSuccessfully = true;
	}
}

bool mapParser::loadFile(std::string fileName)
{
	try
	{
		std::ifstream infile(fileName);
		if (!infile.is_open())
			throw "Unable to open map file.";
		bool isItems = false;
		std::unordered_map<std::string, std::string> object;
		bool foundObject = false;
		int weight = 0;
		for (std::string line; getline(infile, line);)
		{

			if (line == "=ITEMS=")
				isItems = true;
			else if (line.find("Item") != std::string::npos || line.find("Map") != std::string::npos
				|| line.find("Wall") != std::string::npos || line.find("=BG=") != std::string::npos)
				;//ignore these lines
			else if (line.find('(') != std::string::npos)
			{
				foundObject = true;
				loadObject(object, weight);
				if (isItems)
					weight++;
			}
			else if (line.find(')') != std::string::npos)
			{
				foundObject = false;
				if (isItems)
					weight--;
			}
			else
			{
				std::string delim = "=";
				std::string key;
				std::string value;
				auto start = 0U;
				auto end = line.find(delim);
				while (end != std::string::npos)
				{
					key = line.substr(start, end - start);
					start = end + delim.length();
					end = line.find(delim, start);
				}
				value = line.substr(start, end);
				key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
				value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

				object[key] = value;
			}
		}
		loadObject(object, weight);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void mapParser::loadObject(std::unordered_map<std::string, std::string>& object, int weight)
{
	//This is where I would put asynchronous coding to allow for each object to be loaded into the map
	//To help speed up the performance as no objects depends on another.
	bool hasName = false;
	bool hasPos = false;
	bool hasStart = false;
	bool hasEnd = false;
	for (auto it = object.begin(); it != object.end(); ++it)
	{
		if (it->first.find("Name") != std::string::npos)
			hasName = true;
		else if (it->first.find("Pos") != std::string::npos)
			hasPos = true;
		else if (it->first.find("Start") != std::string::npos)
			hasStart = true;
		else if (it->first.find("End") != std::string::npos)
			hasEnd = true;
	}

	if (hasName)
	{
		if (hasPos)
			m_map.mapObjects.push_back(mapObject(object["Name"], weight, object["Pos"]));
		else
			m_map.mapObjects.push_back(mapObject(object["Name"], weight));
	}
	else if (hasStart && hasEnd)
	{
		Vector2i startPos = getPair(object["Start"]);
		Vector2i endPos = getPair(object["End"]);
		for (int y = startPos.m_y; y <= endPos.m_y; y++)
			m_map.mapObjects.push_back(mapObject("Wall", weight, Vector2i(startPos.m_x, y)));
		for (int x = startPos.m_x + 1; x <= endPos.m_x; x++)
			m_map.mapObjects.push_back(mapObject("Wall", weight, Vector2i(x, endPos.m_y)));
	}
	object.clear();
}

Vector2i mapParser::getPair(std::string str)
{
	std::string delim = ",";
	std::string x;
	std::string y;
	auto start = 0U;
	auto end = str.find(delim);
	while (end != std::string::npos)
	{
		x = str.substr(start, end - start);
		start = end + delim.length();
		end = str.find(delim, start);
	}
	y = str.substr(start, end);
	return Vector2i(atoi(x.c_str()), atoi(y.c_str()));
}