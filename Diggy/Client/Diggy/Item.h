#pragma once
#include "VisualGameObject.h"
class Item :
	public VisibleGameObject
{

public:
	enum Type { Nothing, Shovel, Heart, Gold, Gem };
	Item(Item::Type type);
	void setType(Item::Type type);
//	void ifClicked(){}
	Type getType(){return itemType;}

	void Tween(sf::Vector2f destination, float speed);
	void Draw(sf::RenderWindow & window);
private:
	Type itemType;
	bool isMoving;
	sf::Vector2f destPos;
	float moveSpeed;
};