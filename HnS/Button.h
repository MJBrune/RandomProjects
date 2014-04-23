#ifndef _Button_H
#define _Button_H
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class button
{
private:
	ResourceManager& resMgrRef;
public:
	std::shared_ptr<sf::Text> text;
	sf::RectangleShape shape;
	sf::FloatRect bBox;
	
	button(ResourceManager& resMgr);
	button(const button& copyButton);
	void calcbBox();
	void setPosition(float x, float y);

	void setBackground(sf::Color color);
	void setFontColor(sf::Color color);
	void setOutline(sf::Color color);

	void draw(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, sf::Shader& shader);

	void setFontSize(int size);
	sf::FloatRect getbBox(){return bBox;}

	void setText(std::string textString);
	bool isClicked(int x, int y);
};
#endif