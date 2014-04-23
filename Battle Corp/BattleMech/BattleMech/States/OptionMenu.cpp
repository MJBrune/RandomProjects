#include "OptionMenu.h"
#include "MainMenu.h"

extern States::MainMenu	bMainMenu;

namespace States
{
	OptionMenu::OptionMenu()
	{

		m_okayBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_okayBtn);

		m_typeOneBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_typeOneBtn);

		m_typeTwoBtn = new UI::Button(sf::FloatRect(0,0,280,50));
		widgets.push_back(m_typeTwoBtn);

	//	m_mechBtn = new UI::Button(sf::FloatRect(0,0,77,66));
	//	widgets.push_back(m_mechBtn);

		m_okayBtn->SetPosition(sf::Vector2f(100,100));
		m_typeOneBtn->SetPosition(sf::Vector2f(100,200));
		m_typeTwoBtn->SetPosition(sf::Vector2f(100,300));
	//	m_mechBtn->SetPosition(sf::Vector2f(500,300));

	}

	void OptionMenu:: Update(float timespan)
	{
		if(m_okayBtn->IsClicked())
		{
			MainGame.SetState(bMainMenu);
		}
		else if(m_typeOneBtn->IsClicked())
		{
			plains.LoadFromFile("plains.png");
			lWoods.LoadFromFile("LWoods.png");
			hWoods.LoadFromFile("HWoods.png");
			rocks.LoadFromFile("rocks.png");

		}
		else if(m_typeTwoBtn->IsClicked())
		{
			plains.LoadFromFile("plains2low.png");
			lWoods.LoadFromFile("LWoods2low.png");
			hWoods.LoadFromFile("HWoods2low.png");
			rocks.LoadFromFile("rock2low.png");
		}

	}

	void OptionMenu:: Render()
	{
		MainGame.GetWindow().Clear(sf::Color(100,100,255));

		//Draw Okay Button
		sf::Shape exitBox = sf::Shape::Rectangle(m_okayBtn->GetBoundingBox().Left, m_okayBtn->GetBoundingBox().Top, m_okayBtn->GetBoundingBox().Right, m_okayBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(exitBox);
		sf::String exitText("Okay");
		exitText.SetPosition(m_okayBtn->GetPosition());
		exitText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(exitText);

		//Draw Next Button
		sf::Shape typeOneBox = sf::Shape::Rectangle(m_typeOneBtn->GetBoundingBox().Left, m_typeOneBtn->GetBoundingBox().Top, m_typeOneBtn->GetBoundingBox().Right, m_typeOneBtn->GetBoundingBox().Bottom, sf::Color(255,255,255),1);
		MainGame.GetWindow().Draw(typeOneBox);
		sf::String typeOneText("Terrian Type 1");
		typeOneText.SetPosition(m_typeOneBtn->GetPosition());
		typeOneText.SetColor(sf::Color::Black);
		MainGame.GetWindow().Draw(typeOneText);


		//Draw Back Button
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
	}

	void OptionMenu:: Init()
	{
		MainGame.SetWidgetContainer(widgets);

		m_PlainsSprite.SetImage(plains);
		m_LForestSprite.SetImage(lWoods);
		m_RocksSprite.SetImage(rocks);
		m_HForestSprite.SetImage(hWoods);
		m_PlainsSprite.SetPosition(sf::Vector2f(500,300));
		m_LForestSprite.SetPosition(sf::Vector2f(600,300));
		m_RocksSprite.SetPosition(sf::Vector2f(600,400));
		m_HForestSprite.SetPosition(sf::Vector2f(500,400));
	}

	void OptionMenu:: Exit()
	{
	}
}