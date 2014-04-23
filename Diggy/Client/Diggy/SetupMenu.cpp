#include "SetupMenu.h"

void SetupMenu::Draw(sf::RenderWindow& window)
{
	window.draw(nameText);
	window.draw(textTitle);
}

SetupMenu::SetupMenu(std::string name)
{
	playerName = name; 
	nameText.setString(playerName);
	textTitle.setString("Name: ");
	textTitle.setPosition(200,200);
	nameText.setPosition(300,200);
	enterHit = false;
}

void SetupMenu::Update(sf::RenderWindow& renderWindow)
{
	std::cout << playerName << std::endl;
	sf::Event windowEvent;
	while(renderWindow.pollEvent(windowEvent))
		if(windowEvent.type == sf::Event::TextEntered)
		{
			if (windowEvent.text.unicode == 8)
			{
				if (playerName.size () > 0)
				{
					playerName.pop_back();
					nameText.setString(playerName);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				enterHit = true;
			}
			else if (windowEvent.text.unicode > 47)
			{
				playerName.push_back(static_cast<char>(windowEvent.text.unicode));
				nameText.setString(playerName);
			}
		}

}