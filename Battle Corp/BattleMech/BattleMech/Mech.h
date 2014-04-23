#include "Globals.h"

#ifndef MB_MECH_H
#define MB_MECH_H

#include "Weapon.h"
#include "Tile.h"
#include "TileMap.h"
#include <SFML/Network.hpp>
#define WEAPMIN 0
#define WEAPMAX 1

enum StockMech
{
	RLight,
	RMedium,
	RHeavy,
	BLight,
	BMedium,
	BHeavy
	//to be replaced with actual mech names
};
enum Direction
{
	North = 0,
	NorthWest = 60,
	NorthEast = -60,
	SouthWest = 120,
	SouthEast = -120,
	South = 180
};

class Mech
{
public:

	bool IsMine;
	bool canMove;
	bool isDead;
	bool isMoving;
	bool isRotating;
	bool initialMove;
	std::vector <Weapon *> m_weapons;

	Mech(StockMech mechType, TileMap *map, Tile* initialTile, Direction facing)
		:m_mechType(mechType),
		m_gameMap(map),
		m_mechTile(initialTile),
		m_facingDirection(facing)
	{
		IsMine	= false;
		canMove = true;
		isDead = false;
		isMoving = false;
		isRotating = false;
		initialMove = true;
		m_GridX = 0;
		m_GridY = 0;
		SetMechType(mechType);
		if(m_mechTile != NULL)
		{
			Place(m_mechTile->GridX,m_mechTile->GridY, true);
		}

	}

	void SetMechType(const StockMech &mechType);

	void die(){isDead = true;}

	void IsHit(location loc, Weapon weap);

	void LostLimb(location loc);

	void LostWeapon(location loc);

	bool CanMoveTo(int x, int y);

	void Move(int x, int y);

	int Distance(const Tile * TileToMoveTo);

	int HitModifier(Mech * MechTarget, Weapon * weap);

	int Fire(Mech * MechTarget, Weapon * weap);

	int GetHitLocation(Mech * MechTarget, Weapon * weap);

	void Place(int x, int y, bool instant = false);

	void Update(float timespan);

	void Init();

	void Render(sf::RenderTarget &target);

	int GetMovement()
		{return m_lastMovement;}

	Tile* GetTile()
		{return m_mechTile;}

	float checkAngles(Mech * MechFiring, Mech * MechTarget);

	void SetFacing(Direction facing);

	StockMech GetType()
		{return m_mechType;}

	const Direction& GetFacing(){return m_facingDirection;}

	const void WriteToPacket(sf::Packet &packet);

	void ReadFromPacket(sf::Packet &packet);

	int* getArmor() {return m_armor;}
	
private:
	int m_armor[6];
	int m_weaponSlots;
	int m_movement;
	int m_lastMovement;
	int m_GridX,m_GridY;
	location hitLocation;
	sf::Sprite m_mechSprite;
	StockMech m_mechType;
	sf::Image m_mech;
	TileMap *m_gameMap;
	Tile* m_mechTile;
	sf::Vector2f m_pos;
	Direction m_facingDirection;
	float m_rot;
};
#endif