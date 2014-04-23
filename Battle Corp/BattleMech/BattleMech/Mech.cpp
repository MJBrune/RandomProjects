#include "TileMap.h"
#include "Mech.h"
#include "States/BattleMech.h"
#include "States/MainMenu.h"
#include "HelperFunctions.h"

void Mech::Init(){

	if(IsMine)
	{
		m_mechSprite.SetColor(sf::Color(150,255,150));
	}
	else
	{
		m_mechSprite.SetColor(sf::Color(255,150,150));
	}
}

void Mech::IsHit(location loc, Weapon weap)
{
	int crit = 0;
	srand ( time(NULL) );

	m_armor[loc] -= weap.GetDamage();
	std::cout << "you hit the enemy's " << loc << " for " << weap.GetDamage() << std::endl;
	for (int i = 0; i <= COCKPIT; i++)
		std::cout << "Enemy: Armor[" << i << "]: " << m_armor[i] << std::endl;
	//m_armor[loc] -= 100;
	// if any arms and legs gets blown off then overload the damage
	// to the torso and remove the limb.
	if ( m_armor[loc] <= 0 )
	{
		m_armor[TORSO] += m_armor[loc];
		LostLimb(loc);
	}

	if ( m_armor[loc] > 0 )
	{
		crit = ((rand() % 6)+1) + ((rand() % 6)+1);
		if (crit == 1)
		{
			crit = rand() % 11 + 1;
			if (crit = 11)
			{
				LostLimb(loc);
			}
			else if ( crit <= 8)
			{
				LostWeapon(loc);
			}
			std::cout << "Critical Hit!: " << loc << " crit roll: " << crit;
		}
	}
	if (m_armor[TORSO] <= 0 || m_armor[COCKPIT] <= 0)
		die();
}

void Mech::SetMechType(const StockMech &mechType)
{
		m_mechType = mechType;
		m_weapons.clear();

		//Quick and dirty paste-in to get it running
		switch(mechType)
		{
		default:
		case 0:
			m_mechSprite.SetImage(m_mechLRImage);
			break;
		case 1:
			m_mechSprite.SetImage(m_mechMRImage);
			break;
		case 2:
			m_mechSprite.SetImage(m_mechHRImage);
			break;
		case 3:
			m_mechSprite.SetImage(m_mechLBImage);
			break;
		case 4:
			m_mechSprite.SetImage(m_mechMBImage);
			break;
		case 5:
			m_mechSprite.SetImage(m_mechHBImage);
			break;
		}
		m_mechSprite.SetCenter(m_mechSprite.GetImage()->GetWidth()/2,m_mechSprite.GetImage()->GetHeight()/2);

		switch(mechType)
		{
		case RLight:
			m_movement = 6;
			m_armor[TORSO] = 10;
			m_armor[LEFTLEG] = 7;
			m_armor[RIGHTLEG] = 7;
			m_armor[LEFTARM] = 7;
			m_armor[RIGHTARM] = 7;
			m_armor[COCKPIT] = 6;
			m_weaponSlots = 5;
			m_weapons.push_back(new Weapon(3, 1, 1, 5, 6, "Heavy Laser", RIGHTARM));
			for (int i = 1; i <= 4; i++)
				m_weapons.push_back(new Weapon(2, 1, 1, 3, 4, "Medium Laser", TORSO));
			m_mech.LoadFromFile("Resources/RLightLow.png");
			break;
		case RMedium:
			m_movement = 4;
			m_armor[TORSO] = 16;
			m_armor[LEFTLEG] = 11;
			m_armor[RIGHTLEG] = 11;
			m_armor[LEFTARM] = 11;
			m_armor[RIGHTARM] = 11;
			m_armor[COCKPIT] = 6;
			m_weaponSlots = 5;
			m_weapons.push_back(new Weapon(5, 1, 2, 8,10,"Heavy Rifle", RIGHTARM));
			for (int i = 1; i <= 2; i++)
				m_weapons.push_back(new Weapon(2, 1, 1, 3, 4, "Medium Laser", TORSO));
			m_weapons.push_back(new Weapon(1, 1, 2, 6, 14, "Rocket Pack", RIGHTARM, 6));
			m_mech.LoadFromFile("Resources/RMediumLow.png");

			break;
		case RHeavy:
			m_movement = 2;
			m_armor[TORSO] = 22;
			m_armor[LEFTLEG] = 15;
			m_armor[RIGHTLEG] = 15;
			m_armor[LEFTARM] = 15;
			m_armor[RIGHTARM] = 15;
			m_armor[COCKPIT] = 6;
			m_weaponSlots = 6;
			// Load Heavy Mech here todo
			m_mech.LoadFromFile("Resources/RHeavyLow.png");
			for (int i = 0; i <= 2; i++)
				m_weapons.push_back(new Weapon(2, 1, 1, 3, 4, "Medium Laser", TORSO));
			m_weapons.push_back(new Weapon(7, 1, 1, 4, 5, "Heavy Cannon", RIGHTARM));
			m_weapons.push_back(new Weapon(7, 1, 1, 4, 5, "Heavy Cannon", LEFTARM));
			m_weapons.push_back(new Weapon(4, 1, 4, 10,12, "Guided Rocket", TORSO));
			break;
		case BLight:
			m_movement = 6;
			m_armor[TORSO] = 10;
			m_armor[LEFTLEG] = 7;
			m_armor[RIGHTLEG] = 7;
			m_armor[LEFTARM] = 7;
			m_armor[RIGHTARM] = 7;
			m_armor[COCKPIT] = 6;
			m_weaponSlots = 5;
			m_weapons.push_back(new Weapon(3, 1, 1, 5, 6, "Heavy Laser", RIGHTARM));
			for (int i = 1; i <= 4; i++)
				m_weapons.push_back(new Weapon(2, 1, 1, 3, 4, "Medium Laser", TORSO));
			m_mech.LoadFromFile("Resources/BLightLow.png");
			break;
		case BMedium:
			m_movement = 4;
			m_armor[TORSO] = 16;
			m_armor[LEFTLEG] = 11;
			m_armor[RIGHTLEG] = 11;
			m_armor[LEFTARM] = 11;
			m_armor[RIGHTARM] = 11;
			m_armor[COCKPIT] = 6;
			m_weaponSlots = 5;
			m_weapons.push_back(new Weapon(5, 1, 2, 8,10,"Heavy Rifle", RIGHTARM));
			for (int i = 1; i <= 2; i++)
				m_weapons.push_back(new Weapon(2, 1, 1, 3, 4, "Medium Laser", TORSO));
			m_weapons.push_back(new Weapon(1, 1, 2, 6, 14, "Rocket Pack", RIGHTARM, 6));
			m_mech.LoadFromFile("Resources/BMediumLow.png");

			break;
		case BHeavy:
			m_movement = 2;
			m_armor[TORSO] = 22;
			m_armor[LEFTLEG] = 15;
			m_armor[RIGHTLEG] = 15;
			m_armor[LEFTARM] = 15;
			m_armor[RIGHTARM] = 15;
			m_armor[COCKPIT] = 6;
			m_weaponSlots = 6;
			// Load Heavy Mech here todo
			m_mech.LoadFromFile("Resources/BHeavyLow.png");
			for (int i = 0; i <= 2; i++)
				m_weapons.push_back(new Weapon(2, 1, 1, 3, 4, "Medium Laser", TORSO));
			m_weapons.push_back(new Weapon(7, 1, 1, 4, 5, "Heavy Cannon", RIGHTARM));
			m_weapons.push_back(new Weapon(7, 1, 1, 4, 5, "Heavy Cannon", LEFTARM));
			m_weapons.push_back(new Weapon(4, 1, 4, 10,12, "Guided Rocket", TORSO));
			break;
		}
}

void Mech::LostLimb(location loc)
{
	if ( loc == COCKPIT || loc == TORSO )
		die();
	for (int i = 0; i <= m_weapons.size()-1; i++)
	{
		if ( m_weapons[i]->GetLocation() == loc)
		{
			m_weapons.erase(m_weapons.begin() + i);
			m_weaponSlots -= 1;
		}
	}
}

void Mech::LostWeapon(location loc)
{
	int weapon = 0;
	int currentSlots = m_weaponSlots;
	int found = 0;
	for (int i = 0; i <= m_weapons.size()-1; i++)
	{
		if ( m_weapons[i]->GetLocation() == loc)
		{
			found += 1;
		}
	}
	srand ( time(NULL) );
	do
	{
		weapon = rand() % m_weaponSlots;
		if ( m_weapons[weapon]->GetLocation() == loc)
		{
			std::cout << "Lost Weapon: " << m_weapons[weapon]->GetWeaponName() 
				<< "at: " << loctionstr[loc] << std::endl;
			m_weapons.erase(m_weapons.begin() + weapon);
			m_weaponSlots -= 1;
		}
	}while(m_weaponSlots == currentSlots || found == 0);
}

bool Mech::CanMoveTo(int x, int y){
	int lastMovement = Distance(&(*m_gameMap)(x,y));
	if (lastMovement <= m_movement && canMove)
	{
		return true;
	} else {
		return false;
	}
}

void Mech::Move(int x, int y)
{
	if (CanMoveTo(x, y))
	{
		if (m_mechTile != NULL)
			canMove = false;

		if(initialMove)
		{
			Place(x, y, true);
			initialMove = false;
		} 
		else 
		{
			m_lastMovement = Distance(&(*m_gameMap)(x,y));
			Place(x,y);
		}


		m_mechTile = &(*m_gameMap)(x,y);
		SetFacing(m_facingDirection);
	}
}

int Mech::Distance(const Tile * TileToMoveTo)
{
	//the following calculates the distance between two tiles.
	if (m_mechTile == NULL) return 0;
	int x = ((m_mechTile->GridX) - TileToMoveTo->GridX);
	int y = m_mechTile->GridY - TileToMoveTo->GridY;
	int a = pow(float(x), float(2));
	int b = pow(float(y), float(2));
	int c = sqrt(float(a + b));
	return c;
}

void Mech::Place(int x, int y, bool instant)
{
	m_GridX = x;
	m_GridY = y;

	if(m_mechTile != NULL)
	{
		m_mechTile->ContainsMech	= false;
		m_mechTile->MyMech			= 0;
	}
	if (instant) m_pos = m_gameMap->ToWorldCoord(m_GridX, m_GridY);

	m_mechTile					= &(*m_gameMap)(x,y);
	isMoving					= true;
//	m_lastMovement				= 0;
	m_mechTile->ContainsMech	= true;
	m_mechTile->MechType		= m_mechType;
	m_mechTile->MechIsMine		= IsMine;
	m_mechTile->MyMech			= this;
}

int Mech::HitModifier(Mech * MechTarget, Weapon * weap)
{
	int modifierToHit = 0;

	if ( weap->GetWeaponName().find("Laser") != weap->GetWeaponName().npos ||
		weap->GetWeaponName().find("Cannon") != weap->GetWeaponName().npos)
	{
		if (this->Distance(MechTarget->GetTile()) < weap->GetShortRange()[WEAPMIN] )
			modifierToHit += 2;
	}

	if ( weap->GetWeaponName().find("Rifle") != weap->GetWeaponName().npos )
	{
		if (this->Distance(MechTarget->GetTile()) < weap->GetShortRange()[WEAPMIN] )
			modifierToHit += 1;
		if (this->Distance(MechTarget->GetTile()) > weap->GetShortRange()[WEAPMAX] )
			modifierToHit += 2;
	}

	if ( weap->GetWeaponName().find("Rocket Pack") != weap->GetWeaponName().npos )
	{
		if (this->Distance(MechTarget->GetTile()) < weap->GetShortRange()[WEAPMIN] )
			modifierToHit += 2;
		if (this->Distance(MechTarget->GetTile()) > weap->GetShortRange()[WEAPMAX] )
			modifierToHit += 1;
	}

	if ( weap->GetWeaponName().find("Guided Rocket") != weap->GetWeaponName().npos )
	{
		if (this->Distance(MechTarget->GetTile()) < weap->GetShortRange()[WEAPMIN] )
			modifierToHit += 2;
		if (this->Distance(MechTarget->GetTile()) > weap->GetShortRange()[WEAPMAX] )
			modifierToHit += 1;
	}

	if ( m_lastMovement > 0 )
		modifierToHit += 2;

	for (int i = 1; i <= 8; i+=2)
	{
		if (MechTarget->GetMovement() > i)
		{
			modifierToHit += 1;
		}
	}

	if ( MechTarget->GetTile()->MyType == Tile::Type::LWoods )
		modifierToHit += 1;
	else if ( MechTarget->GetTile()->MyType == Tile::Type::HWoods )
		modifierToHit += 2;

	return modifierToHit;
}

int Mech::Fire(Mech * MechTarget, Weapon * weap)
{
	int hitRoll = 0;
	int hits = 1;
	if (this->Distance(MechTarget->GetTile()) > weap->GetMaxRange())
	{
		weap->canFire = false;
		std::cout << "Mech out of maximum range.\nMax Range is: " << weap->GetMaxRange() << std::endl;
		return -1;
	}
	if (this->Distance(MechTarget->GetTile()) < weap->GetMinRange())
	{
		weap->canFire = false;
		std::cout << "Mech out of minimum range.\nMin Range is: " << weap->GetMinRange() << std::endl;
		return -1;
	}
	if (checkAngles(this, MechTarget) >= 90)
	{
		weap->canFire = false;
		std::cout << "Mech out of angle range." << std::endl;
		return -1;
	}
	if (!weap->canFire)
	{
		std::cout << "Mech can't fire." << std::endl;
		return -1;
	}
	if (checkAngles(MechTarget, this) > 90)
	{
		hits = 2;
		std::cout << "Double hit!" << std::endl;
	}
	weap->canFire = false;
	for (int i = 0; i < hits; i++)
	{
		for (int j = 0; j < weap->GetAmmo(); j++)
		{
			int locRoll = ((rand() % 6));
			hitRoll = ((rand() % 6)+1) + ((rand() % 6)+1);
			int mod = HitModifier(MechTarget, weap);
			if (hitRoll >= mod)
			{
				std::cout << "You have hit.\nYou Rolled: " << hitRoll << "\nYou Needed: " << mod << std::endl;
				MechTarget->IsHit((location)locRoll, *weap);
				for (int i = 0; i <= COCKPIT; i++)
				std::cout << "You: Armor[" << i << "]: " << m_armor[i] << std::endl;
			}
			else
			{
				std::cout << "You have missed.\nYou Rolled: " << hitRoll << "\nYou Needed: " << mod << std::endl;
			}
		}
	}
	return hitRoll;
}

float Mech::checkAngles(Mech * MechFiring, Mech * MechTarget)
{
	float playerPosX = MechFiring->GetTile()->GridX * 59;
	float playerPosY = MechFiring->GetTile()->GridY * 66 + 21;
	if (MechFiring->GetTile()->GridX % 2 == 0)
		playerPosY += 33;
	float targetPosX = MechTarget->GetTile()->GridX * 59;
	float targetPosY = MechTarget->GetTile()->GridY * 66 + 21;
	if (MechTarget->GetTile()->GridX % 2 == 0)
		targetPosY += 33;
	float diffPosX = playerPosX - targetPosX;
	float diffPosY = playerPosY - targetPosY;
	float radRotation = (float)atan2(diffPosY, diffPosX);
	float degRotation = 90 - (radRotation * (180 / 3.14159265359));

	//New stuff
	float totalAngle = abs(degRotation - MechFiring->GetFacing());
	if(totalAngle > 180) 
		totalAngle = 360 - totalAngle;

	//Change to totalAngle
	std::cout << "Angle: " << totalAngle << std::endl
		<< "Player Coords: " << playerPosX << "," << playerPosY << std::endl
		<< "Target Coords: "<< targetPosX << ","  << targetPosY << std::endl;

	//Change to totalAngle
	return totalAngle;
}

void Mech::SetFacing(Direction facing)
{
	m_facingDirection = facing;
	isRotating = true;
}
	
void Mech::Update(float timespan)
{
	if(isMoving){

		sf::Vector2f goalPos = m_gameMap->ToWorldCoord(m_GridX, m_GridY);

		//If there's less than a pixel left, move directly into place and stop moving
		if(abs(goalPos.x - m_pos.x) < 1 && abs(goalPos.y - m_pos.y) < 1){
			m_pos = goalPos;
			isMoving = false;
		} else {
		
			//Create a normal vector
			sf::Vector2f normGoalPos;

			normGoalPos.x = (goalPos.x - m_pos.x);
			normGoalPos.y = (goalPos.y - m_pos.y);

			float moveLength = sqrt((normGoalPos.x * normGoalPos.x) + (normGoalPos.y * normGoalPos.y));
			normGoalPos.x = normGoalPos.x / moveLength;
			normGoalPos.y = normGoalPos.y / moveLength;

			//Movement speed. Pixels/s
			float moveSpeed = 100;

			if(moveLength < 50){
				moveSpeed = 50;
			}

			//Move
			m_pos.x += normGoalPos.x * moveSpeed * timespan;
			m_pos.y += normGoalPos.y * moveSpeed * timespan;
		}
	}

	if(isRotating){

		if(abs(m_facingDirection - m_rot) < 1){
			m_rot = m_facingDirection;
		} else {
			float goalRot = m_facingDirection;
			if(goalRot < 0) goalRot += 360;
			float newRot = (goalRot - m_rot) * timespan * 2;

			m_rot += newRot;
		}
		
		
		m_mechSprite.SetRotation(m_rot);
	}

}

void Mech::Render(sf::RenderTarget &target)
{
	m_mechSprite.SetPosition(m_pos);

	target.Draw(m_mechSprite);
}


const void Mech::WriteToPacket(sf::Packet &packet)
	{
		packet << (unsigned char&)m_mechType;

		packet << m_GridX;
		packet << m_GridY;
		packet << (signed int&)m_facingDirection;
		

		for (int i = 0; i <= COCKPIT; i++)
			packet << m_armor[i];

		packet << (unsigned char)m_weaponSlots;
		packet << m_lastMovement;
		packet << m_movement;
		for (int i = 0; i < m_weaponSlots; i++)
			m_weapons[i]->WriteToPacket(packet);
	}

void Mech::ReadFromPacket(sf::Packet &packet)
	{
		packet >> (unsigned char&)m_mechType;
		
		packet >> m_GridX;
		packet >> m_GridY;

		packet >> (signed int&)m_facingDirection;

		for (int i = 0; i <= COCKPIT; i++)
			packet >> m_armor[i];

		packet >> (unsigned char&)m_weaponSlots;
		packet >> m_lastMovement;
		packet >> m_movement;
		m_weapons.clear();
		for (int i = 0; i < m_weaponSlots; i++)
		{
			Weapon *add = new Weapon();
			add->ReadFromPacket(packet);
			m_weapons.push_back(add);
		}
		
		if (m_armor[TORSO] <= 0 || m_armor[COCKPIT] <= 0)
			die();
		Move(m_GridX, m_GridY);
		SetFacing(m_facingDirection);
	}
