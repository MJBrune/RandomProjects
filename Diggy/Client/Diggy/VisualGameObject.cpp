#include "VisualGameObject.h"

VisibleGameObject::VisibleGameObject()
	: _image(new sf::Texture()),
	_isLoaded(true)
{
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if(_image->loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(*_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

void VisibleGameObject::SetPosition(float x, float y)
{
	_sprite.setPosition(x,y);
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
  return _sprite.getPosition();
  return sf::Vector2f();
}

void VisibleGameObject::Update(float elapsedTime)
{
}