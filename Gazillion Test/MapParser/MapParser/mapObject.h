#pragma once
#include <string>
#include "Vector2i.h"
//Basic class to hold all the properties of each map object.
//Could put more things like bool isWall; and bool isBlockingObject;
//Of course this is where I would hold a pointer to a sprite/material && model/etc to display the object.
//Probably also throw in a draw() for rendering the object and onUpdate() in here as well for phyiscs/interactions/etc
class mapObject
{
public:
	std::string m_name;
	Vector2i m_pos;
	int m_weight;
	mapObject(std::string name, int weight, Vector2i pos = Vector2i(0, 0));
	mapObject(std::string name, int weight, std::string pos);
};