#ifndef _TANK_H
#define _TANK_H
#include "ResourceManager.h"
#include <SFML\Graphics.hpp>
#include "json\value.h"
#include "json\reader.h"
#include "json\writer.h"
#include <fstream>
#include <Thor/Vectors.hpp>
#include <SFML\System.hpp>
class tank
{
private:
	ResourceManager& resMgrRef;
	sf::Sprite tankSprite;
	sf::Sprite tankTurrentSprite;
	sf::Vector2f turretOffset;
	sf::Vector2f facing;
	int speed;
	int mobility;
public:
	tank(ResourceManager& resMgr);
	void loadFromFile(std::string fileName);
	void draw(sf::RenderWindow& window);
	void handleInput(sf::Event handleEvent);
	void move(float x, float y);
	void currentMove(float x, float y);
	void setTurret(sf::Vector2f mousePoint);
	void update(sf::RenderWindow& window);
};
#endif