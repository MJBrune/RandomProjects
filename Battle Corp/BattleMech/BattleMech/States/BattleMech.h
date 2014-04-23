#ifndef STATE_MAINGAME
#define STATE_MAINGAME

#include "../GameState.h"
#include "../Network/GameClient.h"
#include "../Network/Server.h"
#include "../UI/Button.h"
#include <SFML/Network.hpp>
#include "../Globals.h"
#include <iostream>
#include "../HelperFunctions.h"

const short DEFAULTSERVERPORT = 10003;

namespace States
{
	class BattleMech: public GameState
	{
	public:

		BattleMech();
		BattleMech(sf::IPAddress ipAddr);

		void HostConnect();

		void Connect(sf::IPAddress ipAddr, const bool &hosting = false);

		void SetBattleMechType(const unsigned &type);

		virtual void Update(float timespan);

		virtual void Render();

		virtual void Init()	;

		virtual void Exit();


	private:
		bool connected;
		bool isMoving;
//		bool firing;
		Network::GameClient client;
		Network::Server		hostServer;	//NOTE: ONLY FOR HOST JOIN PURPOSES
		bool isHosting;
		UI::Button m_endTurnBtn;
		sf::Image m_leftUIImage;
		sf::Sprite m_leftUI;
		sf::Shape m_endTurnBox;
		sf::String m_endTurnText;

		sf::Image m_rHeavyUIImage;
		sf::Image m_rMedUIImage;
		sf::Image m_rLightUIImage;
		
		bool m_directionSwitch;
		UI::Button m_NorthBtn;
		sf::Shape m_NorthBox;
		sf::String m_NorthText;

		UI::Button m_NorthWestBtn;
		sf::Shape m_NorthWestBox;
		sf::String m_NorthWestText;

		UI::Button m_NorthEastBtn;
		sf::Shape m_NorthEastBox;
		sf::String m_NorthEastText;

		UI::Button m_SouthWestBtn;
		sf::Shape m_SouthWestBox;
		sf::String m_SouthWestText;

		UI::Button m_SouthEastBtn;
		sf::Shape m_SouthEastBox;
		sf::String m_SouthEastText;

		UI::Button m_SouthBtn;
		sf::Shape m_SouthBox;		
		sf::String m_SouthText;

		sf::Sprite m_rHeavyUI;
		sf::Sprite m_rMedUI;
		sf::Sprite m_rLightUI;
		Mech * displayMech;
		sf::String mechInfo;
		std::ostringstream mechInfoStr;
		int* displayMechArmor;

		sf::Shape m_boxForFire;
		sf::String m_fire;
		std::vector<UI::Button *> m_fireForWeapon;
		std::vector<sf::String> m_weaponsForMech;
		std::vector<UI::Widget*>	m_widgets;
	};
}

#endif
