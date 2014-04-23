#include "BattleMech.h"
#include "../Network/ServerClient.h"

namespace States
{		
	BattleMech::BattleMech()
			:m_endTurnBtn(sf::FloatRect(0,0,280,50)),
			m_NorthBtn(sf::FloatRect(0,0,80,30)),
			m_NorthWestBtn(sf::FloatRect(0,0,80,30)),
			m_NorthEastBtn(sf::FloatRect(0,0,80,30)),
			m_SouthWestBtn(sf::FloatRect(0,0,80,30)),
			m_SouthEastBtn(sf::FloatRect(0,0,80,30)),
			m_SouthBtn(sf::FloatRect(0,0,80,30))
		{
			isHosting = false;
			connected = false;
		}
		BattleMech::BattleMech(sf::IPAddress ipAddr)
			:m_endTurnBtn(sf::FloatRect(0,0,280,50)),
			m_NorthBtn(sf::FloatRect(0,0,80,30)),
			m_NorthWestBtn(sf::FloatRect(0,0,80,30)),
			m_NorthEastBtn(sf::FloatRect(0,0,80,30)),
			m_SouthWestBtn(sf::FloatRect(0,0,80,30)),
			m_SouthEastBtn(sf::FloatRect(0,0,80,30)),
			m_SouthBtn(sf::FloatRect(0,0,80,30))
		{
			Connect(ipAddr);
		}

		void BattleMech:: HostConnect()
		{
			hostServer.Start(DEFAULTSERVERPORT);
			hostServer.GetMap().CreateRandomMap(11,11);
	
			Connect("localhost", true);
		}

		void BattleMech::Connect(sf::IPAddress ipAddr, const bool &hosting)
		{
			isHosting = hosting;
			client.Connect(ipAddr, DEFAULTSERVERPORT);
		}

		void BattleMech:: SetBattleMechType(const unsigned &type)
		{
			client.SetMechChoice(type);
		}
		

		void BattleMech:: Update(float timespan)
		{

			if(isHosting)
			{
				hostServer.Tick();
			}
			
			if(m_endTurnBtn.IsClicked() && client.IsMyTurn())
			{
				//client.SendPlayerMechList(); // this was for debug purposes
				client.EndMyTurn();
			}

			sf::Vector2f mousePos(MainGame.GetWindow().GetInput().GetMouseX(), MainGame.GetWindow().GetInput().GetMouseY());
			
			if(client.GameState() == Network::Server::ConditionState::InGame)
			{
				if (m_NorthBtn.IsClicked())
				{
					client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].SetFacing(North);
					client.SetMechFacing(0, North);
				}
				else if (m_NorthWestBtn.IsClicked())
				{
					client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].SetFacing(NorthWest);
					client.SetMechFacing(0, NorthWest);
				}
				if (m_NorthEastBtn.IsClicked())
				{
					client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].SetFacing(NorthEast);
					client.SetMechFacing(0, NorthEast);
				}
				else if (m_SouthWestBtn.IsClicked())
				{
					client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].SetFacing(SouthWest);
					client.SetMechFacing(0, SouthWest);
				}
				else if (m_SouthEastBtn.IsClicked())
				{
					client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].SetFacing(SouthEast);
					client.SetMechFacing(0, SouthEast);
				}
				else if (m_SouthBtn.IsClicked())
				{
					client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].SetFacing(South);
					client.SetMechFacing(0, South);
				}

				for(int i = 0; i < client.GetMap().Tiles.size(); i++)
				{
					Tile &t = client.GetMap().Tiles[i];

					sf::FloatRect tileRect = client.GetMap().TileBox(t.GridX,t.GridY);

					if(tileRect.Contains(mousePos.x, mousePos.y))
					{
						if(MainGame.GetWindow().GetInput().IsMouseButtonDown(sf::Mouse::Left))
						{
							//Clicked tile
								if (!t.ContainsMech)
									client.SetMechPosition(0,t.GridX,t.GridY);						

								for ( int j = 0; j < client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].m_weapons.size(); j++)
									if(m_fireForWeapon[j]->IsClicked() && client.IsMyTurn())
									{
										if (t.ContainsMech)
										{
											client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].Fire(t.MyMech, client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].m_weapons[j]);
											client.SendPlayerMechList();
										}
									}
									else if (t.ContainsMech)
										displayMech = t.MyMech;
						}
					}

					if(t.ContainsMech){
						t.MyMech->Update(timespan);
					}
				}
			}
			client.Tick();
		}

		void BattleMech:: Render()
		{
			switch(client.GameState())
			{
			case Network::Server::ConditionState::WaitingForPlayers:
				{
					sf::String noti("Waiting for players...\n\nCurrently: "+ ToString<int>(client.PlayerCount()) + "/" + ToString<int>(client.MaxPlayers()));
					MainGame.GetWindow().Draw(noti);
				}
				break;
			case Network::Server::ConditionState::InGame:
				client.GetMap().Render(MainGame.GetWindow());

				{
					//displayMech = &client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0];
					MainGame.GetWindow().Draw(m_leftUI);
					if(displayMech != NULL)
					{
						if (displayMech->GetType() == RLight || displayMech->GetType() == BLight)
							MainGame.GetWindow().Draw(m_rLightUI);
						else if (displayMech->GetType() == RMedium || displayMech->GetType() == BMedium)
							MainGame.GetWindow().Draw(m_rMedUI);
						else if (displayMech->GetType() == RHeavy || displayMech->GetType() == BHeavy)
							MainGame.GetWindow().Draw(m_rHeavyUI);
					
						displayMechArmor = displayMech->getArmor();
						for(int i = 0; i <= COCKPIT; i++)
						{
							mechInfoStr.str("");
							mechInfoStr.clear();
							mechInfoStr << loctionstr[i] << ": " << displayMechArmor[i];
							mechInfo.SetText(mechInfoStr.str());
							mechInfo.SetSize(20);
							mechInfo.SetPosition(725, 315+(20 * i));
							MainGame.GetWindow().Draw(mechInfo);
						}
						
					}
					if(client.IsMyTurn())
					{
						sf::String noti;
						if (client.clients[!client.CurrentPlayersTurn()].myPlayer.m_mechs[0].isDead)
						{
							noti.SetText("YOU WON!!!");
						}
						else if (client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].isDead)
						{
							noti.SetText("YOU ARE DEAD!!!");
						}
						else
							noti.SetText("It's your turn!");
						noti.SetColor(sf::Color(100,255,100));
						MainGame.GetWindow().Draw(noti);
						MainGame.GetWindow().Draw(m_endTurnBox);
						MainGame.GetWindow().Draw(m_endTurnText);

						MainGame.GetWindow().Draw(m_NorthBox);
						MainGame.GetWindow().Draw(m_NorthText);

						MainGame.GetWindow().Draw(m_NorthWestBox);
						MainGame.GetWindow().Draw(m_NorthWestText);

						MainGame.GetWindow().Draw(m_NorthEastBox);
						MainGame.GetWindow().Draw(m_NorthEastText);

						MainGame.GetWindow().Draw(m_SouthWestBox);
						MainGame.GetWindow().Draw(m_SouthWestText);

						MainGame.GetWindow().Draw(m_SouthEastBox);
						MainGame.GetWindow().Draw(m_SouthEastText);

						MainGame.GetWindow().Draw(m_SouthBox);
						MainGame.GetWindow().Draw(m_SouthText);

						for ( int i = 0; i < client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].m_weapons.size(); i++)
						{
							m_weaponsForMech.push_back(sf::String(client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].m_weapons[i]->GetWeaponName()));
							m_weaponsForMech[i].SetSize(20);
							m_weaponsForMech[i].SetPosition(725, 462+(i*20));
							MainGame.GetWindow().Draw(m_weaponsForMech[i]);

							m_fire.SetPosition(900, 467+(i*20));
							m_fireForWeapon[i]->SetPosition(m_fire.GetPosition());
							m_boxForFire.SetPosition(m_fire.GetPosition());
							if (client.clients[client.CurrentPlayersTurn()].myPlayer.m_mechs[0].m_weapons[i]->canFire)
							{
								MainGame.GetWindow().Draw(m_boxForFire);
								MainGame.GetWindow().Draw(m_fire);
							}
						}

					}
					else
					{
						sf::String noti("Player " + ToString<int>(client.CurrentPlayersTurn()) + "'s turn.");
						MainGame.GetWindow().Draw(noti);
					}

					if(MainGame.GetWindow().GetInput().IsKeyDown(sf::Key::Tab))
					{
						std::string statString = "";
						for(int c = 0; c < client.clients.size(); c++)
						{
							statString += "Player " + ToString<int>(client.clients[c].id) + ": Mech Type " + ToString<int>(client.clients[c].mechChoice);
							statString +="\n";
						}
						sf::String noti(statString);
						noti.SetPosition(200,200);
						MainGame.GetWindow().Draw(noti);
					}
				}
				break;
			};
		}

		void BattleMech:: Init()	
		{
			MainGame.SetWidgetContainer(m_widgets);
			
			m_widgets.push_back(&m_endTurnBtn);
			m_endTurnBtn.SetPosition(sf::Vector2f(700,700));
			m_endTurnBox = sf::Shape::Rectangle(m_endTurnBtn.GetBoundingBox().Left, m_endTurnBtn.GetBoundingBox().Top, m_endTurnBtn.GetBoundingBox().Right, m_endTurnBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_endTurnText.SetText("End Turn");
			m_endTurnText.SetPosition(m_endTurnBtn.GetPosition());
			m_endTurnText.SetColor(sf::Color::Black);

			m_widgets.push_back(&m_NorthBtn);
			m_NorthBtn.SetPosition(sf::Vector2f(795,600));
			m_NorthBox = sf::Shape::Rectangle(m_NorthBtn.GetBoundingBox().Left, m_NorthBtn.GetBoundingBox().Top, m_NorthBtn.GetBoundingBox().Right, m_NorthBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_NorthText.SetSize(16);
			m_NorthText.SetText("North");
			m_NorthText.SetPosition(m_NorthBtn.GetPosition());
			m_NorthText.SetColor(sf::Color::Black);

			m_widgets.push_back(&m_NorthWestBtn);
			m_NorthWestBtn.SetPosition(sf::Vector2f(710,600));
			m_NorthWestBox = sf::Shape::Rectangle(m_NorthWestBtn.GetBoundingBox().Left, m_NorthWestBtn.GetBoundingBox().Top, m_NorthWestBtn.GetBoundingBox().Right, m_NorthWestBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_NorthWestText.SetSize(16);
			m_NorthWestText.SetText("NorthWest");
			m_NorthWestText.SetPosition(m_NorthWestBtn.GetPosition());
			m_NorthWestText.SetColor(sf::Color::Black);

			m_widgets.push_back(&m_NorthEastBtn);
			m_NorthEastBtn.SetPosition(sf::Vector2f(880,600));
			m_NorthEastBox = sf::Shape::Rectangle(m_NorthEastBtn.GetBoundingBox().Left, m_NorthEastBtn.GetBoundingBox().Top, m_NorthEastBtn.GetBoundingBox().Right, m_NorthEastBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_NorthEastText.SetSize(16);
			m_NorthEastText.SetText("NorthEast");
			m_NorthEastText.SetPosition(m_NorthEastBtn.GetPosition());
			m_NorthEastText.SetColor(sf::Color::Black);

			m_widgets.push_back(&m_SouthWestBtn);
			m_SouthWestBtn.SetPosition(sf::Vector2f(710,650));
			m_SouthWestBox = sf::Shape::Rectangle(m_SouthWestBtn.GetBoundingBox().Left, m_SouthWestBtn.GetBoundingBox().Top, m_SouthWestBtn.GetBoundingBox().Right, m_SouthWestBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_SouthWestText.SetSize(16);
			m_SouthWestText.SetText("SouthWest");
			m_SouthWestText.SetPosition(m_SouthWestBtn.GetPosition());
			m_SouthWestText.SetColor(sf::Color::Black);

			m_widgets.push_back(&m_SouthEastBtn);
			m_SouthEastBtn.SetPosition(sf::Vector2f(880,650));
			m_SouthEastBox = sf::Shape::Rectangle(m_SouthEastBtn.GetBoundingBox().Left, m_SouthEastBtn.GetBoundingBox().Top, m_SouthEastBtn.GetBoundingBox().Right, m_SouthEastBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_SouthEastText.SetSize(16);
			m_SouthEastText.SetText("SouthEast");
			m_SouthEastText.SetPosition(m_SouthEastBtn.GetPosition());
			m_SouthEastText.SetColor(sf::Color::Black);

			m_widgets.push_back(&m_SouthBtn);
			m_SouthBtn.SetPosition(sf::Vector2f(795,650));
			m_SouthBox = sf::Shape::Rectangle(m_SouthBtn.GetBoundingBox().Left, m_SouthBtn.GetBoundingBox().Top, m_SouthBtn.GetBoundingBox().Right, m_SouthBtn.GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			m_SouthText.SetSize(16);
			m_SouthText.SetText("South");
			m_SouthText.SetPosition(m_SouthBtn.GetPosition());
			m_SouthText.SetColor(sf::Color::Black);
			
			m_leftUIImage.LoadFromFile("Resources/LeftUIGrey.jpg");
			m_leftUI.SetImage(m_leftUIImage);
			m_leftUI.SetPosition(sf::Vector2f(689,26));

			m_rHeavyUIImage.LoadFromFile("Resources/RHeavyUI.png");
			m_rHeavyUI.SetImage(m_rHeavyUIImage);
			m_rHeavyUI.SetPosition(sf::Vector2f(720,55));

			m_rMedUIImage.LoadFromFile("Resources/RMedUI.png");
			m_rMedUI.SetImage(m_rMedUIImage);
			m_rMedUI.SetPosition(sf::Vector2f(720,50));

			m_rLightUIImage.LoadFromFile("Resources/RLightUI.png");
			m_rLightUI.SetImage(m_rLightUIImage);
			m_rLightUI.SetPosition(sf::Vector2f(720,55));

			for ( int i = 0; i < 6; i++)
			{
				m_fire.SetText("Fire");
				m_fire.SetSize(15);
				m_fire.SetColor(sf::Color::Black);
				m_fireForWeapon.push_back(new UI::Button(m_fire.GetRect()));
				m_widgets.push_back(m_fireForWeapon[i]);
			}

			m_boxForFire = sf::Shape::Rectangle(m_fireForWeapon[0]->GetBoundingBox().Left, m_fireForWeapon[0]->GetBoundingBox().Top, m_fireForWeapon[0]->GetBoundingBox().Right, m_fireForWeapon[0]->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		}

		void BattleMech:: Exit()
		{

		}

}
