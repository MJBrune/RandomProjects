#include "Blox.h"

Blox::Blox(Blox::Type type, Item::Type itemtype)
	:VisibleGameObject(),
	tileType(type),
	item(itemtype),
	gotitem(false)
{
	switch(type)
	{
    case Blox::Type::Hole:
	    this->Load("hole.png");
	    break;
	case Blox::Type::Dirt:
		this->Load("dirt.png");
		isDiggable = true;
		break;
	case Blox::Type::Grass:
		this->Load("grass.png");
		isDiggable = true;
		break;
	case Blox::Type::Rock:
		this->Load("rock.png");
		isDiggable = false;
		break;
	}
}
void Blox::setType(Blox::Type type)
{
	tileType = type;
	switch(type)
	{
    case Blox::Type::Hole:
	    this->Load("hole.png");
	    break;
	case Blox::Type::Dirt:
		this->Load("dirt.png");
		isDiggable = true;
		break;
	case Blox::Type::Grass:
		this->Load("grass.png");
		isDiggable = true;
		break;
	case Blox::Type::Rock:
		this->Load("rock.png");
		isDiggable = false;
		break;
	}
}
void Blox::ifClicked(Player* player)
{
	if(!gotitem)
	{
		player->adjustItem(Item::Type::Shovel, -1);
		if (tileType != 0) 
			setType(Type(tileType-1));
		if (tileType == 0) 
		{
			gotitem = true;
			switch(item.getType())
			{
			case Item::Type::Nothing:
				break;
			case Item::Type::Shovel:
				player->adjustItem(Item::Type::Shovel, 2);
				item.Tween(sf::Vector2f(500, 200), 5);
				break;
			case Item::Type::Heart:
				player->adjustItem(Item::Type::Heart, 1);
				item.Tween(sf::Vector2f(500, 250), 5);
				break;
			case Item::Type::Gold:
				player->adjustItem(Item::Type::Gold, 1);
				item.Tween(sf::Vector2f(500, 300), 5);
				break;
			case Item::Type::Gem:
				player->adjustItem(Item::Type::Gem, 1);
				item.Tween(sf::Vector2f(500, 350), 5);
				break;
			}
		}
	}
}

void Blox::Draw(sf::RenderWindow & window)
{
	VisibleGameObject::Draw(window);
}

void Blox::DrawItem(sf::RenderWindow & window)
{
	if (tileType == Blox::Type::Hole)
		item.Draw(window);
}