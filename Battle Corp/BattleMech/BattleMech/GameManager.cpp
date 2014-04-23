#include "GameManager.h"
#include <iostream>


GameManager::GameManager(const unsigned int &width, const unsigned int &height, const std::string &title)
	:window(sf::VideoMode(width, height), title, sf::Style::Close)
{
	currentState	= 0;
	widgets			= 0;
	window.SetFramerateLimit(30);
}

void GameManager::SetState(GameState &state)
{
	if(currentState != 0)
	{
		currentState->Exit();
	}

	currentState = &state;
	currentState->Init();
}

void GameManager::SetWidgetContainer(std::vector<UI::Widget *> &container)
{
	widgets = &container;
}


void GameManager::Step()
{
	while(window.GetEvent(event))
	{
		sf::Sleep(0.0001f);// Give system time

		switch(event.Type)
		{
		case sf::Event::Closed:

			window.Close();
			break;

		case sf::Event::TextEntered:
			
			if(widgets != 0)
			{
				for(int i = 0 ; i < widgets->size(); i++)
				{
					(*widgets)[i]->TextInput(event.Text.Unicode);
				}
			}
			break;

		case sf::Event::MouseButtonPressed:

			if(widgets != 0)
			{
				sf::Vector2f mousePos(event.MouseButton.X, event.MouseButton.Y);

				for(int i = 0; i < widgets->size(); i++)
				{
					UI::Widget &wid = *(*widgets)[i];
					
					if(wid.GetBoundingBox().Contains(mousePos.x, mousePos.y))
					{
						wid.Click(event.MouseButton.Button);
					}
					else
					{
						wid.UnClick(event.MouseButton.Button);
					}
				}

			}
			break;

		case sf::Event::MouseMoved:

			if(widgets != 0)
			{
				sf::Vector2f mousePos(event.MouseMove.X, event.MouseMove.Y);

				for(int i = 0; i < widgets->size(); i++)
				{
					UI::Widget &wid = *(*widgets)[i];
					
					if(wid.GetBoundingBox().Contains(mousePos.x, mousePos.y))
					{
						wid.Hover();
					}
					else
					{
						wid.UnHover();
					}
				}
			}
			break;
		}
	}

	window.Clear();

	if(currentState!= 0)
	{
		currentState->Update(window.GetFrameTime());
		currentState->Render();
	}
	window.Display();
}

