#include "Diggy.h"

namespace DiggyState
{
	bool Game::IsExiting()
	{
		if(_gameState == DiggyState::GameState::Exiting) 
			return true;
		else 
			return false;
	}

	void Game::Start()
	{
		if(_gameState != Uninitialized)
			return;

		_mainWindow.create(sf::VideoMode(1024,768,32),"Diggy!", sf::Style::Close);
		_mainWindow.setFramerateLimit(30);
		_gameState = DiggyState::GameState::ShowingSplash;
		_setupMenu = new SetupMenu("James");
		while(!IsExiting())
		{
			GameLoop();
		}

		mouseState = false;
		lastMouseState = false;
		
		_mainWindow.close();
	}

	void Game::GameLoop()
	{
		sf::Event currentEvent;

		_mainWindow.pollEvent(currentEvent);

		if(currentEvent.type == sf::Event::Closed)
			_gameState = DiggyState::GameState::Exiting;

		_mainWindow.clear(sf::Color(0,0,0));
		switch(_gameState)
		{
		case DiggyState::GameState::Exiting:
			{
				_mainWindow.close();
				break;
			}
		case DiggyState::GameState::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case DiggyState::GameState::ShowingMenu:
			{
				ShowMenu();
				Setup = true;
				break;
			}
		case DiggyState::GameState::ShowSetup:
			{
				_setupMenu->Draw(_mainWindow);
				_setupMenu->Update(_mainWindow);
				if( _setupMenu->enterHit)
					_gameState = DiggyState::GameState::Playing;
				_mainWindow.display();
				break;
			}
		case DiggyState::GameState::Playing:
			{
				
				if(Setup)
				{
					Setup = false;
					SetupScore = true;
					SetupGame(10, 10, _setupMenu->getPlayerName());
				}


				if(currentEvent.type == sf::Event::MouseButtonPressed)
				{
					mouseState = true;
					//if(mouseState)
					{
						_gameTable.ifClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y, player1);
						if (player1->Shovel == 0) 
							this->setGamestate(DiggyState::GameState::ScoreScreen);
					}
				} 
				else 
				{
					mouseState = false;
				}
				lastMouseState = mouseState;

				_gameTable.Draw(_mainWindow);
				player1->Draw(_mainWindow);
				_mainWindow.display();
				
				break;
			}
		case DiggyState::GameState::ScoreScreen:
			{
				if(SetupScore)
				{
					_connection = new Connection("mjbrune.org");
					_connection->openConnection();
					_connection->uploadScore(player1);
					_connection->closeConnection();
					SetupScore = false;
					leaderBoard = new std::vector<Player>;
					player1->setTextPosition(000,200);
					_connection->openConnection();
					_connection->downloadScore(Connection::Type::hearts, *leaderBoard);
					_connection->closeConnection();
					
					for(int i = 0; i < leaderBoard->size(); i++)
					{
						leaderBoard->at(i).setTextPosition(500,50*i);
						leaderBoard->at(i).setLeaderPosition(Item::Type::Heart);
					}
				}

				lastMouseState = mouseState;
				player1->Draw(_mainWindow);
				for(int i = 0; i < leaderBoard->size(); i++)
					leaderBoard->at(i).DrawLeader(_mainWindow, Item::Type::Heart);
				_mainWindow.display();
				
				break;
			}
		}
		sf::sleep(sf::milliseconds(1));
	}

	void Game::ShowSplashScreen()
	{
		SplashScreen splashScreen;
		splashScreen.Show(_mainWindow);
		_gameState = DiggyState::GameState::ShowingMenu;
	}

	void Game::ShowMenu()
	{
		MainMenu mainMenu;
		MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
		switch(result)
		{
		case MainMenu::Exit:
			_gameState = DiggyState::GameState::Exiting;
			break;
		case MainMenu::Play:
			_gameState = DiggyState::GameState::ShowSetup;
			break;
		}
	}
	void Game::SetupGame(int tableX, int tableY, std::string playerName)
	{
		_gameTable.Start(tableX,tableY);
		player1 = new Player(10,0,0,0);
		player1->SetName(playerName);
		player1->setTextPosition(500,200);
	}
}