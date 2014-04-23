#ifndef MAP_TILE
#define MAP_TILE
#include <SFML/Network.hpp>

class Mech;

class Tile
{
public:
	enum Type
	{
		Plains = 0,
		LWoods,
		HWoods,
		Stone,
	};

	Type MyType;
	bool Solid;
	
	int	GridX, GridY;


	bool			ContainsMech;
	unsigned char	MechType;
	bool			MechIsMine;

	Mech *MyMech;

	Tile(const Type &tileType, const bool &solid);

	void WriteToPacket(sf::Packet &packet);
	void ReadPacket(sf::Packet &packet);
private:
protected:
};

#endif