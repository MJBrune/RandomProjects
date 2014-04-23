#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <string>
#include <vector>
#include "UI/Widget.h"

class GameManager
{
public:
	GameManager(const unsigned int &width = 1024, const unsigned int &height = 800, const std::string &title = "Battle Corp");

	void SetState(GameState &state);

	sf::RenderWindow &GetWindow(){return window;}
	
	void Step();
	void SetWidgetContainer(std::vector<UI::Widget *> &container);

private:
	GameState*					currentState;
	sf::RenderWindow			window;
	sf::Event					event;


	std::vector<UI::Widget*>*	widgets;
protected:
};

#endif