#pragma once
#include "Item.h"
#include <sstream>
#include <string>
#include <SFML\Graphics\Text.hpp>
class Player
{
public:
	bool hasShovel;
	Player(int shov, int heart, int gold, int gem);
	void adjustItem(Item::Type item, int adjust);
	void Draw(sf::RenderWindow& window);
	void setTextPosition(int x, int y);
	void setLeaderPosition(Item::Type type);
	void DrawLeader(sf::RenderWindow& window, Item::Type type);
	void SetName(std::string name);
	std::string GetName(){return playerName;}
	int Shovel;
	int Heart;
	int Gold;
	int Gem;
private:
	std::string playerName;
	sf::Text NameText;
	sf::Text ShovelText;
	sf::Text HeartText;
	sf::Text GoldText;
	sf::Text GemText;
	std::string convertInt(int number)
	{
	   std::stringstream ss;//create a stringstream
	   ss << number;//add number to the stream
	   return ss.str();//return a string with the contents of the stream
	}
};
