#include "Connect.h"

Connection::Connection(std::string ip)
	:_ip(ip)
{
}

void Connection::uploadScore(Player* player1)
{
	sf::Packet _packet;
	_packet << 
		(int)Type::score <<
		player1->Heart <<
		player1->Gold <<
		player1->Gem <<
		player1->GetName();
	_socket.send(_packet);
}

void Connection::downloadScore(Connection::Type type, std::vector<Player>& leaderBoard)
{
	sf::Packet _packet;
	sf::Packet _sendPacket;
	std::string name;
	int players;
	int packetType;
	int item;
	_sendPacket << type;
	_socket.send(_sendPacket);
	_socket.receive(_packet);
	std::cout << _packet << std::endl;

	_packet >> packetType;
	_packet >> players;
	std::cout << players << " " << packetType << std::endl;
	switch(packetType)
	{
	case Connection::Type::hearts:
		for (int i = 0; i < players; i++)
		{
			_packet >> item;
			Player* player = new Player(0,item,0,0);
			_packet >> name;
			player->SetName(name);
			std::cout << item << " " << name << std::endl;
			leaderBoard.push_back(*player);
		}
		break;
	case Connection::Type::gold:
		for (int i = 0; i < players; i++)
		{
			_packet >> item;
			Player* player = new Player(0,0,item,0);
			_packet >> name;
			player->SetName(name);
			std::cout << item << " " << name << std::endl;
			leaderBoard.push_back(*player);
		}
		break;
	case Connection::Type::gems:
		for (int i = 0; i < players; i++)
		{
			_packet >> item;
			Player* player = new Player(0,0,0,item);
			_packet >> name;
			player->SetName(name);
			std::cout << item << " " << name << std::endl;
			leaderBoard.push_back(*player);
		}
		break;
	}
}