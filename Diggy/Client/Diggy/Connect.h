#pragma once
#include <SFML\Network.hpp>
#include "Player.h"
#include <list>

class Connection
{
private:
	sf::TcpSocket _socket;
	sf::IpAddress _ip;
public:
	enum Type { score, hearts, gold, gems};
	Connection(std::string ip);
	void uploadScore(Player* player1);
	void downloadScore(Connection::Type type, std::vector<Player>& leaderBoard);
	void openConnection(){_socket.connect(_ip,27099);}
	void closeConnection(){_socket.disconnect();}	
};