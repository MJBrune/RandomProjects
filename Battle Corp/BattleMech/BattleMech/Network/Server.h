#ifndef NET_SERVER
#define NET_SERVER
#include <SFML/Network.hpp>
#include <vector>
#include "ServerClient.h"
#include <iostream>

namespace Network
{
	class Server
	{
	public:

		//Server sends a list of commands to clients, these commands must be identified so we know how to parse them
		//We identify the commands by always sending a value first, these values are the following in this enum:

		enum PacketSendType	
		{
			MapData				= 0,
			IdData				= 1,
			PlayerCount			= 2,
			GameState			= 3,
			PlayerTurn			= 4,
			PlayerMechChoice	= 5,
			MovePlayer			= 6,
			PlayerMechList		= 7,
			SetMechFacing		= 8,
			PlayerEndTurn		= 9,
			//TODO: Add more packet types as we move along
		};

		enum ConditionState
		{
			WaitingForPlayers	= 0,
			InGame				= 1,
			GameEndError		= 2,
			GameEndSuccess		= 3,

		};

		unsigned char MaxPlayers;


		Server(const unsigned char &playerMax = 2);
		Server(const int &port, const unsigned char &playerMax = 2);
		void Start(const int &port);

		bool IsReady();

		void Tick();

		void SendMap();
		void UpdateMechChoice(const ServerClient &client);

		void SendPlayerCount();

		TileMap &GetMap();

		void ChangeGameState(const ConditionState &state);

		void SendGameState();

		void SendPlayerMechList(ServerClient &client, sf::SocketTCP &socket);

		void SetPlayerTurn(const unsigned char& player);
		void SetPlayerTurn(const ServerClient &client);


	protected:
		sf::SocketTCP				tcpListen;
		unsigned char				nextIdToGive, currentPlayerTurn;
		std::vector<ServerClient>	clients;
		TileMap						tileMap;
		ConditionState				current_state;
		

	private:

		void Notify(std::string message)
		{
			std::cout<<message<<'\n';
		}

		

	};
}

#endif