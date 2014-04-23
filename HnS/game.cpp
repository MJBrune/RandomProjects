#include "game.h"

game::game()
	:
	FixedStep(sf::seconds(1.0 / 60.0)),
	ElapsedTime(sf::Time::Zero),
	debug(true),
	FPS(resMgr),
	playState(resMgr)
{
	FPS.setBackground(sf::Color::Transparent);
	FPS.setFontColor(sf::Color::White);
	FPS.setPosition(600,0);
}

void game::start()
{
	if(gameState != GameState::Uninitialized)
		return;
	switchingStates = false;
	gameWindow.create(sf::VideoMode(800,600,32),"The Away Team", sf::Style::Default);
	gameWindow.setFramerateLimit(100);
	setGameState(GameState::ShowingSplash, true);
	updateNext = updateClock.getElapsedTime().asMilliseconds();
	frameCount = 0;
	while(gameState != GameState::Exiting)
	{
		gameLoop();
	}
	gameWindow.close();
}

void game::gameLoop()
{
	switchingStates = false;
	if (setup)
	{
		setupState();
	}

	//Average Frames Per Second Counter
	avgFrameCounter.push_back(1.0 / updateClock.getElapsedTime().asSeconds());
	if (frameClock.getElapsedTime().asSeconds() >= 1)
	{
		frameClock.restart();
		int average = 0;
		for (unsigned int i = 0; i < avgFrameCounter.size(); i++)
		{
			average += avgFrameCounter.at(i);
		}
		average /= avgFrameCounter.size();
		std::stringstream out;
		out << "Frames: " << average;
		FPS.setText(out.str());
		avgFrameCounter.clear();
	}

	ElapsedTime += updateClock.restart();
	while(ElapsedTime >= FixedStep)
	{
		ElapsedTime -= FixedStep;
		if (!switchingStates)
			fixedUpdate();
	}

	if (!switchingStates)
	{
		handleInput();
		draw();
	}
}

void game::setupState()
{
//	switch(gameState)
//	{
//	}
	setup = false;
}

void game::handleInput()
{
	sf::Event event;
	while(gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed 
			|| event.type == sf::Event::KeyPressed 
			&& event.key.code == sf::Keyboard::Escape)
			setGameState(GameState::Exiting);
		if (event.type == sf::Event::Resized) 
			gameWindow.setView(
			sf::View(
			sf::FloatRect(0,0,gameWindow.getSize().x,gameWindow.getSize().y)
			)
			);
		switch(gameState)
		{
		case GameState::ShowingSplash:
			{
				if(event.type == sf::Event::KeyPressed
					|| event.type == sf::Event::MouseButtonPressed)
				{
					setGameState(GameState::Playing);
				}

				break;
			}
		case GameState::Playing:
			{
				playState.handleInput(event);
				break;
			}
		}
	}
}

void game::fixedUpdate()
{
	switch(gameState)
	{
	case GameState::ShowingSplash:
		{
			break;
		}
	case GameState::Playing:
		{
			playState.update(gameWindow);
			break;
		}

	}
}

void game::draw()
{
	gameWindow.clear(sf::Color(0,0,0));
	switch(gameState)
	{
	case GameState::Exiting:
		{
			gameWindow.close();
			break;
		}
	case GameState::ShowingSplash:
		{
			splashScreen.Show(gameWindow);
			break;
		}
	case GameState::Playing:
		{
			playState.draw(gameWindow);
			break;
		}
	}
	if (debug)
		FPS.draw(gameWindow);
	gameWindow.display();
}

void game::setGameState(GameState state, bool Setup)
{
	gameState = state;
	setup = Setup;
	switchingStates = true;
}
