#include "Splashscreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture splashImage;
	if(splashImage.loadFromFile("assets/Splashscreen.jpg") != true)
	{
		return;
	}

	sf::Sprite sprite(splashImage);

	renderWindow.draw(sprite);
}