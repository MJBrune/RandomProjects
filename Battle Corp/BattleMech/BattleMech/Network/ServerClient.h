#ifndef NET_SVRCLIENT
#define NET_SVRCLIENT
#include <SFML/Network.hpp>
#include "../Player.h"


namespace Network
{
	//This will hold other data soon
	struct ServerClient
	{
		ServerClient(sf::SocketTCP &sock, const char &i)
		{
			socket			= &sock;
			id				= i;
			mechChoice		= 0;

		}
		ServerClient()
		{
			socket		= NULL;
			id			= 0;
			mechChoice	= 0;
		}

		void WriteToPacket(sf::Packet &packet)
		{
			packet << id;
			packet << mechChoice;
		}

		void ReadFromPacket(sf::Packet &packet)
		{
			packet >> id;
			packet >> mechChoice;
		}

		sf::SocketTCP *socket;
		unsigned char id, mechChoice;
		Player myPlayer;
	};
}
#endif