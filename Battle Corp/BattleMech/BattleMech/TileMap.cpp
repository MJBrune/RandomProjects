#include "Globals.h"
#include "TileMap.h"
#include "Mech.h"

	TileMap::TileMap()
	{
		SizeX = 0;
		SizeY = 0;
	}

	TileMap::TileMap(const unsigned int &width, const unsigned int &height)
	{
		CreateBlankMap(width, height);
	}

	void TileMap::CreateBlankMap(const unsigned int &width, const unsigned int &height) 
	{
		SizeX = width;
		SizeY = height;

		Tiles.clear();
		for(unsigned int y = 0; y < height; y++)
		{
			for(unsigned int x = 0; x < width; x++)
			{
				Tile add(Tile::Plains, false);
				add.GridX = x;
				add.GridY = y;
				Tiles.push_back(add);
			}
		}
	}

	void TileMap::CreateRandomMap(const unsigned int &width, const unsigned int &height)
	{
		SizeX = width;
		SizeY = height;
		Tiles.clear();
		srand(time(NULL));
		for(unsigned int y = 0; y < height; y++)
		{
			for(unsigned int x = 0; x < width; x++)
			{
				
				Tile add(Tile::Type(rand() % 5), false);
				add.GridX = x;
				add.GridY = y;
				Tiles.push_back(add);
			}
		}
	}

	Tile &TileMap::operator ()(const int &x, const int&y)
	{
		return Tiles[(y * SizeX) + x];
	}
	void TileMap::getMyMech()
	{
		for(int i = 0; i < Tiles.size(); i++)
		{
			if(Tiles[i].ContainsMech && Tiles[i].MyMech != 0 && Tiles[i].MyMech->IsMine)
				m_myMech = Tiles[i].MyMech;
		}
	}
	void TileMap::Render(sf::RenderTarget &target)
	{
		getMyMech();

		std::vector <Mech*> Mechs;

		sf::Image &img = hexImage;

		sf::Sprite shape;
		shape.SetImage(img);
		sf::String location;
		std::string locationnumber;

		for(int i = 0; i < Tiles.size(); i++)
		{
			// Added Offsets for centering items
			// + 180 , + 21 (the offsets for a centered map)
			shape.SetCenter(shape.GetSize().x / 2, shape.GetSize().y / 2);
			shape.SetPosition(ToWorldCoord(Tiles[i].GridX, Tiles[i].GridY));

			std::stringstream sstream;
			//sstream << (10 - Tiles[i].GridY - (Tiles[i].GridX / 2) + Tiles[i].GridX)<< "," << (10 - Tiles[i].GridY - (Tiles[i].GridX / 2));
			sstream << Tiles[i].GridX << "," << Tiles[i].GridY;
			locationnumber = sstream.str();
			sstream.clear();
			location.SetText(locationnumber);
			
			location.SetScale(.4f,.4f);

			location.SetCenter(location.GetSize() / 2, 0);
			location.SetPosition
				(
				shape.GetPosition().x,
				shape.GetPosition().y + 15
				);

			switch(Tiles[i].MyType)
			{
			default:
			case Tile::Plains:
				shape.SetImage(plains);
				shape.SetColor(sf::Color(255,255,255));
				break;
			case Tile::LWoods:
				shape.SetImage(lWoods);
				shape.SetColor(sf::Color(255,255,255));
				break;
			case Tile::HWoods:
				shape.SetImage(hWoods);
				shape.SetColor(sf::Color(255,255,255));
				break;
			case Tile::Stone:
				shape.SetImage(rocks);
				shape.SetColor(sf::Color(255,255,255));
				break;
			}
			if(m_myMech->CanMoveTo(Tiles[i].GridX,Tiles[i].GridY))
			{
				shape.SetColor(sf::Color::Green);
			}
			if(Tiles[i].ContainsMech && Tiles[i].MyMech != 0)
			{
				Mechs.push_back(Tiles[i].MyMech);
			}
			
			target.Draw(shape);
			target.Draw(location);
		}
		for(int i = 0; i < Mechs.size(); i++){
			Mechs[i]->Render(target);
		}
	}

	void TileMap::Update(float timespan)
	{
		sf::Vector2f mousePos(MainGame.GetWindow().GetInput().GetMouseX(), MainGame.GetWindow().GetInput().GetMouseY());

	}


	const bool TileMap::TileExists(const int&x, const int&y)
	{
		if(x >= 0 && x < SizeX)
		{
			if(y >= 0 && y < SizeY)
			{
				return true;
			}
		}
		return false;
	}


	//Network Related
	void TileMap::WriteToPacket(sf::Packet &packet)
	{
		packet << SizeX;
		packet << SizeY;
		for(int i = 0; i < Tiles.size(); i++)
		{
			Tiles[i].WriteToPacket(packet);
		}
	}

	//Network Related
	void TileMap::ReadPacket(sf::Packet &packet)
	{
		packet >> SizeX;
		packet >> SizeY;

		CreateBlankMap(SizeX, SizeY);
		
		for(int i = 0; i < Tiles.size(); i++)
		{
			Tiles[i].ReadPacket(packet);
		}
	}


	const sf::FloatRect TileMap::TileBox(const int &x, const int &y)
	{
		sf::FloatRect ret(0,0,0,0);

		if(TileExists(x,y))
		{
			sf::Vector2f pos((float)x * 59, (float)y * hexImage.GetHeight() + 21);
			if(x % 2 == 0)
			{
				pos.y += 33;
			}
			ret = sf::FloatRect(pos.x, pos.y,pos.x + hexImage.GetWidth(), pos.y + hexImage.GetHeight());
		}

		return ret;
	}