#ifndef MAP_TILEMAP
#define MAP_TILEMAP
#include "Tile.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class TileMap
{
public:
	TileMap();
	TileMap(const unsigned int &width, const unsigned int &height);
	void CreateBlankMap(const unsigned int &width, const unsigned int &height);
	void CreateRandomMap(const unsigned int &width, const unsigned int &height);
	Tile &operator ()(const int &x, const int&y);
	void Render(sf::RenderTarget &target);
	void Update(float timespan);
	const bool TileExists(const int&x, const int&y);
	const sf::FloatRect TileBox(const int&x, const int &y);
	//Network Related
	void WriteToPacket(sf::Packet &packet);
	//Network Related
	void ReadPacket(sf::Packet &packet);
	std::vector<Tile> Tiles;
	unsigned int SizeX,SizeY;
	Mech * m_myMech;
	void getMyMech();
	static sf::Image hexImage;
	
	sf::Vector2f ToGridCoord(int x, int y)
	{
		int yOffset = -21;

		if(x % 2 == 0){ yOffset += -22; }else{ yOffset = 0;}

		x = floor((float)x / 59);
		y = floor((float)(y + yOffset) / 66);

		return sf::Vector2f(x, y);
	}

	sf::Vector2f ToWorldCoord(int x, int y)
	{
		int yOffset = 21;
		
		if(x % 2 == 0){ yOffset += 33; }else{ yOffset += 0;}

		x = x * 59 + 37.5;
		y = (y * 66) + yOffset + 33;

		return sf::Vector2f(x, y);
	}
private:

	static sf::Image mechImages[5];
};

#endif
