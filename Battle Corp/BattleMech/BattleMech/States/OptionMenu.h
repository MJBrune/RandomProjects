
#ifndef STATES_OPTIONMENU
#define STATES_OPTIONMENU

#include <SFML/Graphics.hpp>
#include "../GameState.h"
#include "../Globals.h"
#include "../UI/Text.h"
#include "../UI/Button.h"


namespace States
{
	class OptionMenu: public GameState
	{
	private:
		std::vector<UI::Widget*>	widgets;
		UI::Button	*				m_okayBtn;
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

		OptionMenu();

		virtual void Update(float timespan);

		virtual void Render();

		virtual void Init();

		virtual void Exit();
	};
}

#endif