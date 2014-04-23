#include "Globals.h"
#ifndef MB_PLAYER_H
#define MB_PLAYER_H
#include "Mech.h"
#include <SFML/Network.hpp>
class Player
{
public:
	std::vector <Mech> m_mechs;

	Player()
	{
	}

	Player(int playerID, std::vector <Mech> mechs, std::string name)
		:m_playerID(playerID),
		m_mechs(mechs),
		m_playerName(name)
	{}

	void WriteToPacket(sf::Packet &packet)
	{
		packet << m_playerID;
		packet << m_mechs.size();
		packet << m_playerName;
		for (int i = 0; i <= m_mechs.size(); i++)
			m_mechs[i].WriteToPacket(packet);
	}

	void ReadFromPacket(sf::Packet &packet)
	{
		int mechSize = 0;
		packet >> m_playerID;
		packet >> mechSize;
		packet >> m_playerName;
		for (int i = 0; i <= mechSize; i++)
			m_mechs[i].ReadFromPacket(packet);
	}

private:
	int m_playerID;
	std::string m_playerName;
};
#endif