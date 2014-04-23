#ifndef _GAME_H
#define _GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Splashscreen.h"
#include <unordered_map>
#include "Button.h"
#include "ResourceManager.h"
#include "playingState.h"
#include <sstream>
enum GameState { Uninitialized, ShowingSplash, ShowingMenu, Intro,
	Playing, Deploying, PlayingMission, EndMission, Exiting };

class game
{
private:
	sf::RenderWindow gameWindow;
	ResourceManager resMgr;
	SplashScreen splashScreen;
	playingState playState;
	bool musicInit;
	bool setup;
	bool switchingStates;
	sf::Clock updateClock;
	sf::Clock frameClock;
	std::vector<int> avgFrameCounter;
	button FPS;
	sf::Time FixedStep;
	sf::Time ElapsedTime;
	int frameCount;
	int updateCount;
	int updateTime;
	float updateNext;
	int frameTime;
	int frameNext;
public:
	bool debug;
	game();
	void start();
	void setGameState(GameState state, bool Setup = false);
	void fixedUpdate();
	void handleInput();
	void draw();
	void setupState();
	void gameLoop();
	GameState gameState;

};
#endif