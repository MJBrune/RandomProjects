#include "game.h"

game::game()
	:
	charMgr(textureManager),
	missions(textureManager),
	player1(charMgr, textureManager),
	luaMgr(missions, charMgr, player1.playerShip),
	depSrc(&charMgr, textureManager),
	gameIntro(textureManager),
	sect(player1.playerShip, missions, textureManager, depSrc),
	FixedStep(sf::seconds(1.0 / 60.0)),
	ElapsedTime(sf::Time::Zero),
	debug(true)
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
	gameWindow.create(sf::VideoMode(800,600,32),"The Away Team", sf::Style::Close);
	gameWindow.setFramerateLimit(100);
	setGameState(GameState::ShowingSplash, true);
	setSmooth(false);
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
		handleInput();
	if (!switchingStates)
		draw();
}

void game::setupState()
{
	switch(gameState)
	{
	case GameState::Intro:
		{
			gameIntro.setViews(gameWindow);
			break;
		}
	case GameState::Playing:
		{
			sect.generate();
			break;
		}
	case GameState::Deploying:
		{
			break;
		}
	case GameState::PlayingMission:
		{
			missions.setViews(gameWindow);
			luaMgr.doThreadedFile(depSrc.missionPtr->getDetails("Lua file"));
			missions.missionPtr = depSrc.missionPtr;
			break;
		}
	}
	setup = false;
}

void game::handleInput()
{
	sf::Event event;
	while(gameWindow.pollEvent(event))
	{
		if (switchingStates)
			break;
		if (event.type == sf::Event::Closed 
			|| event.type == sf::Event::KeyPressed 
			&& event.key.code == sf::Keyboard::Escape)
			setGameState(GameState::Exiting);
		switch(gameState)
		{
		case GameState::ShowingSplash:
			{
				if(event.type == sf::Event::KeyPressed
					|| event.type == sf::Event::MouseButtonPressed)
				{
					setGameState(GameState::ShowingMenu);
				}

				break;
			}
		case GameState::ShowingMenu:
			{
				if(event.type == sf::Event::MouseMoved)
				{
					mainMenu.mouseOver(event.mouseMove.x, event.mouseMove.y);
				}
				else if(event.type == sf::Event::MouseButtonPressed)
				{
					switch(mainMenu.isClicked(event.mouseButton.x, event.mouseButton.y))
					{
					case mainMenu::Exit:
						setGameState(GameState::Exiting);
						break;
					case mainMenu::Play:
						setGameState(GameState::Intro, true);
						break;
					}
				}
				break;
			}
		case GameState::Intro:
			{
				if(event.type == sf::Event::KeyPressed 
					&& event.key.code == sf::Keyboard::Return)
				{
					setGameState(GameState::Playing, true);
				}
				break;
			}
		case GameState::Playing:
			{
				if (event.type == sf::Event::Closed)
					setGameState(GameState::Exiting);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					sect.generate();
				}
				else if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::S)
				{
					player1.playerShip.adjustSensors(.5);
					std::cout << player1.playerShip.getSensors() << std::endl;
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sect.isClicked(event.mouseButton.x, event.mouseButton.y);
					}
				}
				break;
			}
		case GameState::Deploying:
			{
				if (event.type == sf::Event::Closed)
					setGameState(GameState::Exiting);
				else
				{
					depSrc.handleInput(event);
					if (depSrc.skipped)
					{
						sect.skipped.restart();
						depSrc.skipped = false;
						setGameState(GameState::Playing, false);
					}
				}
				break;
			}
		case GameState::PlayingMission:
			{
				if (event.type == sf::Event::MouseMoved)
				{
					missions.hover(event.mouseMove.x, event.mouseMove.y);
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						missions.clicked(event.mouseButton.x, event.mouseButton.y);
					}
				}
				break;
			}
		case GameState::EndMission:
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						std::cout << event.mouseButton.x << " | " << event.mouseButton.y << std::endl;
					}
				}
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
	case GameState::ShowingMenu:
		{
			break;
		}
	case GameState::Intro:
		{
			gameIntro.update(FixedStep.asMicroseconds());
			if (gameIntro.moveOn)
			{
				setGameState(GameState::Playing, true);
			}
			break;
		}
	case GameState::Playing:
		{
			sect.update(FixedStep.asMicroseconds());
			if (sect.inMission)
			{
				setGameState(GameState::Deploying, true);
				sect.inMission = false;
			}
			player1.fixedUpdate();
			break;
		}
	case GameState::Deploying:
		{
			depSrc.update();
			if (depSrc.deployed)
			{
				setGameState(GameState::PlayingMission, true);
			}
			break;
		}
	case GameState::PlayingMission:
		{
			if (missions.missionPtr->Completed)
				setGameState(GameState::Playing);
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
	case GameState::ShowingMenu:
		{
			mainMenu.draw(gameWindow);
			break;
		}
	case GameState::Intro:
		{
			gameIntro.draw(gameWindow);
			break;
		}
	case GameState::Playing:
		{
			sect.draw(gameWindow);
			player1.draw(gameWindow);
			break;
		}
	case GameState::Deploying:
		{			
			depSrc.draw(gameWindow);
			break;
		}
	case GameState::PlayingMission:
		{
			missions.draw(gameWindow);
			break;
		}
	case GameState::EndMission:
		{
			endMissionSrc.draw(gameWindow);
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

void game::setSmooth(bool smooth)
{
	for(std::unordered_map<std::string, sf::Texture>::iterator iterator = textureManager.begin(); iterator != textureManager.end(); iterator++) 
	{
		iterator->second.setSmooth(smooth);
	}
}