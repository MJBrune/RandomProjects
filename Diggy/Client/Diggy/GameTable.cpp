#include "GameTable.h"

void GameTable::Start(unsigned int sizeX, unsigned int sizeY)
{
	srand ( time(NULL) );
	_gameTable.clear();
	for ( int i = 0; i <= sizeX-1; i++)
	{
		for ( int j = 0; j <= sizeY-1; j++)
		{
			bool satisfied = false;
			while(!satisfied)
			{
				switch((rand() % 3)+1)
				{
				case 1:
					_gameTable.emplace_back(std::make_shared<Blox>(Blox::Type::Dirt, Item::Type(rand() % 5)));
					satisfied = true;
					numberOfDirt++;
					break;
				case 2:
					_gameTable.emplace_back(std::make_shared<Blox>(Blox::Type::Grass, Item::Type(rand() % 5)));
					satisfied = true;
					numberOfGrass++;
					break;
				case 3:
					_gameTable.emplace_back(std::make_shared<Blox>(Blox::Type::Rock, Item::Type(rand() % 5)));
					numberOfRocks++;
					satisfied = true;
					break;
				}
			}
			 _gameTable.at(_gameTable.size()-1)->SetPosition(TABLEOFFSETW+i*30, TABLEOFFSETH+j*30);
			 _gameTable.at(_gameTable.size()-1)->bBox.left = TABLEOFFSETW+i*30;
			 _gameTable.at(_gameTable.size()-1)->bBox.top = TABLEOFFSETH+j*30;
			 _gameTable.at(_gameTable.size()-1)->bBox.width = (TABLEOFFSETW+i*30)+30;
			 _gameTable.at(_gameTable.size()-1)->bBox.height = (TABLEOFFSETH+j*30)+30;
		}
	}
}

void GameTable::Draw(sf::RenderWindow& renderWindow)
{
	for (int i = 0; i < _gameTable.size(); i++)
	{
		_gameTable.at(i)->Draw(renderWindow);
	}        
	
	for (int i = 0; i < _gameTable.size(); i++)
	{
		_gameTable.at(i)->DrawItem(renderWindow);
	}       
}

void GameTable::ifClick(int x, int y, Player* player)
{
	for (int i = 0; i < _gameTable.size(); i++)
	{          
		if( 
			_gameTable.at(i)->bBox.height > y 
			&& _gameTable.at(i)->bBox.top < y 
			&& _gameTable.at(i)->bBox.left < x 
			&& _gameTable.at(i)->bBox.width > x
			)
		{
			_gameTable.at(i)->ifClicked(player);
		}
	}
}