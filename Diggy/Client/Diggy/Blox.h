#pragma once
#include "VisualGameObject.h"
#include "Item.h"
#include "Player.h"
class Blox :
	public VisibleGameObject
{

public:
	enum Type { Hole=0, Dirt=1, Grass=2, Rock=3 };
	Blox(Blox::Type type, Item::Type itemtype);
	void setType(Blox::Type type);
	void ifClicked(Player* player);
	Type getType(){return tileType;}
	sf::FloatRect bBox;
	void SetPosition(float x, float y)
	{
		VisibleGameObject::SetPosition(x,y);
		item.SetPosition(x,y);
	}
	void Draw(sf::RenderWindow & window);
	void DrawItem(sf::RenderWindow & window);
private:
	bool gotitem;
	Item item;
	Type tileType;
	bool isDiggable;

};
