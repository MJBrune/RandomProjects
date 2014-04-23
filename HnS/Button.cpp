#include "Button.h"

button::button(ResourceManager& resMgr)
	:
	text(new sf::Text),
	resMgrRef(resMgr)
{
	resMgrRef.loadFont("assets/fonts/SourceSansPro.ttf");

	text->setFont(*resMgrRef.getFont("assets/fonts/SourceSansPro.ttf"));
	text->setColor(sf::Color::Black);
}

button::button(const button& copyButton)
	:
	resMgrRef(copyButton.resMgrRef)
{
	this->text = copyButton.text;
	text->setString(copyButton.text->getString());
	this->shape = copyButton.shape;
	this->bBox = copyButton.bBox;
	this->text->setFont(*resMgrRef.getFont("assets/fonts/SourceSansPro.ttf"));
	calcbBox();
}
void button::setText(std::string textString)
{
	text->setString(textString);
	calcbBox();
}
void button::setPosition(float x, float y)
{
	shape.setPosition(x,y);
	calcbBox();
}

void button::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(*text);
}

void button::draw(sf::RenderWindow& window, sf::Shader& shader)
{
	window.draw(shape, &shader);
	window.draw(*text, &shader);
}

void button::calcbBox()
{	
	shape.setSize(sf::Vector2f(text->getLocalBounds().width/text->getCharacterSize()+text->getLocalBounds().width,text->getCharacterSize()));
	text->setPosition(shape.getPosition().x, text->getLocalBounds().height/2 - shape.getSize().y/2 + shape.getPosition().y);
	bBox.left = shape.getPosition().x;
	bBox.top = shape.getPosition().y;
	bBox.width = shape.getPosition().x+shape.getSize().x;
	bBox.height = shape.getPosition().y+shape.getSize().y;
}

bool button::isClicked(int x, int y)
{
	return ( 
		bBox.height > y 
		&& bBox.top < y 
		&& bBox.left < x 
		&& bBox.width > x
		);
}

void button::setBackground(sf::Color color)
{
	shape.setFillColor(color);
}

void button::setFontColor(sf::Color color)
{
	text->setColor(color);
}

void button::setOutline(sf::Color color)
{
	shape.setOutlineColor(color);
}

void button::setFontSize(int size)
{
	text->setCharacterSize(size);
}