#include "Blox.h"
#include <vector>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#define TABLEOFFSETW 100
#define TABLEOFFSETH 150
class GameTable
{
public:
	void Start(unsigned int sizeX, unsigned int sizeY);
	void Draw(sf::RenderWindow& renderWindow);
	void ifClick(int x, int y, Player* player);
	int numberOfRocks;
	int numberOfDirt;
	int numberOfGrass;
private:
	std::vector<std::shared_ptr<Blox>> _gameTable;
};