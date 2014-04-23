#include <iostream>
#include <list>
#include <sys/types.h>
#include <unistd.h>
#include <SFML/Network.hpp>

#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


int main()
{
	sf::TcpListener _listener;
	_listener.listen(27099);
	int pid;
	std::cout << "hi" << std::endl;
	while (true)
	{
		sf::TcpSocket client;
		if (_listener.accept(client) == sf::Socket::Done)
		{
			pid = fork();

			if(pid != 0)
			{
				// A new client just connected!
				std::cout << "New connection received from " << client.getRemoteAddress() << std::endl;
				//doSomethingWith(client);
				//	MYSQL* test;
				sf::Packet _packet;
				if(client.receive(_packet) == sf::Socket::Done)
				{
					int packetType;
					_packet >> packetType;
					switch(packetType)
					{
					case 0:
						try
						{
							int heart, gold, gem;
							std::string playerName;
							_packet >> heart;
							_packet >> gold;
							_packet >> gem;
							_packet >> playerName;

							sql::Driver *driver;
							sql::Connection *con;
							sql::Statement *stmt;
							sql::ResultSet *res;
							sql::PreparedStatement *pstmt;

							// Create a connection
							driver = get_driver_instance();
							con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
							// Connect to the MySQL test database
							con->setSchema("diggy");
							stmt = con->createStatement();
							pstmt = con->prepareStatement("INSERT INTO leaderboard (heart, gold, gem, name, ip) VALUES(?, ?, ?, ?, ?)");
							pstmt->setInt(1, heart);
							pstmt->setInt(2, gold);
							pstmt->setInt(3, gem);
							pstmt->setString(4, playerName);
							pstmt->setString(5, client.getRemoteAddress().toString());
							pstmt->executeUpdate();
						}
						catch (sql::SQLException &e)
						{
						    std::cout << "ERROR WITH UPLOAD";
							std::cout << "# ERR: SQLException in " << __FILE__;
							std::cout << "(" << __FUNCTION__ << ") on line "
								<< __LINE__ << std::endl;
							std::cout << "# ERR: " << e.what();
							std::cout << " (MySQL error code: " << e.getErrorCode();
							std::cout << ", SQLState: " << e.getSQLState() <<
								" )" << std::endl;
						}
						break;
					case 1:
					std::cout << "CASE 1!!!!!" << std::endl;
					try
						{
							sql::Driver *driver;
							sql::Connection *con;
							sql::Statement *stmt;
							sql::ResultSet *res;
							sql::PreparedStatement *pstmt;

							driver = get_driver_instance();
							con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
                            con->setSchema("diggy");
							pstmt = con->prepareStatement("SELECT heart as heart, name as name FROM leaderboard ORDER BY heart DESC LIMIT 10");
							std::cout << "statement prepared" << std::endl;
							res = pstmt->executeQuery();
							sf::Packet _sendPacket;
                			_sendPacket << 1 << 10;
							res->beforeFirst();
							std::cout << "res after last" << std::endl;
							while (res->next())
							{
							    std::cout << res->getInt("heart") << res->getString("name");
								_sendPacket << res->getInt("heart");
								_sendPacket << res->getString("name");
							}
							client.send(_sendPacket);
							}
						catch (sql::SQLException &e)
						{
						    std::cout << "# ERR: SQLException in " << __FILE__;
							std::cout << "(" << __FUNCTION__ << ") on line "
								<< __LINE__ << std::endl;
							std::cout << "# ERR: " << e.what();
							std::cout << " (MySQL error code: " << e.getErrorCode();
							std::cout << ", SQLState: " << e.getSQLState() <<
								" )" << std::endl;
						}
						break;
					}

				}
				std::cout << std::endl;
			}
		}
	}
}
