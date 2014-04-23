#include "MechMenu.h"
namespace States
{
	MechMenu::MechMenu()
		:m_ptrMech(RLight, NULL, NULL, North)
	{

		m_okayBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_okayBtn);

		m_nextBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_nextBtn);

		m_backBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_backBtn);

		m_okayBtn->SetPosition(sf::Vector2f(50,100));
		m_nextBtn->SetPosition(sf::Vector2f(50,200));
		m_backBtn->SetPosition(sf::Vector2f(50,300));

		m_typeOneBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_typeOneBtn);

		m_typeTwoBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_typeTwoBtn);

	//	m_mechBtn = new UI::Button(sf::FloatRect(0,0,77,66));
	//	widgets.push_back(m_mechBtn);

		m_typeOneBtn->SetPosition(sf::Vector2f(50,600));
		m_typeTwoBtn->SetPosition(sf::Vector2f(50,700));
	}

	void MechMenu:: Update(float timespan)
	{
		if(m_okayBtn->IsClicked())
		{
			MainGame.SetState(bMechGame);
			bMechGame.SetBattleMechType(m_mechPage-1);
		}
		else if(m_nextBtn->IsClicked())
		{
			if (m_mechPage == 6)
				m_mechPage = 1;
			else
				m_mechPage++;
		}
		else if(m_backBtn->IsClicked())
		{
			if (m_mechPage == 1)
				m_mechPage = 6;
			else
				m_mechPage--;
		}
		else if(m_typeOneBtn->IsClicked())
		{
			plains.LoadFromFile("Resources/Plains.png");
			lWoods.LoadFromFile("Resources/LWoods.png");
			hWoods.LoadFromFile("Resources/HWoods.png");
			rocks.LoadFromFile("Resources/Rocks.png");
		}
		else if(m_typeTwoBtn->IsClicked())
		{
			plains.LoadFromFile("Resources/Plains2Low.png");
			lWoods.LoadFromFile("Resources/LWoods2Low.png");
			hWoods.LoadFromFile("Resources/HWoods2Low.png");
			rocks.LoadFromFile("Resources/Rock2Low.png");
		}

	}

	void MechMenu:: Render()
	{
		MainGame.GetWindow().Clear(sf::Color(0,0,0));

		//Draw Okay Button
		sf::Shape exitBox = sf::Shape::Rectangle(m_okayBtn->GetBoundingBox().Left, m_okayBtn->GetBoundingBox().Top, m_okayBtn->GetBoundingBox().Right, m_okayBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(exitBox);
		sf::String exitText("Okay");
		exitText.SetPosition(m_okayBtn->GetPosition());
		exitText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(exitText);

		//Draw Next Button
		sf::Shape NextBox = sf::Shape::Rectangle(m_nextBtn->GetBoundingBox().Left, m_nextBtn->GetBoundingBox().Top, m_nextBtn->GetBoundingBox().Right, m_nextBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(NextBox);
		sf::String NextText("Next Mech");
		NextText.SetPosition(m_nextBtn->GetPosition());
		NextText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(NextText);


		//Draw Back Button
		sf::Shape BackBox = sf::Shape::Rectangle(m_backBtn->GetBoundingBox().Left, m_backBtn->GetBoundingBox().Top, m_backBtn->GetBoundingBox().Right, m_backBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(BackBox);
		sf::String BackText("Previous Mech");
		BackText.SetPosition(m_backBtn->GetPosition());
		BackText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(BackText);

		//Draw Type One
		sf::Shape typeOneBox = sf::Shape::Rectangle(m_typeOneBtn->GetBoundingBox().Left, m_typeOneBtn->GetBoundingBox().Top, m_typeOneBtn->GetBoundingBox().Right, m_typeOneBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(typeOneBox);
		sf::String typeOneText("Terrian Type 1");
		typeOneText.SetPosition(m_typeOneBtn->GetPosition());
		typeOneText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(typeOneText);


		//Draw Type Two
		sf::Shape typeTwoBox = sf::Shape::Rectangle(m_typeTwoBtn->GetBoundingBox().Left, m_typeTwoBtn->GetBoundingBox().Top, m_typeTwoBtn->GetBoundingBox().Right, m_typeTwoBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(typeTwoBox);
		sf::String typeTwoText("Terrian Type 2");
		typeTwoText.SetPosition(m_typeTwoBtn->GetPosition());
		typeTwoText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(typeTwoText);

		//	sf::Shape mechBox = sf::Shape::Rectangle(m_mechBtn->GetBoundingBox().Left, m_mechBtn->GetBoundingBox().Top, m_mechBtn->GetBoundingBox().Right, m_mechBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		//	MainGame.GetWindow().Draw(mechBox);
		//Draw Mech Image
		MainGame.GetWindow().Draw(m_PlainsSprite);
		MainGame.GetWindow().Draw(m_LForestSprite);
		MainGame.GetWindow().Draw(m_RocksSprite);
		MainGame.GetWindow().Draw(m_HForestSprite);

		//	sf::Shape mechBox = sf::Shape::Rectangle(m_mechBtn->GetBoundingBox().Left, m_mechBtn->GetBoundingBox().Top, m_mechBtn->GetBoundingBox().Right, m_mechBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		//	MainGame.GetWindow().Draw(mechBox);
		
		m_lightString.SetText("8 Movement\nHead: 6\nTorso: 10\nL/R Arm: 7\nL/R Leg: 7");
		m_lightString.SetPosition(750,150);
		m_medString.SetText("5 Movement\nHead: 6\nTorso: 16\nL/R Arm: 11\nL/R Leg: 11");
		m_medString.SetPosition(750,150);
		m_heavyString.SetText("2 Movement\nHead: 6\nTorso: 22\nL/R Arm: 15\nL/R Leg: 15\n");
		m_heavyString.SetPosition(750,150);

		for (int i = 0; i < m_ptrMech.m_weapons.size(); i++)
		{
			m_weapons = "";
			m_weapons += m_ptrMech.m_weapons[i]->GetWeaponName() 
				+ "\nDamage: " + ToString(m_ptrMech.m_weapons[i]->GetDamage()) 
				+ "\nMin Range: " + ToString(m_ptrMech.m_weapons[i]->GetMinRange())
				+ "\nMax Range: " + ToString(m_ptrMech.m_weapons[i]->GetMaxRange())
				+ "\nAmmo Per Shot: " + ToString(m_ptrMech.m_weapons[i]->GetAmmo()) + "\n";
			m_weapString.SetText(m_weapons);
			m_weapString.SetPosition(50+(i*150),400);
			MainGame.GetWindow().Draw(m_weapString);
		}
		
		

		
		//Draw Mech Image
		switch(m_mechPage)
		{
		case 1:
				MainGame.GetWindow().Draw(m_rLMechSprite);
				MainGame.GetWindow().Draw(m_lightString);
				MainGame.GetWindow().Draw(m_LMechSprite);
				m_ptrMech.SetMechType(RLight);
			break;
		case 2:
				MainGame.GetWindow().Draw(m_rMMechSprite);
				MainGame.GetWindow().Draw(m_medString);
				MainGame.GetWindow().Draw(m_MMechSprite);
				m_ptrMech.SetMechType(RMedium);
			break;
		case 3:
				MainGame.GetWindow().Draw(m_rHMechSprite);
				MainGame.GetWindow().Draw(m_heavyString);
				MainGame.GetWindow().Draw(m_HMechSprite);
				m_ptrMech.SetMechType(RHeavy);
			break;
		case 4:
				MainGame.GetWindow().Draw(m_bLMechSprite);
				MainGame.GetWindow().Draw(m_lightString);
				MainGame.GetWindow().Draw(m_LMechSprite);
				m_ptrMech.SetMechType(BLight);
			break;
		case 5:
				MainGame.GetWindow().Draw(m_bMMechSprite);
				MainGame.GetWindow().Draw(m_medString);
				MainGame.GetWindow().Draw(m_MMechSprite);
				m_ptrMech.SetMechType(BMedium);
			break;
		case 6:
				MainGame.GetWindow().Draw(m_bHMechSprite);
				MainGame.GetWindow().Draw(m_heavyString);
				MainGame.GetWindow().Draw(m_HMechSprite);
				m_ptrMech.SetMechType(BHeavy);
			break;
		}
	}

	void MechMenu:: Init()
	{
		MainGame.SetWidgetContainer(widgets);
		m_mechPage = 1;
		m_weapString.SetSize(17);
		m_HMechImage.LoadFromFile("Resources/RHeavyUI.png");
		m_MMechImage.LoadFromFile("Resources/RMedUI.png");
		m_LMechImage.LoadFromFile("Resources/RLightUI.png");

		m_HMechSprite.SetImage(m_HMechImage);
		m_MMechSprite.SetImage(m_MMechImage);
		m_LMechSprite.SetImage(m_LMechImage);

		m_HMechSprite.SetPosition(500,100);
		m_MMechSprite.SetPosition(500,100);
		m_LMechSprite.SetPosition(500,100);

		m_rHMechSprite.SetImage(m_mechHRImage);
		m_rMMechSprite.SetImage(m_mechMRImage);
		m_rLMechSprite.SetImage(m_mechLRImage);

		m_bHMechSprite.SetImage(m_mechHBImage);
		m_bMMechSprite.SetImage(m_mechMBImage);
		m_bLMechSprite.SetImage(m_mechLBImage);

		m_rHMechSprite.SetPosition(sf::Vector2f(400,200));
		m_rMMechSprite.SetPosition(sf::Vector2f(400,200));
		m_rLMechSprite.SetPosition(sf::Vector2f(400,200));
		m_bHMechSprite.SetPosition(sf::Vector2f(400,200));
		m_bMMechSprite.SetPosition(sf::Vector2f(400,200));
		m_bLMechSprite.SetPosition(sf::Vector2f(400,200));

		m_PlainsSprite.SetImage(plains);
		m_LForestSprite.SetImage(lWoods);
		m_RocksSprite.SetImage(rocks);
		m_HForestSprite.SetImage(hWoods);
		m_PlainsSprite.SetPosition(sf::Vector2f(500,600));
		m_LForestSprite.SetPosition(sf::Vector2f(600,600));
		m_RocksSprite.SetPosition(sf::Vector2f(600,700));
		m_HForestSprite.SetPosition(sf::Vector2f(500,700));
	}

	void MechMenu:: Exit()
	{
		//for(int i = 0; i < widgets.size(); i++)
		//{
			//delete widgets[i];
		//}
		//widgets.clear();
	}
}
