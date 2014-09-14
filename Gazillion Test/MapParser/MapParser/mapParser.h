#pragma once
#include <string>
#include "mapObject.h"
#include "map.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Vector2i.h"
#include <algorithm>

class mapParser
{
public:
	mapParser(std::string fileName);
	map m_map;
private:
	bool loadFile(std::string fileName);
	void loadObject(std::unordered_map<std::string, std::string>& object, int weight);
	Vector2i getPair(std::string str);
	
	std::vector<mapObject> mapObjects;
};