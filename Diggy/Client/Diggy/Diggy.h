#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Splashscreen.h"
#include "MainMenu.h"
#include "GameTable.h"
#include "Player.h"
#include "Connect.h"
#include "SetupMenu.h"
#include <exception>

namespace DiggyState
{
	enum GameState { Uninitialized, ShowingSplash, ShowingMenu, 
		ShowSetup, Playing, ScoreScreen, Exiting };

	class Game
	{

	public:
		void Start();
		void setGamestate(GameState state){ _gameState = state;}

	private:
		bool Setup;
		bool SetupScore;
		Player* player1;
		bool IsExiting();
		void GameLoop();
		void ShowSplashScreen();
		void ShowMenu();
		void SetupGame(int tableX, int tableY, std::string playerName);

		Connection* _connection;
		std::vector<Player>* leaderBoard;

		GameTable _gameTable;
		GameState _gameState;
		sf::RenderWindow _mainWindow;

		SetupMenu* _setupMenu;
		bool lastMouseState;
		bool mouseState;
	};
}