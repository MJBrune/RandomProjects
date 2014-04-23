#include "MainMenu.h"


namespace States
{
	MainMenu::MainMenu()
		{
			enteringIpInfo = false;
			enterForHostJoin = false;

			exitBtn = new UI::Button(sf::FloatRect(0,0,280,50));
			widgets.push_back(exitBtn);

			ipText = new UI::Text("localhost");
			
			widgets.push_back(ipText);

			joinBtn = new UI::Button(sf::FloatRect(0,0,280,50));
			widgets.push_back(joinBtn);
			
			hostJoinBtn = new UI::Button(sf::FloatRect(0,0,280,50));
			widgets.push_back(hostJoinBtn);

			joinBtn->SetPosition(sf::Vector2f(100,200));
			exitBtn->SetPosition(sf::Vector2f(100,100));
			hostJoinBtn->SetPosition(sf::Vector2f(100,300));

			//debug only MechMenu
		//	OptionBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		//	widgets.push_back(OptionBtn);
		//	OptionBtn->SetPosition(sf::Vector2f(500,300));

		}

		void MainMenu:: Update(float timespan)
		{
			if(exitBtn->IsClicked())
			{
				MainGame.GetWindow().Close();
			}
			if(joinBtn->IsClicked())
			{
				enteringIpInfo = true;
			}
			if(ipText->TextEntered())
			{
				bMechGame.Connect(ipText->TextString(), false);
				MainGame.SetState(bMechMenu);
			}else if(hostJoinBtn->IsClicked())
			{
				bMechGame.HostConnect();
				MainGame.SetState(bMechMenu);
			}
		//	if (OptionBtn->IsClicked())
		//	{
		//		MainGame.SetState(bOptionMenu);
		//	}
		}

		void MainMenu:: Render()
		{
			MainGame.GetWindow().Clear(sf::Color(0,0,0));

			if(enteringIpInfo == false)
			{
				//Draw Exit Button
				sf::Shape exitBox = sf::Shape::Rectangle(exitBtn->GetBoundingBox().Left, exitBtn->GetBoundingBox().Top, exitBtn->GetBoundingBox().Right, exitBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
				MainGame.GetWindow().Draw(exitBox);
				sf::String exitText("Exit");
				exitText.SetPosition(exitBtn->GetPosition());
				exitText.SetColor(sf::Color::Black);
				MainGame.GetWindow().Draw(exitText);

				//Draw Join Button
				sf::Shape joinBox = sf::Shape::Rectangle(joinBtn->GetBoundingBox().Left, joinBtn->GetBoundingBox().Top, joinBtn->GetBoundingBox().Right, joinBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
				MainGame.GetWindow().Draw(joinBox);
				sf::String joinText("Join Game");
				joinText.SetPosition(joinBtn->GetPosition());
				joinText.SetColor(sf::Color::Black);
				MainGame.GetWindow().Draw(joinText);

				
				//Draw Join Button
				sf::Shape hostJoinBox = sf::Shape::Rectangle(hostJoinBtn->GetBoundingBox().Left, hostJoinBtn->GetBoundingBox().Top, hostJoinBtn->GetBoundingBox().Right, hostJoinBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
				MainGame.GetWindow().Draw(hostJoinBox);
				sf::String hostJoinText("Host and Join Game");
				hostJoinText.SetPosition(hostJoinBtn->GetPosition());
				hostJoinText.SetColor(sf::Color::Black);
				MainGame.GetWindow().Draw(hostJoinText);


				//Debug only mechmenu
			//	sf::Shape OptionMenuBox = sf::Shape::Rectangle(OptionBtn->GetBoundingBox().Left, OptionBtn->GetBoundingBox().Top, OptionBtn->GetBoundingBox().Right, OptionBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
			//	MainGame.GetWindow().Draw(OptionMenuBox);
			//	sf::String OptionMenu("Option Menu");
			//	OptionMenu.SetPosition(OptionBtn->GetPosition());
			//	OptionMenu.SetColor(sf::Color::Black);
			//	MainGame.GetWindow().Draw(OptionMenu);
			}
			else
			{
				sf::String ipString = sf::String("IP: " + ipText->TextString());
				ipString.SetPosition(100,100);
				MainGame.GetWindow().Draw(ipString);
			}
		}

		void MainMenu:: Init()
		{
			enteringIpInfo = false;
			MainGame.SetWidgetContainer(widgets);
		}

		void MainMenu:: Exit()
		{
		}
}