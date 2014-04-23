#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <iostream>

class SetupMenu
{
private:
	sf::Text textTitle;
	std::string playerName;
	sf::Text nameText;
public:
	bool enterHit;
	SetupMenu(std::string name);
	void setPlayerName(std::string name){playerName = name;}
	std::string getPlayerName(){return playerName;}
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& renderWindow);
};