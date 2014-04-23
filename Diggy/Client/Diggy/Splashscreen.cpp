#include "Splashscreen.h"


namespace DiggyState
{
	void SplashScreen::Show(sf::RenderWindow & renderWindow)
	{
		sf::Texture splashImage;
		if(splashImage.loadFromFile("Splashscreen.jpg") != true)
		{
			return;
		}

		sf::Sprite sprite(splashImage);

		renderWindow.draw(sprite);
		renderWindow.display();

		sf::Event event;
		while(true)
		{
			while(renderWindow.pollEvent(event))
			{
				if(event.type == sf::Event::KeyPressed
					|| event.type == sf::Event::MouseButtonPressed
					|| event.type == sf::Event::Closed )
				{
					return;
				}
			}
		}
	}
}