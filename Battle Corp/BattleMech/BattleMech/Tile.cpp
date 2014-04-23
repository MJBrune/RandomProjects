#include "Tile.h"
#include "Mech.h"

	Tile::Tile(const Type &tileType, const bool &solid)
	{
		GridX			= 0;
		GridY			= 0;

		MyType			= tileType;
		Solid			= solid;

		ContainsMech	= false;
		MechType		= 0;
		MechIsMine		= false;

		MyMech			= 0;
	}

	void Tile::WriteToPacket(sf::Packet &packet)	//Write data to a packet that can be sent over the network
	{
		packet << (unsigned char&)MyType;
		packet << Solid;
		packet << ContainsMech;
		packet << MechType;
	}

	void Tile::ReadPacket(sf::Packet &packet)
	{
		packet >> (unsigned char&)MyType;
		packet >> Solid;
		packet >> ContainsMech;
		packet >> MechType;
	}