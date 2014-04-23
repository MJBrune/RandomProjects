#include "Globals.h"

#ifndef MB_WEAP_H
#define MB_WEAP_H
#include <SFML/Network.hpp>
enum location
{
	LEFTLEG,
	RIGHTLEG,
	LEFTARM,
	RIGHTARM,
	TORSO,
	COCKPIT
};
const std::string loctionstr[] = {"Left Leg", "Right Leg", "Left Arm", "Right Arm", "Body", "Cockpit"};
class Weapon
{
public:
	Weapon(int dmg = 0, int minRange = 0, int shortMinRange = 0, int m_shortMaxRange = 0, int maxrange = 0, 
		std::string weap = "LASER", location WeaponLocation = TORSO, int ammo = 1)
		: m_damage(dmg),
		m_minRange(minRange),
		m_shortMinRange(shortMinRange),
		m_maxRange(maxrange),
		m_weaponName(weap),
		m_WeaponLocation(WeaponLocation),
		m_ammoPerShot(ammo)
		{canFire = true;}
	bool canFire;
	int GetDamage()
		{return m_damage;}
	int GetAmmo()
		{return m_ammoPerShot;}
	int GetMinRange()
		{return m_minRange;}
	int* GetShortRange()
		{int *shortrange = new int[2]; shortrange[0] = m_shortMinRange; shortrange[1] = m_shortMaxRange; return shortrange;}
	int GetMaxRange()
		{return m_maxRange;}
	location GetLocation()
		{return m_WeaponLocation;}
	std::string GetWeaponName()
		{return m_weaponName;}
		
	
	void WriteToPacket(sf::Packet &packet)
	{
		packet  << (unsigned char&)m_WeaponLocation;
		packet  << m_damage;
		packet	<< m_minRange;
		packet	<< m_shortMinRange;
		packet	<< m_shortMaxRange;
		packet	<< m_maxRange;
		packet	<< m_ammoPerShot;
		packet  << canFire;
		packet	<< m_weaponName;
	}

	void ReadFromPacket(sf::Packet &packet)
	{
		packet  >> (unsigned char&)m_WeaponLocation;
		packet  >> m_damage;
		packet	>> m_minRange;
		packet	>> m_shortMinRange;
		packet	>> m_shortMaxRange;
		packet	>> m_maxRange;
		packet	>> m_ammoPerShot;
		packet  >> canFire;
		packet  >> m_weaponName;
	}

private:
	int m_damage;
	int m_minRange;
	int m_shortMinRange;
	int m_shortMaxRange;
	int m_maxRange;
	int m_ammoPerShot;
	int shortrange[2];
	location m_WeaponLocation;
	std::string m_weaponName;
};
#endif