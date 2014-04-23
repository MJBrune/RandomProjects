#include "playingState.h"


playingState::playingState(ResourceManager& resMgr)
	:
	resMgrRef(resMgr),
	playerTank(resMgrRef)
{
	playerTank.loadFromFile("./assets/tanks/tank0.json");
	playerTank.move(200,200);
}


playingState::~playingState()
{
}

void playingState::draw(sf::RenderWindow& window)
{
	playerTank.draw(window);
}

void playingState::update(sf::RenderWindow& window)
{
	playerTank.update(window);
}

void playingState::handleInput(sf::Event handleEvent)
{
	playerTank.handleInput(handleEvent);
}