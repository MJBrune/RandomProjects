#ifndef NET_GAME_CLIENT
#define NET_GAME_CLIENT
#include <SFML/Network.hpp>
#include "Server.h"
#include <iostream>


namespace Network
{
	class GameClient
	{
	public:

		enum SendPacketTypes
		{
			MechChoice	= 0,
			MechMove	= 1,
			MechFacing	= 2,
			EndTurn = 3,
			PlayerMechList = 4,
		};

		GameClient();


		void Connect(sf::IPAddress ip, const unsigned short &port);
		void Tick();
		void SetMechChoice(const unsigned char& choice);
		void SetMechPosition(const unsigned char& mechID, const unsigned short &posX, const unsigned short &posY);
		void SetMechFacing(const unsigned char& mechID, const Direction &dir);
		void SendPlayerMechList();



		const bool							HasReceivedMap()
		{
			return ret_event_func(ev_recMap);
		}
		const bool							HasReceivedId()
		{
			return ret_event_func(ev_recIdData);
		}
		const unsigned char &				MaxPlayers()	{return maxplayers;}
		const unsigned char &				PlayerCount()	{return playercount;}
		const unsigned char&				GameState()
		{
			return current_state;
		}
		TileMap &							GetMap(){return tiles;}
		const unsigned char&				CurrentPlayersTurn()
		{
			return current_turn;
		}
		const bool							IsMyTurn()
		{
			if(current_turn == id)
			{
				return true;
			}
			return false;
		}
		
		void EndMyTurn();

		std::vector <ServerClient>	clients;
	private:

		sf::SocketTCP				socket;

		unsigned char				id, maxplayers, playercount, current_turn;
		TileMap						tiles;
		unsigned char				current_state;

		void Error(std::string string)
		{
			std::cout<<"An error has occured: "<< string<<"\n";
		}

		bool ret_event_func(bool &eventToUse)
		{
			bool temp = eventToUse;
			eventToUse = false;
			return temp;
		}



		//events
		bool	ev_recMap,
				ev_recIdData
				;
		



	protected:
	};
}
#endif