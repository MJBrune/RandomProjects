
#ifndef STATES_MECHMENU
#define STATES_MECHMENU

#include <SFML/Graphics.hpp>
#include "../GameState.h"
#include "../Globals.h"
#include "../UI/Text.h"
#include "../UI/Button.h"
#include "BattleMech.h"

extern States::BattleMech bMechGame;
namespace States
{
	class MechMenu: public GameState
	{
	private:
		std::vector<UI::Widget*>	widgets;
		UI::Button	*				m_okayBtn;
		UI::Button  *				m_nextBtn;
		UI::Button  *				m_backBtn;
		UI::Button  *				m_mechBtn;

		int							m_mechPage;
		int							m_mechClicked;
		sf::Sprite					m_rHMechSprite;
		sf::Sprite					m_rMMechSprite;
		sf::Sprite					m_rLMechSprite;
		sf::Sprite					m_bHMechSprite;
		sf::Sprite					m_bMMechSprite;
		sf::Sprite					m_bLMechSprite;

		sf::String					m_lightString;
		sf::String					m_medString;
		sf::String					m_heavyString;

		sf::String					m_weapString;
		std::string					m_weapons;
		Mech						m_ptrMech;
		sf::Sprite					m_HMechSprite;
		sf::Sprite					m_MMechSprite;
		sf::Sprite					m_LMechSprite;

		sf::Image					m_HMechImage;
		sf::Image					m_MMechImage;
		sf::Image					m_LMechImage;
		
		UI::Button  *				m_typeOneBtn;
		UI::Button  *				m_typeTwoBtn;

		int							m_plainsPage;
		int							m_lForstPage;
		int							m_hForstPage;
		int							m_rocksPage;
		int							m_terrianClicked;
		sf::Sprite					m_PlainsSprite;
		sf::Sprite					m_LForestSprite;
		sf::Sprite					m_RocksSprite;
		sf::Sprite					m_HForestSprite;
	public:

		MechMenu();

		virtual void Update(float timespan);

		virtual void Render();

		virtual void Init();

		virtual void Exit();
	};
}

#endif