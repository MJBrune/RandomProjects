#include "GameClient.h"

namespace Network
{
		GameClient::GameClient()
		{
			socket.SetBlocking(false);

			id				= 0;
			current_turn	= 0;
		}
		void GameClient:: Connect(sf::IPAddress ip, const unsigned short &port)
		{
			socket.Connect(port, ip);
			socket.SetBlocking(false);
		}

		void GameClient:: Tick()
		{
			//Begin Receive Check
			sf::Packet packet;
			if(socket.Receive(packet) == sf::Socket::Done)
			{
				unsigned char packetType = 0;
				packet >> packetType;
				
				
				switch(packetType)
				{
				case Server::IdData:
					packet >> id;
					ev_recIdData = true;
					break;

				case Server::MapData:
					tiles.ReadPacket(packet);
					ev_recMap = true;
					break;

				case Server::PlayerCount:
					packet >> playercount;
					packet >> maxplayers;

					{
						for(int i = 0; i < playercount; i++)
						{
							ServerClient toAdd;
							toAdd.ReadFromPacket(packet);

							bool doAdd = true;
							for(int c = 0; c < clients.size(); c++)
							{
								if(clients[c].id == toAdd.id)
								{
									doAdd = false;
									break;
								}
							}

							if(doAdd)
							{
								clients.push_back(toAdd);
							}
						}

					}
					clients.reserve(maxplayers);
					break;
				case Server::GameState:
					{
						unsigned char stateData = 0;
						packet >> stateData;
						current_state = stateData;
					}
				break;
				case Server::PlayerTurn:
					packet >> current_turn;
					break;
				case Server::PlayerMechChoice:
					{
						unsigned char pid = 0;
						unsigned char pMech = 0;
						packet >> pid;
						packet >> pMech;
							for(int c = 0; c < clients.size(); c++)
							{
								if(clients[c].id == pid)
								{
									clients[c].mechChoice = pMech;
									for(int m = 0; m < clients[c].myPlayer.m_mechs.size(); m++)
									{
										clients[c].myPlayer.m_mechs[m].SetMechType((StockMech)pMech);
									}
								}
							}
					}
					break;
				case Server::MovePlayer:
					{
						unsigned char	pid		= 0;
						unsigned char	mechId	= 0;
						unsigned short	posX	= 0;
						unsigned short	posY	= 0;
						
						packet >> pid;
						packet >> mechId;
						packet >> posX;
						packet >> posY;

						packet >> current_turn;

						for(unsigned char c = 0; c < clients.size(); c++)
						{
							if(clients[c].id == pid)
							{
								ServerClient &cl = clients[c];
								if(mechId < cl.myPlayer.m_mechs.size())
								{
									cl.myPlayer.m_mechs[mechId].Move(posX, posY);
								}
							}
						}

					}
					break;
				case Server::PlayerMechList:
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
									Mech add(StockMech::RLight, &tiles, 0, Direction::North);
									add.IsMine = (id == pid);
									add.Init();
									cl.myPlayer.m_mechs.push_back(add);
								}
								for(unsigned char m = 0; m < cl.myPlayer.m_mechs.size(); m++)
								{
									cl.myPlayer.m_mechs[m].ReadFromPacket(packet);
								}
								break;
							}
						}
					}
					break;
				case Server::SetMechFacing:
					{
						unsigned char	pid		= 0;
						unsigned char	mechId	= 0;
						signed int	rotate	= 0;
						
						packet >> pid;
						packet >> mechId;
						packet >> rotate;
						packet >> current_turn;

						for(unsigned char c = 0; c < clients.size(); c++)
						{
							if(clients[c].id == pid)
							{
								ServerClient &cl = clients[c];
								if(mechId < cl.myPlayer.m_mechs.size())
								{
									cl.myPlayer.m_mechs[mechId].SetFacing((Direction)rotate);
								}
							}
						}
					}
					break;
				case Server::PlayerEndTurn:
					{
						packet >> current_turn;
						clients[current_turn].myPlayer.m_mechs[0].canMove = true;
						for ( int i = 0; i < clients[current_turn].myPlayer.m_mechs[0].m_weapons.size(); i++)
							clients[current_turn].myPlayer.m_mechs[0].m_weapons[i]->canFire = true;
						//for (int i = 0; i < clients[current_turn].myPlayer.m_mechs[0].m_weapons.size(); i++)
					}
					break;
				default:
					Error("Unknown packet type: " + (int&)packetType);
					break;
				}
				
			}
		}

		void GameClient::SetMechChoice(const unsigned char& choice)
		{
			sf::Packet packet;
			packet << (unsigned char)SendPacketTypes::MechChoice;
			packet << (unsigned char)choice;
			socket.Send(packet);
		}

		
		void GameClient::SetMechPosition(const unsigned char& mechID, const unsigned short &posX, const unsigned short &posY)
		{
			sf::Packet packet;
			packet << (unsigned char)SendPacketTypes::MechMove;
			packet << mechID;
			packet << posX;
			packet << posY;
			socket.Send(packet);
		}

		void GameClient::SetMechFacing(const unsigned char& mechID, const Direction &dir)
		{
			sf::Packet packet;
			packet << (unsigned char)SendPacketTypes::MechFacing;
			packet << mechID;
			packet << (signed int&)dir;
			socket.Send(packet);
		}

		void GameClient::EndMyTurn()
		{
			sf::Packet packet;
			packet << (unsigned char)SendPacketTypes::EndTurn;
			socket.Send(packet);
		}

		void GameClient::SendPlayerMechList()
		{
			sf::Packet packet;
			packet << (unsigned char)SendPacketTypes::PlayerMechList;
			packet << !id;
			packet << (unsigned char)clients[!id].myPlayer.m_mechs.size();
			for(int i = 0 ; i < clients[!id].myPlayer.m_mechs.size(); i++)
			{
				clients[!id].myPlayer.m_mechs[i].WriteToPacket(packet);
			}
			socket.Send(packet);
		}
}