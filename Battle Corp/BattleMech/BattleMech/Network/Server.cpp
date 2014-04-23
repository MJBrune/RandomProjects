#include "Server.h"
#include "../Network/GameClient.h"
namespace Network
{
		Server::Server(const unsigned char &playerMax)
		{
			MaxPlayers = playerMax;
			tcpListen.SetBlocking(false);
		}
		Server::Server(const int &port, const unsigned char &playerMax)
		{
			tcpListen.SetBlocking(false);
			MaxPlayers = playerMax;
			Start(port);
		}

		void Server::Start(const int &port)
		{
			currentPlayerTurn = 0;
			nextIdToGive	= 0;
			if(tcpListen.Listen(port)){
				std::cout<<"Started listen on port "<< port<<'\n';
				tcpListen.SetBlocking(false);
			}else{
				std::cout<<"Failed listen on port "<< port<<'\n';
			}

			ChangeGameState(WaitingForPlayers);
		}

		bool Server::IsReady()
		{
			return tcpListen.IsValid();
		}

		void Server::Tick()
		{
			//Look for Clients Code
			sf::SocketTCP *newClient = new sf::SocketTCP();
			newClient->SetBlocking(false);

			sf::Socket::Status acceptStatus = tcpListen.Accept(*newClient);

			if(acceptStatus == sf::Socket::Done)
			{
				newClient->SetBlocking(false);
				ServerClient add(*newClient, nextIdToGive);

				switch(add.id)//Sets the mech's position based on player ID
				{
				default:
				case 0:
					for(int m = 0; m < 1; m++)
					{
						Mech mAdd(StockMech(add.mechChoice), &tileMap, &tileMap(m, 8), Direction(Direction::North));
						add.myPlayer.m_mechs.push_back(mAdd);
					}
					break;
				case 1:
					for(int m = 0; m < 1; m++)
					{
						Mech mAdd(StockMech(add.mechChoice), &tileMap, &tileMap(m, 1), Direction(Direction::South));
						add.myPlayer.m_mechs.push_back(mAdd);
					}
					break;
				}

				clients.push_back(add);
				nextIdToGive++;

				sf::Packet packet;
				packet << (unsigned char)PacketSendType::MapData;
				tileMap.WriteToPacket(packet);
				add.socket->Send(packet);

				packet = sf::Packet();
				packet << (unsigned char)PacketSendType::IdData;
				packet << (unsigned char&)add.id;
				add.socket->Send(packet);

				packet = sf::Packet();
				packet << (unsigned char)PacketSendType::GameState;
				packet << (unsigned char&)current_state;
				add.socket->Send(packet);

				SendPlayerCount();

				for(int i =0 ; i < clients.size(); i++)
				{
					this->SendPlayerMechList(clients[i], *add.socket);
				}

				for(int i = 0; i < clients.size(); i++)
				{
					SendPlayerMechList(add, *clients[i].socket);
				}

				SetPlayerTurn(this->currentPlayerTurn);



				if(clients.size() >= MaxPlayers)
				{
					ChangeGameState(InGame);
				}

				Notify("Added new client!");
			}
			else
			{
				delete newClient;
			}
			//End of Look for Clients Code


			//Listen for Data Code

			for(unsigned int i = 0; i < clients.size(); i++)
			{
				sf::Packet packet;
				if(clients[i].socket->Receive(packet) == sf::Socket::Done)
				{
					unsigned char packetType = 0;
					packet >> packetType;

				
					switch(packetType)
					{
					case 0:	//client setting it's mech
						packet >> clients[i].mechChoice;
						for(int m = 0; m < clients[i].myPlayer.m_mechs.size(); m++)
						{
							clients[i].myPlayer.m_mechs[m].SetMechType((StockMech)clients[i].mechChoice);
						}
						UpdateMechChoice(clients[i]);//inform every client about this mech choice
						break;

					case 1: //client moving a mech
						{
							unsigned char	mechID		= 0;
							unsigned short	posX		= 0;
							unsigned short	posY		= 0;

							packet >> mechID;
							packet >> posX;
							packet >> posY;

							if(i == this->currentPlayerTurn)
							{
								if(mechID < clients[i].myPlayer.m_mechs.size())
								{
									Mech &mech = clients[i].myPlayer.m_mechs[mechID];
									mech.Move(posX,posY);
									
									sf::Packet packet;
									packet << (unsigned char)MovePlayer;
									packet << clients[i].id;
									packet << mechID;
									packet << posX;
									packet << posY;
									packet << currentPlayerTurn;
									for(int c = 0; c < clients.size(); c++)
									{
										clients[c].socket->Send(packet);
									}
								}
							}
							else
							{
							}
						}
						break;
					case 2:	//client setting direction
						{
							unsigned char	mechID		= 0;
							signed int	dir				= 0;

							packet >> mechID;
							packet >> dir;

							if(i == this->currentPlayerTurn)
							{
								if(mechID < clients[i].myPlayer.m_mechs.size())
								{
									Mech &mech = clients[i].myPlayer.m_mechs[mechID];
									mech.SetFacing((Direction)dir);
									
									sf::Packet packet;
									packet << (unsigned char)SetMechFacing;
									packet << clients[i].id;
									packet << mechID;
									packet << dir;
									packet << currentPlayerTurn;

									for(int c = 0; c < clients.size(); c++)
									{
										clients[c].socket->Send(packet);
									}
								}
							}
							else
							{
							}
						}
						break;
					case 3: //Player ended turn
						{
							if(i == this->currentPlayerTurn)
							{
								currentPlayerTurn++;

								if(currentPlayerTurn >= clients.size())
								{
									currentPlayerTurn = 0;
								}

								sf::Packet packet;
								packet << (unsigned char)PlayerEndTurn;
								packet << currentPlayerTurn;

								for(int c = 0; c < clients.size(); c++)
								{
									clients[c].socket->Send(packet);
								}
							}
						}
						break;
						case 4:
							{
								unsigned char	pid		= 0;
								unsigned char	mCount	= 0;

								packet >> pid;
								packet >> mCount;

								for(unsigned char c = 0; c < clients.size(); c++)
								{
									if(clients[c].id == pid)
									{
										ServerClient &cl = clients[c];
										cl.myPlayer.m_mechs.clear();
										for(unsigned char m = 0; m < mCount; m++)
										{
											Mech add(StockMech::RLight, &tileMap, 0, Direction::North);
											add.IsMine = (cl.id == pid);
											add.Init();
											cl.myPlayer.m_mechs.push_back(add);
										}
										for(unsigned char m = 0; m < cl.myPlayer.m_mechs.size(); m++)
										{
											cl.myPlayer.m_mechs[m].ReadFromPacket(packet);
										}
										SendPlayerMechList(cl, *cl.socket);
									//	break;
									}
								}
							}
						break;
					}
				}
			}

			//End of Listen For Data Code
		}

		void Server::SendMap()
		{
			sf::Packet packet;
			packet<<(unsigned char)PacketSendType::MapData;
			tileMap.WriteToPacket(packet);

			for(int i = 0; i < clients.size(); i++)
			{
				clients[i].socket->Send(packet);	
			}
		}

		void Server::UpdateMechChoice(const ServerClient &client)
		{
			sf::Packet packet;
			packet << (unsigned char)PacketSendType::PlayerMechChoice;
			packet << client.id;
			packet << client.mechChoice;
			
			for(int i = 0; i < clients.size(); i++)
			{
				clients[i].socket->Send(packet);	
			}
		}

		void Server::SendPlayerCount()
		{
			sf::Packet packet;

			packet	<<	(unsigned char)PacketSendType::PlayerCount;
			packet	<<	(unsigned char)clients.size();
			packet	<<	MaxPlayers;

			
			for(int i = 0; i < clients.size(); i++)
			{
				clients[i].WriteToPacket(packet);
			}

			for(int i = 0; i < clients.size(); i++)
			{
				clients[i].socket->Send(packet);	
			}
		}

		TileMap &Server::GetMap(){return tileMap;}

		void Server::ChangeGameState(const ConditionState &state)
		{
			if(state != current_state)
			{
				current_state = state;
				SendGameState();
			}
		}

		void Server::SendGameState()
		{
			sf::Packet packet;
			packet << (unsigned char)PacketSendType::GameState;
			packet << (unsigned char&)current_state;
			for(int i = 0; i < clients.size(); i++)
			{
				clients[i].socket->Send(packet);	
			}
		}

		void Server::SetPlayerTurn(const unsigned char& player)
		{
			currentPlayerTurn = player;
			sf::Packet packet;

			packet << (unsigned char)PacketSendType::PlayerTurn;
			packet << player;
			for(int i = 0; i < clients.size(); i++)
			{
				clients[i].socket->Send(packet);	
			}
		}
		void Server::SetPlayerTurn(const ServerClient &client)
		{
			SetPlayerTurn(client.id);
		}

		void Server::SendPlayerMechList(ServerClient &client, sf::SocketTCP &socket)
		{
			sf::Packet packet;
			packet << (unsigned char)this->PlayerMechList;
			packet << client.id;
			packet << (unsigned char)client.myPlayer.m_mechs.size();
			for(int i =0 ; i < client.myPlayer.m_mechs.size(); i++)
			{
				client.myPlayer.m_mechs[i].WriteToPacket(packet);
			}
			socket.Send(packet);
		}
}