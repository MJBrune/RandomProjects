#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
//#include <tr1/memory>
#include <iostream>
class VisibleGameObject
{
public:
	bool _isLoaded;
	sf::Sprite  _sprite;

	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
private:
	std::shared_ptr<sf::Texture> _image;
	std::string _filename;
};
